#!/bin/bash

export ANDROID_NDK=~/data/android-ndk-r8e/
rm -r build
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/android.toolchain.cmake -DANDROID_API_LEVEL=9 -H. -Bbuild
make -C build
