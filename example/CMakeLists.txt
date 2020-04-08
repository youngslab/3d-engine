
find_package(glfw3 QUIET)
if(NOT ${glfw3_FOUND})
  find_package(glfw REQUIRED)
endif()
if(NOT TARGET glfw::glfw)
  add_library(glfw::glfw INTERFACE IMPORTED)
  target_link_libraries(glfw::glfw INTERFACE glfw3)
endif()

find_package(fmt REQUIRED)

add_executable(ogl-example
  main.cpp
)

target_link_libraries(ogl-example ogl glfw::glfw fmt::fmt)

set(fragment_shader coordinate.fs)
set(vertex_shader   coordinate.vs)

set(shader_files
  res/shader/${fragment_shader}
  res/shader/${vertex_shader}
)

set(image_files
  res/image/container.jpg
  res/image/awesomeface.png
)

file(COPY ${shader_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/shader)

file(COPY ${image_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/image)

