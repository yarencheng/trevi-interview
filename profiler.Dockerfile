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

## size of dirty words to be generate in test case
ENV DATASIZE_MIN=100000
ENV DATASIZE_MAX=200000
ENV DATASIZE_STEP=10000

## size of strings to be filtered in test case
ENV SAMPLE_SIZE=1000

COPY profiler.entry.sh .
RUN chmod +x profiler.entry.sh
CMD ./profiler.entry.sh