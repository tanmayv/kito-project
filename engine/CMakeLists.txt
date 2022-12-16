list(APPEND ENGINE_SOURCES 
  "empty.cc"
)
list(APPEND ENGINE_HEADERS 
  "empty.h"
)
list(APPEND ENGINE_LIBS 
  kito-common
)

add_library(kito-engine SHARED ${ENGINE_SOURCES})

target_include_directories(kito-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(kito-engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(kito-engine ${ENGINE_LIBS})

install(TARGETS kito-engine DESTINATION /usr/lib)
install(FILES ${ENGINE_HEADERS} DESTINATION include)

