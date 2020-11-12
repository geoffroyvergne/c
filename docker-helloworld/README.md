# Docker helloworld

docker build -f Dockerfile -t helloworld .

docker run --rm --name helloworld helloworld

docker run -ti helloworld sh

docker run -ti --rm conanio/clang9-x86 bash


ldd helloworld
 ---> Running in 004b224e5122
        linux-gate.so.1 (0xf7f7f000)
        libstdc++.so.6 => /lib/i386-linux-gnu/libstdc++.so.6 (0xf7d8c000)
        libm.so.6 => /lib/i386-linux-gnu/libm.so.6 (0xf7c87000)
        libgcc_s.so.1 => /lib/i386-linux-gnu/libgcc_s.so.1 (0xf7c68000)
        libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xf7a7b000)
        /lib/ld-linux.so.2 (0xf7f81000)