#!/bin/sh

CMAKE_CXX_COMPILER=
CLANG_REQUIRED_VERSION=10
GCC_REQUIRED_VERSION=10

if [ -f /bin/clang++ ]; then
  CLANG_VERSION=`clang --version | grep clang | sed -E 's/.* (.*)-.*$/\1/'`
  CLANG_VERSION_MAJOR=`echo $CLANG_VERSION | sed -E 's/([^.]+).*/\1/'`
  if [ "$CLANG_VERSION_MAJOR" -ge "$CLANG_REQUIRED_VERSION" ]; then
    CMAKE_CXX_COMPILER=clang++
  fi
fi

if [ ! "$CMAKE_CXX_COMPILER" ]; then
  GCC_VERSION=`gcc --version | grep ^gcc | sed 's/^.* //'`
  GCC_VERSION_MAJOR=`echo $GCC_VERSION | sed -E 's/([^.]+).*/\1/'`
  if [ "$GCC_VERSION_MAJOR" -ge "$GCC_REQUIRED_VERSION" ]; then
    CMAKE_CXX_COMPILER=g++
  else
    if [ -f /bin/g++-10 ]; then
      CMAKE_CXX_COMPILER=g++-10
    else
      echo "Cannot find a compatible compiler. Terminate build."
      1>&2
      exit 1
    fi
  fi
fi

if [ ! -d build ]; then
  mkdir build
else
  rm -rf build/*
fi

cd build

cmake -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER "$@" ..
