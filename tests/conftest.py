import more_itertools
import pytest
import unicorn
from unicorn import x86_const


class RegisterAccessor:
    def __init__(self, machine):
        self.machine = machine

    def __getitem__(self, register_id):
        return self.machine.engine.reg_read(register_id)

    def __setitem__(self, register_id, value):
        self.machine.engine.reg_write(register_id, value)


class MemoryAccessor:
    def __init__(self, machine):
        self.machine = machine

    def indexer_to_bounds(self, slice_or_int):
        if isinstance(slice_or_int, int):
            return slice_or_int, slice_or_int

        # Caller gave us a slice
        if slice_or_int.step is not None:
            raise ValueError("Slicing with any step is not supported.")

        if slice_or_int.start is None:
            base_address = 0
        else:
            base_address = slice_or_int.start

        # Allow indexing from the end of RAM
        if base_address < 0:
            base_address += self.machine.memory_size

        # The upper bound for mem_read is inclusive, so we need to subtract 1
        # from the given upper bound since Python uses exclusive upper bounds.
        if slice_or_int.stop is None:
            last_address = self.machine.memory_size - 1
        else:
            last_address = where.stop - 1

        return base_address, last_address

    def __getitem__(self, where):
        base_address, last_address = self.indexer_to_bounds(where)
        return self.machine.engine.mem_read(base_address, last_address)

    def __setitem__(self, where, data):
        # Blow up if they try to write using a slice
        if not isinstance(where, int):
            raise TypeError(
                "Writing to memory must use an integer address, not a "
                + type(where).__name__
            )

        # Provide a nice error message if they try writing past the end of RAM.
        if where + len(data) >= self.machine.memory_size:
            raise IndexError(
                "Attempted to write past the end of memory: %d bytes at %#08x would"
                " exceed last valid address %#08x."
                % (len(data), where, self.machine.memory_size - 1)
            )
        self.machine.engine.mem_write(where, data)

    # Syntactic sugar for clearing RAM
    def __delitem__(self, where):
        base_address, last_address = self.indexer_to_bounds(where)
        data = b"\x00" * (last_address - base_address + 1)
        self[base_address] = data


class Machine:
    def __init__(self, architecture, address_width, interrupt_callback):
        # type: (int, int, Callable[[Machine, int, int, Tuple[bytes, ...]], None])
        # Map in 1 MiB of RAM for 16-bit architectures, otherwise 512 MiB
        if address_width == unicorn.UC_MODE_16:
            self.memory_size = 2 ** 20
        else:
            self.memory_size = 2 ** 29

        self.engine = unicorn.Uc(architecture, address_width)
        self.architecture = architecture
        self.address_width = address_width
        self.engine.mem_map(0, self.memory_size)
        self.registers = RegisterAccessor(self)
        self.memory = MemoryAccessor(self)
        self.interrupt_callback = interrupt_callback

    def load_image(self, contents):
        # type: (bytes) -> None
        self.engine.memory[0x8000] = contents

    def load_image_file(self, file_path):
        # type: (str) -> None
        with open(file_path, "rb") as fd:
            return self.load_image(fd.read())

    def start(self):
        # () -> None
        self.engine.emu_start(0x8000, self.memory_size - 0x8000)

    def stop(self):
        # () -> None
        self.engine.emu_stop()

    def close(self):
        # () -> None
        self.engine.uc_close()

    def _interrupt_hook(self, _engine, interrupt_number):
        # type: (unicorn.Uc, int) -> None
        if self.architecture == unicorn.UC_ARCH_X86:
            # AL contains the number of arguments. The stack pointer points to the base
            # of the memory we need to read to separate out the individual arguments.
            # The first argument is always a signed int giving the test ID; subsequent
            # arguments are passed to the handler as a tuple of each argument's raw
            # bytes. This way, it can interpret them as needed.
            n_args = self.registers[x86_const.UC_X86_REG_AL]

            if self.address_width == unicorn.UC_MODE_64:
                base_address = self.registers[x86_const.UC_X86_REG_RSP]
                argument_width = 8
            elif self.address_width == unicorn.UC_MODE_32:
                base_address = self.registers[x86_const.UC_X86_REG_ESP]
                argument_width = 4
            else:
                # Address calculation in x86-16 is a bit more involved.
                offset = self.registers[x86_const.UC_X86_REG_SP]
                segment = self.registers[x86_const.UC_X86_REG_SS]
                base_address = ((segment << 4) + offset) % 1048576
                argument_width = 2

            arg_bytes = self.memory[
                base_address : base_address + (n_args * argument_width)
            ]
            test_id_bytes, *args = more_itertools.sliced(arg_bytes, argument_width)

            return self.interrupt_callback(
                self,
                interrupt_number,
                int.from_bytes(test_id_bytes, "little", signed=True),
                args
            )

        raise NotImplementedError(
            "Unsupported architecture arch=%r address_width=%r"
            % (self.architecture, self.address_width)
        )


@pytest.fixture
def virtual_machine__x86_64():
    uc = Machine(unicorn.UC_ARCH_X86, unicorn.UC_MODE_64)
    uc.engine.memory[0x8000] = contents
    # TODO: Set instruction pointer and segment registers?
    uc.start()
    yield uc
    uc.stop()
    uc.close()
