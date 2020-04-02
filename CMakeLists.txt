
cmake_minimum_required(VERSION 3.10)

project(object-gl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(ogl)

if(${OGL_EXAMPLE})
add_subdirectory(example)
endif()


