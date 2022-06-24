#!/bin/bash
## GNU Make and Git are needed for this script
## Install them through the websites or apt

## If not on debian, change these to your distro's package managers
sudo apt-get install libxi-dev
sudo apt-get install libxcursor-dev
sudo apt-get install libxinerama-dev
sudo apt-get install libxrandr-dev

cd ../deps/glfw
mkdir build
cd build
cmake .. -G "Unix Makefiles"

make
sudo make install