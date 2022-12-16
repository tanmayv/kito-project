find_package(glm REQUIRED)
add_library(kito-common INTERFACE)
target_link_libraries(kito-common INTERFACE glm::glm)
target_include_directories(kito-common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
