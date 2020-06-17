

cmake_minimum_required(VERSION 3.10)


project(object-graphics)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(common)
add_subdirectory(object-gl)
# add_subdirectory(object-engine)

if(${OGFX_EXAMPLE})
add_subdirectory(example)
endif()
