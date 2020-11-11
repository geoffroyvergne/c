FROM conanio/clang9 AS build

#COPY conanfile.txt .
#RUN mkdir build

#RUN conan install . -if build/

COPY . .

#RUN cmake -DCMAKE_C_FLAGS="-pthread -static" . -B build/
RUN cmake -DCMAKE_C_FLAGS="-pthread" . -B build/
RUN cmake --build build/

#FROM alpine
FROM conanio/clang9

COPY --from=build /home/conan/build/tcp-server  /usr/local/bin
#COPY etc/conf.ini /etc/http-server/conf.ini

#ENTRYPOINT ["/usr/local/bin/entrypoint.sh", "/usr/local/bin/http-server_main"]
#CMD ["-t", "/var/www", "--host", "0.0.0.0"]

CMD ["/usr/local/bin/tcp-server"]
