FROM golang:1.18.3-alpine

WORKDIR /leetcode

RUN apk update
RUN apk add gcc g++ cmake ninja git

# copy golang tests
COPY ./go.mod ./go.mod
COPY ./go.sum ./go.sum
COPY ./gosolutions ./gosolutions

# copy c++ tests
COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./CMakeLists.txt.in ./CMakeLists.txt.in
COPY ./cppsolutions ./cppsolutions

# compile golang tests
RUN go test -v -c -o gotests ./gosolutions/...

# compile c++ tests
RUN cmake -GNinja .
RUN ninja cpptests

CMD ./cpptests && ./gotests -test.v
