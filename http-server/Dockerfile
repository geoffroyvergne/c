FROM conanio/clang9 AS build

COPY conanfile.txt .
RUN mkdir build

RUN conan install . -if build/

COPY . .

#RUN cmake -DCMAKE_C_FLAGS="-pthread -static" . -B build/
RUN cmake -DCMAKE_C_FLAGS="-pthread" . -B build/
RUN cmake --build build/

#FROM alpine
FROM conanio/clang9

COPY --from=build /home/conan/build/src/bin/http-server_main  /usr/local/bin
COPY www /var/www

CMD ["/usr/local/bin/http-server_main", "-t", "/var/www"]

