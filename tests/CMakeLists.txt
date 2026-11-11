include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Add one test file per module, e.g. test_caesar.cpp, test_aes.cpp ...
add_executable(cryptolab_tests
  test_smoke.cpp
  test_util.cpp
  test_shift.cpp
  test_affine.cpp
  test_vigenere.cpp
  test_playfair.cpp
  test_hill.cpp
  test_transposition.cpp
  test_break_classical.cpp
)
target_link_libraries(cryptolab_tests PRIVATE cryptolab::core GTest::gtest_main)
cryptolab_set_warnings(cryptolab_tests)
gtest_discover_tests(cryptolab_tests)
