# libxml2

https://www.julp.fr/articles/1-2-manipulation-d-un-document-xml-avec-la-methode-dom.html#transformer-un-document-xml-en-arbre-dom

gcc `xml2-config --cflags --libs` -o bin/simple-example simple-example.c 


gcc -o bin/simple-example  `xml2-config --cflags` simple-example.c  `xml2-config --libs`

gcc -o bin/simple-example simple-example.c $(xml2-config --cflags --libs)

gcc -o bin/simple-example simple-example.c \
-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libxml2 \
-L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lxml2 -lz -lpthread -licucore -lm
