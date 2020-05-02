
find_package(glfw3 QUIET)
if(NOT ${glfw3_FOUND})
  find_package(glfw REQUIRED)
endif()
if(NOT TARGET glfw::glfw)
  add_library(glfw::glfw INTERFACE IMPORTED)
  target_link_libraries(glfw::glfw INTERFACE glfw3)
endif()

add_subdirectory(object-gl-example)
# add_subdirectory(object-engine-example)
