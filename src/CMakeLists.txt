set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(APP_SRC
  App.cpp
  GIF.cpp
  Rope.cpp
  Serial.cpp
  Shape.cpp
  Vec2.cpp
  main.cpp
)

add_executable(rope-sim ${APP_SRC})
target_include_directories(rope-sim PRIVATE ../include)
target_link_libraries(rope-sim PRIVATE raylib)