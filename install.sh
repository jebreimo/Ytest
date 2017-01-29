#!/bin/bash

YSTRING_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

if [ ! -d release.Ystring ]
then
    mkdir release.Ystring
fi

cd release.Ystring
cmake -DINSTALL_YTEST -DCMAKE_BUILD_TYPE=Release $YSTRING_DIR
make install
cd ..

if [ ! -d debug.Ystring ]
then
    mkdir debug.Ystring
fi

cd debug.Ystring
cmake -DINSTALL_YTEST -DCMAKE_BUILD_TYPE=Debug $YSTRING_DIR
make install
cd ..
