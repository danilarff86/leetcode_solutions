cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(leetcode-solutions LANGUAGES C CXX)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(CMAKE_CXX_STANDARD 11)

option(PROFILER "Enable profiler build" OFF)
if(PROFILER)
  add_definitions(-pg)
endif(PROFILER)

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

option(SANITIZER "Enable sanitizer" OFF)
if(SANITIZER)
  add_definitions(-fsanitize=address)
  add_definitions(-fsanitize=signed-integer-overflow)
  if(LINUX)
    add_definitions(-fno-omit-frame-pointer)
    add_definitions(-Wno-format-security)
    #add_definitions(-static-libasan)
  endif(LINUX)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=signed-integer-overflow")
endif(SANITIZER)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
               ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main
# targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we have to add them
# here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

file(GLOB SRC "./cppsolutions/*.h" "./cppsolutions/*.cpp")

add_executable(cpptests ${SRC})
target_link_libraries(cpptests gtest_main)
