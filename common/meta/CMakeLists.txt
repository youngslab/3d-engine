

add_library(meta INTERFACE)

target_include_directories(meta INTERFACE ./include)
target_compile_features(meta INTERFACE cxx_std_17)

add_subdirectory(test)


