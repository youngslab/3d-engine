

find_package(glm REQUIRED)
find_package(fmt REQUIRED)
find_package(glad REQUIRED)
find_package(stb REQUIRED)

add_library(ogl STATIC
	src/shader.cpp
	src/texture.cpp
	src/resource.cpp
	src/indexbuffer.cpp
	src/vertexattribute.cpp
	src/vertexbuffer.cpp
	src/vertexarray.cpp
	src/program.cpp
	src/framebuffer.cpp
	src/loader.cpp)

target_link_libraries(ogl PUBLIC glad::glad glm::glm
			fmt::fmt stb::stb stdc++fs)

target_include_directories(ogl PUBLIC ./include)

target_compile_features(ogl PUBLIC cxx_std_17)
