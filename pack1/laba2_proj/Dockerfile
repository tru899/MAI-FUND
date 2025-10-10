FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential cmake valgrind

WORKDIR /project

COPY . /project

RUN mkdir -p build && cd build && cmake .. && cmake --build .

ENTRYPOINT ["valgrind", "--leak-check=full", "./build/laba2"]
