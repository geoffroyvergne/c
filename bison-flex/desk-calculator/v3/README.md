# Simple calculator example
https://github.com/meyerd/flex-bison-example

make
make clean

bison -d calc.y
flex calc.l
gcc calc.tab.c lex.yy.c -o calc -lm
./calc

## TODO
fix divide not reconized
