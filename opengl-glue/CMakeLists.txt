list(APPEND OPENGL_GLUE_SOURCES 
  "glad.c"
)

add_library(opengl-glue SHARED ${OPENGL_GLUE_SOURCES})

target_include_directories(opengl-glue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(opengl-glue PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(opengl-glue PRIVATE /usr/local/include)

