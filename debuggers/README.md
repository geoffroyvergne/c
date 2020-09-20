# compile
gcc -Wall -g gdbtest.c -o bin/gdbtest

# GDB Gnu DeBugger

## run as debug
gdb bin/gdbtest

# lldb llvm DeBugger

## run as debug
ldb bin/gdbtest

# breakpoint
## gdb
break <line>
## llvm
breakpoint set -l <line>