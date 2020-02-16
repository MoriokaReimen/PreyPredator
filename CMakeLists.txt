# Cmake file to build the application

cmake_minimum_required (VERSION 2.6)
project (Tank)

# I guess you have not released the project yet :p
set (Tank_VERSION_MAJOR 0)
set (Tank_VERSION_MINOR 1)
set (Tank_VERSION_PATCH 0)

set (EXECUTABLE_NAME "Tank")

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -coverage")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 ")

##################################
# install GoogleTest
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.8.1.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(googletest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(gtest_main IMPORTED STATIC GLOBAL)
add_dependencies(gtest_main googletest)

# Set libgtest properties
set_target_properties(gtest_main PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest_main.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgtest target to be used as a dependency by test programs
add_library(gtest IMPORTED STATIC GLOBAL)
add_dependencies(gtest googletest)

# Set libgtest properties
set_target_properties(gtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(gmock_main IMPORTED STATIC GLOBAL)
add_dependencies(gmock_main googletest)

# Set libgmock properties
set_target_properties(gmock_main PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(gmock IMPORTED STATIC GLOBAL)
add_dependencies(gmock googletest)

# Set libgmock properties
set_target_properties(gmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

##################################
# set project include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Logic ${source_dir}/include)

##################################
# Logic
file(GLOB_RECURSE LOGIC_SRC Logic/*.cpp)
add_library(Logic ${LOGIC_SRC})

##################################
# Define a test
# file(GLOB_RECURSE TEST_SRC test/*.cpp)
# add_executable(test_all ${TEST_SRC})
# target_link_libraries(test_all gtest_main gtest gmock engines pthread utilities items characters irrxml ${SFML_LIBRARIES} )
# target_include_directories(test_all PUBLIC ${TEST_DIR} ${source_dir}/include)

##################################
# Just make the test runnable with
#   $ make test
# enable_testing()
# add_test(NAME test COMMAND test_all)
