# CMakeList.txt : CMake project for kito-project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("kito-project")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
add_subdirectory(lib/glfw)
add_subdirectory(lib/fmt)
add_subdirectory(lib/glm)
add_executable (kito-project "src/kito-project.cpp" "src/glad.c" "src/shader.h" "src/shader.cpp")
target_link_libraries(kito-project fmt glfw glm::glm ${OPENGL_LIBRARIES})
add_custom_command(TARGET kito-project POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/res
	${PROJECT_BINARY_DIR}/res
	COMMENT "Copying resources into binary directory")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET kito-project PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
