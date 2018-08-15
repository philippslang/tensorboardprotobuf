FROM gcc:8

RUN mkdir cmaketmp && cd cmaketmp \
    && wget https://cmake.org/files/v3.12/cmake-3.12.1.tar.gz \
    && tar xf cmake-3.12.1.tar.gz \
    && cd cmake-3.12.1 \
    && ./bootstrap \
    && make -j 4 \
    && make install \
    && cd / \
    && rm -rf cmaketmp

RUN mkdir protobuftmp && cd protobuftmp \
    && wget https://github.com/google/protobuf/releases/download/v3.6.1/protobuf-cpp-3.6.1.tar.gz \
    && tar -xvf protobuf-cpp-3.6.1.tar.gz \
    && cd protobuf-3.6.1 \
    && mkdir build \
    && cd build \
    && cmake -DBUILD_SHARED_LIBS=1 -DCMAKE_INSTALL_PREFIX=/usr ../cmake \
    && cmake --build . -- -j 4 \
    && cmake --build . --target install \
    && cd / \
    && rm -rf protobuftmp

