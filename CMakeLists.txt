project("QOI")

cmake_minimum_required(VERSION 3.18.1 FATAL_ERROR)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(MAX_PLUGIN_DIR
    ""
    CACHE STRING "Directory to copy 3ds Max plugins to after compilation")

find_package(MaxSDK REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(
  GLOB
  SRC
  *.cpp
  *.h
  *.def
  *.rc
  *.rc2
  qoi/qoi.h)
source_group("" FILES ${SRC})

add_library(qoi SHARED ${SRC})
if(MaxSDK_VERSION VERSION_GREATER 2019)
  set_target_properties(qoi PROPERTIES CXX_STANDARD 17)
else()
  set_target_properties(qoi PROPERTIES CXX_STANDARD 14)
endif()
set_target_properties(qoi PROPERTIES SUFFIX ".bmi")
target_link_libraries(qoi ${MaxSDK_LIBRARIES})
include_directories(${MaxSDK_INCLUDE_DIR} qoi)
add_definitions(${MaxSDK_DEFINITIONS})

if(MAX_PLUGIN_DIR)
  add_custom_command(
    TARGET qoi
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_BINARY_DIR}/bin/\$\(Configuration\)/qoi.bmi
      ${MAX_PLUGIN_DIR}/qoi.bmi)
  find_file(MAX_EXECUTABLE 3dsmax.exe PATHS ${MAX_PLUGIN_DIR}/..)
  set_target_properties(qoi PROPERTIES VS_DEBUGGER_COMMAND ${MAX_EXECUTABLE})
endif()

set(VS_STARTUP_PROJECT qoi)
