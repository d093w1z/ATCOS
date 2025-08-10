#!/bin/bash
SOURCE_DIR=src/
BUILD_DIR=build

find $SOURCE_DIR \( -name "*.cpp" -o -name "*.hpp" \) \
  -exec clang-tidy -p $BUILD_DIR {} +
