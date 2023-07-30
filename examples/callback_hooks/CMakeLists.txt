cmake_minimum_required(VERSION 3.18)

project(Muzzle)
set(MUZZLE_ROOT "../..")
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/deps)

set(CMAKE_BUILD_TYPE Debug)

INCLUDE_DIRECTORIES(${MUZZLE_ROOT}/include)
LINK_DIRECTORIES(${MUZZLE_LIB_FOLDER}/glfw/lib)
set(mz_source_dir ${MUZZLE_ROOT}/src)

#could use aux_source_directory() but its better to list each file to ensure new files are compiled
#https://stackoverflow.com/a/25077976/10415312

set(mz_internal_src
${mz_source_dir}/internal/core.callbacks.internal.c
${mz_source_dir}/internal/core.default_shaders.internal.c
)

set(mz_source
${mz_source_dir}/Applet.c
${mz_source_dir}/Drawing.c
${mz_source_dir}/Error.c
${mz_source_dir}/Batch.c
${mz_source_dir}/Shader.c
${mz_source_dir}/Memory.c
${mz_source_dir}/CallbackHook.c
${mz_internal_src}
${MUZZLE_LIB_FOLDER}/glad/src/glad.c
)

add_executable(main main.c ${mz_source})

message(STATUS "Checking OS")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Checking OS - found (Darwin/MacOS)")
    message(WARNING "Checking OS - warning (Darwin/MacOS support in this CMakeLists.txt is very limited)")
    
    TARGET_LINK_LIBRARIES(main glfw CoreVideo OpenGL IOKit Cocoa Carbon)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Checking OS - found (WIN32)")
    TARGET_LINK_LIBRARIES(main glfw3 opengl32 gdi32 DSound)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Checking OS - found (Linux)")
    TARGET_LINK_LIBRARIES(main glfw GL m)

else ()
# Default to Unix
    message(STATUS "Checking OS - not found (Unix)")
    TARGET_LINK_LIBRARIES(main glfw GL m)
endif ()