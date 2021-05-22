add_executable(test_98 test.cpp)
target_link_libraries(test_98 PRIVATE source_location)
target_compile_features(test_98 PRIVATE cxx_std_98)
add_test(NAME test_98 COMMAND test_98)

add_executable(test_11 test.cpp)
target_link_libraries(test_11 PRIVATE source_location)
target_compile_features(test_11 PRIVATE cxx_std_11)
add_test(NAME test_11 COMMAND test_11)

add_executable(test_17 test.cpp)
target_link_libraries(test_17 PRIVATE source_location)
target_compile_features(test_17 PRIVATE cxx_std_17)
add_test(NAME test_17 COMMAND test_17)

add_executable(test_20 test.cpp)
target_link_libraries(test_20 PRIVATE source_location)
target_compile_features(test_20 PRIVATE cxx_std_20)
add_test(NAME test_20 COMMAND test_20)

