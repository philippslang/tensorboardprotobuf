FROM fedora:28


RUN yum install -y gcc gcc-c++ make findutils which chrpath bzip2-devel bzip2 zlib-devel wget binutils unzip zip gpg file tar.x86_64 libuuid cmake \
    && yum clean all \
    && rm -rf /var/cache/yum

RUN mkdir protobuftmp && cd protobuftmp \
    && wget https://github.com/google/protobuf/releases/download/v3.6.1/protobuf-cpp-3.6.1.tar.gz \
    && tar -xvf protobuf-cpp-3.6.1.tar.gz \
    && cd protobuf-3.6.1 \
    && mkdir build \
    && cd build \
    && cmake -DBUILD_SHARED_LIBS=1 -DCMAKE_INSTALL_PREFIX=/usr ../cmake \
    && cmake --build . -- -j 8 \
    && cmake --build . --target install \
    && cd / \
    && rm -rf protobuftmp
 
