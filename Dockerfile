FROM gcc:10.2

WORKDIR /leetcode

COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./solutions ./solutions

RUN apt update
RUN apt install -y cmake ninja-build

RUN mkdir build
RUN cd build && cmake -GNinja ../
RUN cd build && ninja solutions

CMD [ "./build/solutions/solutions" ]
