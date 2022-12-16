find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
list(APPEND GLFW_GLUE_SOURCES 
  "src/glfw_window_manager.cc"
)

add_library(glfw-glue SHARED ${GLFW_GLUE_SOURCES})

target_link_libraries(glfw-glue glm::glm kito-common glfw)
target_include_directories(glfw-glue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glfw-glue PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

