mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/raylib/mingw/bin__/gcc.exe -DCMAKE_MAKE_PROGRAM=C:\raylib\mingw\bin__\mingw32-make.exe
C:\raylib\mingw\bin__\mingw32-make.exe
.\main.exe
cd ..
rm .\build\