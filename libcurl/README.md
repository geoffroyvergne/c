# libcurl http client
https://github.com/curl/curl/tree/master/docs/examples

https://curl.haxx.se/libcurl/c/simple.html
https://github.com/curl/curl/blob/master/docs/examples/simple.c

gcc simple.c -o bin/simple `curl-config --cflags --libs`

https://github.com/curl/curl/blob/master/docs/examples/parseurl.c


gcc parseurl.c -o bin/parseurl `curl-config --cflags --libs`
