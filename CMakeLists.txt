cmake_minimum_required(VERSION 3.16)

project(awtk-c-demos
  VERSION 1.0.0
  LANGUAGES C CXX
  DESCRIPTION "AWTK widget demos (C)"
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)

find_package(awtk CONFIG REQUIRED)

set(AWTK_C_DEMOS_AWTK_SOURCE "" CACHE PATH
  "AWTK source tree; used by update_res.py when res/assets.inc is missing")

if(NOT AWTK_C_DEMOS_AWTK_SOURCE)
  foreach(_awtk_source_candidate IN ITEMS
      "${CMAKE_CURRENT_SOURCE_DIR}/../awtk"
      "${CMAKE_CURRENT_SOURCE_DIR}/../../awtk")
    if(EXISTS "${_awtk_source_candidate}/scripts/update_res_app.py")
      set(AWTK_C_DEMOS_AWTK_SOURCE "${_awtk_source_candidate}" CACHE PATH
        "AWTK source tree" FORCE)
      break()
    endif()
  endforeach()
endif()

set(_awtk_c_demos_assets_inc "${CMAKE_CURRENT_SOURCE_DIR}/res/assets.inc")
if(AWTK_C_DEMOS_AWTK_SOURCE AND NOT EXISTS "${_awtk_c_demos_assets_inc}")
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  add_custom_command(
    OUTPUT "${_awtk_c_demos_assets_inc}"
    COMMAND ${Python3_EXECUTABLE}
      "${CMAKE_CURRENT_SOURCE_DIR}/scripts/update_res.py"
      all
      "--awtk_root=${AWTK_C_DEMOS_AWTK_SOURCE}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Generating AWTK resources for awtk-c-demos"
    VERBATIM
  )
  add_custom_target(awtk_c_demos_update_res DEPENDS "${_awtk_c_demos_assets_inc}")
endif()

if(NOT EXISTS "${_awtk_c_demos_assets_inc}" AND NOT AWTK_C_DEMOS_AWTK_SOURCE)
  message(FATAL_ERROR
    "res/assets.inc not found. Run: python ./scripts/update_res.py all\n"
    "Or set AWTK_C_DEMOS_AWTK_SOURCE to an AWTK source tree.")
endif()

option(AWTK_C_DEMOS_BUILD_DEMOS "Build demo programs" ON)

if(AWTK_C_DEMOS_BUILD_DEMOS)
  add_subdirectory(demos)
endif()
