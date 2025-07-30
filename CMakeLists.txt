cmake_minimum_required(VERSION 3.10)
project(condot)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(source_dir ${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
  ${source_dir}/main.cpp

  ${source_dir}/asset_manager.hpp
  ${source_dir}/asset_manager.cpp

  ${source_dir}/button.hpp
  ${source_dir}/button.cpp

  ${source_dir}/card.hpp
  ${source_dir}/card.cpp

  ${source_dir}/customization_menu.hpp
  ${source_dir}/customization_menu.cpp

  ${source_dir}/entity.hpp

  ${source_dir}/event.hpp
  ${source_dir}/event.cpp

  ${source_dir}/file_stream.hpp
  ${source_dir}/file_stream.cpp

  ${source_dir}/game.hpp
  ${source_dir}/game.cpp

  ${source_dir}/help_menu.hpp
  ${source_dir}/help_menu.cpp

  ${source_dir}/input.hpp
  ${source_dir}/input.cpp

  ${source_dir}/main_menu.hpp
  ${source_dir}/main_menu.cpp

  ${source_dir}/map.hpp
  ${source_dir}/map.cpp

  ${source_dir}/mercenary.hpp
  ${source_dir}/mercenary.cpp

  ${source_dir}/pause_menu.hpp
  ${source_dir}/pause_menu.cpp

  ${source_dir}/player.hpp
  ${source_dir}/player.cpp

  ${source_dir}/region.hpp
  ${source_dir}/region.cpp

  ${source_dir}/season.hpp

  ${source_dir}/state.hpp
  ${source_dir}/state.cpp

  ${source_dir}/status_bar.hpp
  ${source_dir}/status_bar.cpp

  ${source_dir}/stream.hpp
  ${source_dir}/stream.cpp

  ${source_dir}/timer.hpp
  ${source_dir}/timer.cpp
)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/libraylib.a)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/src
)
