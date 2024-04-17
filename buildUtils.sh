#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi

cmake ..
sudo cmake --build . --target install