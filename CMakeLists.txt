
cmake_minimum_required(VERSION 3.10)

project(object-gl)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GNUInstallDirs)
message( "CMAKE_INSTALL_INCLUDEDIR: " ${CMAKE_INSTALL_INCLUDEDIR})

find_package(glm REQUIRED)
find_package(fmt REQUIRED)
find_package(glad REQUIRED)
find_package(stb REQUIRED)

set(ogl_VERSION 0.0.1)

set(OGL_PUBLIC_HEADERS
  ./include/ogl/framebuffer.h
  ./include/ogl/indexbuffer.h
  ./include/ogl/loader.h
  ./include/ogl/ogl.h
  ./include/ogl/program.h
  ./include/ogl/resource.h
  ./include/ogl/renderbuffer.h
  ./include/ogl/shader.h
  ./include/ogl/texture.h
  ./include/ogl/vertexarray.h
  ./include/ogl/vertexattribute.h
  ./include/ogl/vertexbuffer.h)

set(ogl_SOURCE_FILES
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

add_library(ogl ${ogl_SOURCE_FILES})

target_link_libraries(ogl
  PUBLIC
    glad::glad
    glm::glm
  PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

target_include_directories(ogl
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    $<TARGET_PROPERTY:stb::stb,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:fmt::fmt,INTERFACE_INCLUDE_DIRECTORIES>
)


target_compile_features(ogl PUBLIC cxx_std_17)


set_target_properties(ogl PROPERTIES
  PUBLIC_HEADER "${OGL_PUBLIC_HEADERS}")


# support exporting in the build tree
export(TARGETS ogl NAMESPACE ogl:: FILE oglTargets.cmake)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE ogl)

install(TARGETS ogl
        EXPORT oglTargets
        LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ogl
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
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ogl
        )

if(${OGL_EXAMPLE})
add_subdirectory(example)
endif()

