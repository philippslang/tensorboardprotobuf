# tensorboardprotobuf
Write input files (protobuffers) for Tensorboard with minimal dependencies (protobuf libs). Downside is we shamelessly duplicate the
protobuf files from the tensorflow repo.

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

## License
All novel contributions under MIT license. 

Tensorflow components
- All protobuf files
- https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/lib/hash/crc32c.cc

under the following terms:

Copyright 2015 The TensorFlow Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================
