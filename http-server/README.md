# HTTP Server

```
cd <project/root>
cmake -S . -B build/
cmake --build build/
```

# Run

```
./build/http-server --port <port> default 3000

./build/bin/http-server -c etc/conf.ini
```

# Todo

- [ X ] Improve string concatenation strcat alternative ?
- [ X ] Use file for 404 error
- [ X ] Use ini file for config
- [ ] add unit tests
- [ ] Add Memory Leak checker -Valgrind
- [ ] give ability to use localhost and 0.0.0.0 on socket
- [ ] use constants for http return header mimetype ...
- [ ] 
