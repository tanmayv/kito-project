# CMakeList.txt : CMake project for kito-project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)

project ("kito-project")

set(FREETYPE_ROOT "C:\\Users\\macpc\\Downloads\\freetype-2.12.1.tar\\freetype-2.12.1")
find_package(OpenGL REQUIRED)
set(FREETYPE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
find_package(Freetype REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
add_subdirectory(lib/glfw)
add_subdirectory(lib/fmt)
add_subdirectory(lib/glm)
add_executable (kito-project 
	"src/kito_project.cpp"
	"src/game_loop.cc"
	"src/glfw/glfw_platform.cc"
	"src/opengl/glad.c" 
	"src/opengl/resource_manager.cpp"
	"src/opengl/shader.cpp"
	"src/opengl/text_renderer.cc"
	"src/sudoku/scenes/main_menu.cc"
	"src/sudoku/main.cc"
	"src/opengl/texture.cc" 
	"src/scene/scene_node.cc" 
	"src/scene/scene.cc" 
	"src/math/matrix_stack.cc"
	"src/scene/root_node.cc"
	"src/scene/camera_node.cc" "src/render/renderer_interface.h" "src/global.h")
target_link_libraries(kito-project fmt glfw glm::glm ${OPENGL_LIBRARIES} Freetype::Freetype)
add_custom_command(TARGET kito-project POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/res
	${PROJECT_BINARY_DIR}/res
	COMMENT "Copying resources into binary directory")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET kito-project PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
