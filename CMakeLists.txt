cmake_minimum_required(VERSION 3.15)

project(source_location VERSION 1.0)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(source_location INTERFACE)
set_target_properties(source_location PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include>"
)
add_library(source_location::source_location ALIAS source_location)

# install the target and create export-set
install(TARGETS source_location EXPORT source_locationTargets)

# install header file
install(FILES include/source_location/source_location.hpp DESTINATION include/source_location)

# generate and install export file
install(EXPORT source_locationTargets
        FILE source_locationTargets.cmake
        NAMESPACE source_location::
        DESTINATION lib/cmake/source_location
)

option(BUILD_TESTS "Build the tests" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(BUILD_DOCS "Build docs" OFF)

if(BUILD_TESTS OR BUILD_DOCS)
  include(GetCMakeMM)
  cmmm(VERSION 2.2 REPOSITORY "flagarde/CMakeMM" DESTINATION "CMakeMM")
  cmmm_modules_list(REPOSITORY "flagarde/CMakeCM")
endif()

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfigVersion.cmake"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source_locationConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfig.cmake"
  INSTALL_DESTINATION lib/cmake/source_location
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/source_locationConfigVersion.cmake"
  DESTINATION lib/cmake/source_location
)

# generate the export targets for the build tree
export(EXPORT source_locationTargets
  FILE "${CMAKE_BINARY_DIR}/cmake/source_locationTargets.cmake"
  NAMESPACE source_location::
)

if(BUILD_DOCS)
  add_subdirectory(docs)
endif()

if(BUILD_TESTS)
  include(Doctest)
  add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
