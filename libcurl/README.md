# libcurl http client
https://curl.haxx.se/libcurl/c/simple.html

gcc simple.c -o bin/simple `curl-config --cflags --libs`