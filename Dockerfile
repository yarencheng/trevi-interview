FROM ubuntu:18.04 as builder

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake

WORKDIR /src
COPY * ./

WORKDIR /src/build
RUN cmake ..
RUN make

FROM ubuntu:18.04

COPY --from=builder /src/build/filter /usr/bin/filter

CMD [ "filter" ]