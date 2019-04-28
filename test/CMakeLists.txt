cmake_minimum_required(VERSION 3.6)
project(PPRINT)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)
endif()

# Disable deprecation for windows
if (WIN32)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()	

# PPRINT executable
file(GLOB PPRINT_TEST_SOURCES
"*.cpp"
"*.hpp"
"../include/pprint.hpp"
)
ADD_EXECUTABLE(PPRINT ${PPRINT_TEST_SOURCES})
INCLUDE_DIRECTORIES("../include" ".")
set_target_properties(PPRINT PROPERTIES OUTPUT_NAME tests)
set_property(TARGET PPRINT PROPERTY CXX_STANDARD 17)

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PPRINT)
