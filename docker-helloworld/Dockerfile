# ------------- BUILD ----------------
# https://radupopescu.net/archive/static_linking_for_cpp/

FROM conanio/clang9-x86 as build

COPY src/ .

#RUN clang -static -o helloworld hello-world.c
RUN clang -o helloworld hello-world.c

#RUN ldd helloworld

RUN ./helloworld

# ------------- RUN ----------------

#FROM scratch
FROM conanio/clang9-x86
#FROM ubuntu:focal
#FROM alpine
#FROM gcr.io/distroless/cc

#RUN apt-get update && apt-get install -y libstdc++6
#RUN apk update && apk add --no-cache libstdc++
#RUN apk update && apk add --no-cache libstdc++ musl-dev

#RUN apk update && apk add --no-cache libstdc++ gcompat libc6-compat
#RUN apk update && apk add --no-cache libstdc++ libc6-compat

COPY --from=build /home/conan/helloworld /usr/local/bin/helloworld
CMD ["helloworld"]
