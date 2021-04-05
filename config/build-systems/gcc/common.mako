CC=${TARGET_PLATFORM_SLUG}-unknown-${TARGET_ABI}-gcc
LD=${TARGET_PLATFORM_SLUG}-unknown-${TARGET_ABI}-ld
AS=${ASSEMBLER}

CFLAGS=-Wall -Wextra -Werror -pedantic -pedantic-errors
% if BUILD_MODE == "debug"
CFLAGS=$(CFLAGS) -Og -ggdb
% else
    % if OPTIMIZE_FOR == "size"
        CFLAGS=$(CFLAGS) -Osize
    % elif OPTIMIZE_FOR == "speed"
        CFLAGS=$(CFLAGS) -Ofast
    % endif
% endif

% if not KERNEL_SUPPORT__RED_ZONE
    CFLAGS=$(CFLAGS) -mno-red-zone
% endif

## this is a comment
