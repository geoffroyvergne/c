# HTTP Server

```
cd <project/root>
cmake -S . -B build/
cmake --build build/
```

# Run

```
./build/http-server --port <port> default 3000
```

# Todo

- [ X ] Improve string concatenation strcat alternative ?
- [ X ] Use file for 404 error
- [ ] Use ini file for config
- [ ] add unit tests
- [ ] Add Memory Leak checker -Valgrind