
find_package(glfw3 REQUIRED)

add_executable(ogl-example
  main.cpp
)

target_link_libraries(ogl-example ogl glfw)

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

