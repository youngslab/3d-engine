

find_package(glm REQUIRED)
find_package(fmt REQUIRED)
find_package(glad REQUIRED)
find_package(stb REQUIRED)

set(ogl_VERSION 0.0.1)

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

target_include_directories(ogl PUBLIC
   PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

target_compile_features(ogl PUBLIC cxx_std_17)

# support exporting in the build tree
export(TARGETS ogl NAMESPACE ogl:: FILE oglTargets.cmake)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE ogl)


install(TARGETS ogl
        EXPORT oglTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(EXPORT oglTargets
        FILE oglTargets.cmake
        NAMESPACE ogl::
        DESTINATION lib/cmake/ogl
         )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    oglConfigVersion.cmake
    VERSION ${ogl_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_file(${CMAKE_SOURCE_DIR}/CMake/oglConfig.cmake.in
                 oglConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/oglConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/oglConfigVersion.cmake"
        DESTINATION lib/cmake/ogl
        )
