set(SOURCES
  src/glad.c
)

set(INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Glad STATIC ${SOURCES})

target_include_directories(Glad PUBLIC ${INCLUDE_DIRECTORIES})

set_target_properties(Glad PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)