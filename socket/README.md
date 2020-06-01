# C socket

quit telnet : ctrl + $ > quit
lsof -i -n -P | grep 8888

https://www.binarytides.com/socket-programming-c-linux-tutorial/

gcc simple-socket.c -o bin/simple-socket

gcc threaded-socket-connection.c -o bin/threaded-socket-connection -lpthread