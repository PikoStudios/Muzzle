cmake_minimum_required(VERSION 3.18)

project(ShaderPass)
set(MUZZLE_ROOT "../..")
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/lib)
set(MUZZLE_DEPS_FOLDER ${MUZZLE_ROOT}/deps)
set(FREETYPE ${MUZZLE_DEPS_FOLDER}/freetype)
set(target_name main)

set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(MUZZLE_LIB muzzled)
    add_compile_definitions(MUZZLE_DEBUG_BUILD)
else()
    set(MUZZLE_LIB muzzle)
endif()

include_directories(${MUZZLE_ROOT}/include ${FREETYPE}/include)
link_directories(${MUZZLE_ROOT}/lib ${MUZZLE_DEPS_FOLDER}/glfw/lib ${FREETYPE}/lib)

add_executable(${target_name} main.c)

message(STATUS "Checking OS")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Checking OS - found (Darwin/MacOS)")
    message(WARNING "Checking OS - warning (Darwin/MacOS support in this CMakeLists.txt is very limited)")

    target_link_libraries(${target_name} ${MUZZLE_LIB} glfw3 freetype CoreVideo OpenGL IOKit Cocoa Carbon)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Checking OS - found (WIN32)")
    target_link_libraries(${target_name} ${MUZZLE_LIB} glfw3 freetype opengl32 gdi32 DSound)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Checking OS - found (Linux)")
    target_link_libraries(${target_name} ${MUZZLE_LIB} glfw3 freetype GL m z)

else ()
# Default to Unix
    message(STATUS "Checking OS - not found (Unix)")
    target_link_libraries(${target_name} ${MUZZLE_LIB} glfw3 freetype GL m z)
endif ()
