# tensorboardprotobuf
Protocol buffers for Tensorboard interface

based off https://github.com/shaochuan/cmake-protobuf-example

```
#cd into protobuf source dir
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=-DCMAKE_INSTALL_PREFIX:PATH=/usr ../cmake
cmake --build . 
cmake --build . --target install
```