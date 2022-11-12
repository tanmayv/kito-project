# CMakeList.txt : CMake project for kito-project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("kito-project")

# Add source to this project's executable.
add_executable (kito-project "kito-project.cpp" "kito-project.h")
target_include_directories(kito-project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}lib/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET kito-project PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
