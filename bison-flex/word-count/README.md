# Word Count unix wc like mix flex c

flex -o bin/wc.c wc.l
cc bin/wc.c -o bin/wc -lfl
./bin/wc <chars> ctrl+d

./bin/wc       
test
testt
testttt
       3       3      19

