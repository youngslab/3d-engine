

add_library(object-gfx INTERFACE )

target_link_libraries(object-gfx INTERFACE meta)

target_include_directories(object-gfx INTERFACE ./include)

add_subdirectory(test)
