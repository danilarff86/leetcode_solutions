FROM golang:1.16-alpine

WORKDIR /leetcode

# copy golang tests
COPY ./go.mod ./go.mod
COPY ./go.sum ./go.sum
COPY ./gosolutions ./gosolutions

# copy c++ tests
COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./solutions ./solutions

RUN apk update
RUN apk add gcc g++ cmake ninja git

# compile golang tests
RUN go test -v -c -o gotests ./gosolutions/...

# compile c++ tests
RUN cmake -GNinja .
RUN ninja solutions

CMD ./solutions/solutions && ./gotests -test.v
