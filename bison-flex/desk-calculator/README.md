# Desk calculator mix flex + bison

## v1
flex -o bin/calculator.c calculator.l
cc bin/calculator.c -o bin/calculator -lfl

## v2

bison -d calculator.y
flex -o calculator.c calculator.l
cc -o bin/calculator calculator.tab.c calculator.c -lfl