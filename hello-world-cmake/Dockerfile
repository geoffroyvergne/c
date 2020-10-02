FROM conanio/clang9-x86 AS build
#WORKDIR /src
COPY CMakeLists.txt hello-world.c ./
#RUN cmake . && make
RUN cmake -DCMAKE_C_FLAGS=-static . -B build/ && cmake --build build/

FROM alpine
#WORKDIR /opt/hello-world
COPY --from=build /home/conan/build/helloworld ./
CMD ["./helloworld"]
