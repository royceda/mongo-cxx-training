#!/bin/bash

curl -OL  https://github.com/mongodb/mongo-c-driver/releases/download/1.17.3/mongo-c-driver-1.17.3.tar.gz \
&& tar xzf mongo-c-driver-1.17.3.tar.gz \
&& cd mongo-c-driver-1.17.3 \
&& mkdir cmake-build \
&& cd cmake-build \
&& cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF .. \
&& cmake --build . \
&& cmake --build . --target install



curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.2/mongo-cxx-driver-r3.6.2.tar.gz \
&& tar xzf mongo-cxx-driver-r3.6.2.tar.gz \
&& cd mongo-cxx-driver-r3.6.2/build \
&& cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local \
&& cmake --build . \
&& cmake --build . --target install





