add_executable(example_98 example.cpp)
target_link_libraries(example_98 PRIVATE source_location)
target_compile_features(example_98 PRIVATE cxx_std_98)

add_executable(example_11 example.cpp)
target_link_libraries(example_11 PRIVATE source_location)
target_compile_features(example_11 PRIVATE cxx_std_11)

add_executable(example_17 example.cpp)
target_link_libraries(example_17 PRIVATE source_location)
target_compile_features(example_17 PRIVATE cxx_std_17)

add_executable(example_20 example.cpp)
target_link_libraries(example_20 PRIVATE source_location)
target_compile_features(example_20 PRIVATE cxx_std_20)

