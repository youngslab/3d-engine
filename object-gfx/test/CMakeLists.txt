

add_executable(ox-test main.cpp)

find_package(boost_type_index REQUIRED)

target_link_libraries(ox-test object-gfx
	boost_type_index::boost_type_index)
