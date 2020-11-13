# TCP Server

```
cd <project/root>
cmake -S . -B build/
cmake --build build/
```

# Run

```
./build/tcp-server --port <port> default 3000
```

# Docker

```
docker build . -t tcp-server
docker run -p 3000:3000 --name tcp-server --rm tcp-server
```

# Todo

- [ ] add host in cli params
- [ ] Add Memory Leak checker -Valgrind
- [ ] add unit tests and ini
- [ ] Refactor commands part in tcp-server.c
- [ ] Add Variable env in config
- [ ] 
