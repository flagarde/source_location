set(CXX_TEST "98;11;14")
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.8)
  set(CXX_TEST "${CXX_TEST}" "17")
endif()
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.12)
  set(CXX_TEST "${CXX_TEST}" "20")
endif()
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.20)
  set(CXX_TEST "${CXX_TEST}" "23")
endif()

foreach(STANDARD IN LISTS CXX_TEST)
  add_executable(example_${STANDARD} example.cpp)
  target_link_libraries(example_${STANDARD} PRIVATE source_location)
  set_target_properties(example_${STANDARD} PROPERTIES CXX_STANDARD ${STANDARD} CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
endforeach()
