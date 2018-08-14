# tensorboardprotobuf
Write input files (protobuffers) for Tensorboard with minimal dependencies (protobuf libs)

## Interface
There are only two classes implementing the interface for this library: `Run` and `Record`. A `Run` instance is tied to one tensorboard input file and contains an arbitrary number of `Record` instances. A `Record` is tied to a step and contains scalar values (images etc...) tbd.


## Installation
```
#cd into protobuf source dir
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=1 -DCMAKE_INSTALL_PREFIX=/usr ../cmake
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

## Notes
used 2cbcc471d6340fac1ceca9b9559f62ec2d71a769 for proto definitions from https://github.com/tensorflow/tensorflow/

