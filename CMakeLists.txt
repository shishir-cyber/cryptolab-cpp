cmake_minimum_required(VERSION 3.20)
project(cryptolab
  VERSION 0.0.1
  DESCRIPTION "Educational cryptography library, cryptanalysis lab and hybrid PQ messenger in C++"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

option(CRYPTOLAB_BUILD_TESTS "Build unit tests" ON)
option(CRYPTOLAB_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(CRYPTOLAB_BUILD_EXAMPLES "Build example programs" ON)
option(CRYPTOLAB_SANITIZE "Enable ASan + UBSan" OFF)

include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)

# ---- core library (educational implementations) ----
# Add new .cpp files to this list as each phase lands.
add_library(cryptolab_core
  src/version.cpp
  # Phase 1: classical ciphers
  src/classical/util.cpp
  src/classical/shift.cpp
  src/classical/affine.cpp
  src/classical/vigenere.cpp
  src/classical/playfair.cpp
  src/classical/hill.cpp
  src/classical/transposition.cpp
  # Phase 1: attacks on classical ciphers
  src/attacks/english.cpp
  src/attacks/break_classical.cpp
)
add_library(cryptolab::core ALIAS cryptolab_core)
target_include_directories(cryptolab_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(cryptolab_core PUBLIC cxx_std_20)
cryptolab_set_warnings(cryptolab_core)
cryptolab_enable_sanitizers(cryptolab_core)

if(CRYPTOLAB_BUILD_EXAMPLES)
  add_executable(classical_demo examples/classical_demo.cpp)
  target_link_libraries(classical_demo PRIVATE cryptolab::core)
  cryptolab_set_warnings(classical_demo)
endif()

if(CRYPTOLAB_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
