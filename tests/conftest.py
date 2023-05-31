import subprocess

import pytest


def pytest_collect_file(parent, path):
    """Yield a description of a file if this is indeed a C test file"""
    if path.ext != ".c":
        return None
    yield CFile.from_parent(parent=parent, fspath=path)


class CFile(pytest.File):
    def collect(self):
        # type: () -> Iterable[Union["Item", "Collector"]]
        pass


class CTestItem(pytest.Item):
    def runtest(self):
        # type: () -> None
        """Build the binary and run the test."""
        proc = subprocess.run(
            [
                "make",
                "-DMETALC_TEST_NAME='" + self.name + "'",
            ],
            stderr=subprocess.PIPE,
        )

        if proc.returncode != 0:
            raise AssertionError(
                "Compilation failed:\n" + proc.stderr.decode("utf-8")
            )
