find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
list(APPEND EXAMPLE_SOURCES 
  "hello_triangle.cc"
)
list(APPEND EXAMPLE_LIBS 
  kito-engine
  opengl-glue
  glfw-glue
  OpenGL::GL
  glm::glm
)

add_executable(example ${EXAMPLE_SOURCES})

target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(example ${EXAMPLE_LIBS})
target_include_directories(example PRIVATE /usr/local/include)

