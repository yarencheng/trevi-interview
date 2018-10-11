FROM ubuntu:18.04 as builder

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake

WORKDIR /src
COPY . ./
COPY profiler.CMakeLists.txt CMakeLists.txt

WORKDIR /src/build
RUN cmake ..
RUN make

RUN ./profiler