include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_evidencia2 test_evidencia2.cpp)

target_link_libraries(test_evidencia2 gtest_main evidencia_lib)

add_test(NAME EvidenciaTests COMMAND test_evidencia2)
