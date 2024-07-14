cmake_minimum_required(VERSION 3.18)
project(SharedLibraryExample)

set(MUZZLE_ROOT "../..")
set(MUZZLE_LIB_DIR ${MUZZLE_ROOT}/lib)
set(CMAKE_BUILD_TYPE Debug)

INCLUDE_DIRECTORIES(${MUZZLE_ROOT}/include)
link_directories(${MUZZLE_LIB_DIR})

add_executable(main main.c)
target_link_libraries(main muzzle)
