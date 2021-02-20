# Openssl server

https://wiki.openssl.org/index.php/Simple_TLS_Server

## generate certs

cert.pem
key.pem

openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout ./key.pem -out ./cert.pem


## Compile

gcc main.c -I/usr/local/Cellar/openssl@1.1/1.1.1i/include -L /usr/local/Cellar/openssl@1.1/1.1.1i/lib -lssl -lcrypto -o bin/ssl-server

## test

openssl s_client -connect localhost:3000
openssl s_client -connect localhost:3000 -CAfile ./cert.pem

