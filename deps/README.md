# Dependencies
**`glfw` and `kazmath` are both submodules.**

## How to build GLFW
GLFW is the standard CMake compiliation process

```
cd glfw
mkdir lib
mkdir build
cd build
cmake .. -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF
make # or your build tool
make install # or your build tool
mv src/libglfw3.a ../lib/libglfw3.a
```

## How to build Kazmath
```
cd kazmath
mkdir lib
mkdir build
cd build
cmake .. -DKAZMATH_BUILD_TESTS=OFF -DKAZMATH_BUILD_JNI_WRAPPER=OF -DKAZMATH_BUILD_GL_UTILS=OFF -DKAZMATH_BUILD_LUA_WRAPPER=OFF
make
make install
mv kazmath/libkazmath.a ../lib/libkazmath.a
```