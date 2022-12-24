find_package(glm REQUIRED)
list(APPEND ENGINE_SOURCES
  game.cc
  game_loop.cc
  math/matrix_stack.cc
  scene/camera_node.cc
  scene/root_node.cc
  scene/scene.cc
  scene/scene_node.cc)

list(APPEND ENGINE_HEADERS 
  # "game.h"
)
list(APPEND ENGINE_LIBS 
  glm::glm kito-common
)
MESSAGE("GLM_FOUND ${GLM_FOUND}")
add_library(kito-engine SHARED ${ENGINE_SOURCES})

target_include_directories(kito-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(kito-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(kito-engine ${ENGINE_LIBS})
target_include_directories(kito-engine PRIVATE /usr/local/include)

install(TARGETS kito-engine DESTINATION /usr/local/lib)
install(FILES ${ENGINE_HEADERS} DESTINATION include)

