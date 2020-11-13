# HTTP Server

```
cd <project/root>
cmake -S . -B build/
cmake --build build/
```

## Dependencies lib

```
CuTest 
inih
```

# Run

```
./build/http-server --port <port> default 3000

./build/bin/http-server -c etc/conf.ini
```

# Test

```
./build/src/bin/http-server_test
```

# Docker

```
docker build . -t http-server
docker run -p 3000:3000 --name http-server --rm http-server
docker run -ti --name http-server --rm http-server /usr/local/bin/http-server_main

docker run -p 3000:3000 --name http-server --rm http-server -c /etc/http-server/conf.ini
docker run -p 8000:8000 --name http-server --rm http-server -p 8000

docker run -ti --name http-server --rm http-server bash
```

# Todo

- [ X ] Improve string concatenation strcat alternative ?
- [ X ] Use file for 404 error
- [ X ] Use ini file for config
- [ X ] add unit tests
- [ ] Add Memory Leak checker -Valgrind
- [ X ] give ability to use localhost and 0.0.0.0 on socket
- [ ] use constants for http return header mimetype ...
- [ X ] dockerize
- [ ] manage errors (www target ini conf ...)
- [ ] test css js files
- [ ] send images files jpg png over socket
- [ X ] manage index.html by default
- [ ] Add Variable env in config
- [ ] 
