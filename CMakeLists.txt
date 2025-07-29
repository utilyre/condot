cmake_minimum_required(VERSION 3.30)
project(condot)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME})
add_subdirectory(./src)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/libraylib.a)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/src
)
