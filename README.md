# tensorboardprotobuf
Protocol buffers for Tensorboard interface

based off https://github.com/shaochuan/cmake-protobuf-example

```
#cd into protobuf source dir
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=1 ../cmake
cmake --build . -- -j 8
cmake --build . --target install
```
```
#cd into source dir
mkdir build
cd build
cmake ..
cmake --build .
```

```
docker run -it --rm --mount type=bind,source=$(pwd),target=/tensorboardix ixdev.azurecr.io/ixtensorboard:latest /bin/bash
```