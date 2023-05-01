cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

configure_file(version.h.in version.h)
add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON) 

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}")

set_target_properties(test_version PROPERTIES
INCLUDE_DIRECTORIES ${gtest_SOURCE_DIR})

target_link_libraries(helloworld_cli PRIVATE helloworld)
target_link_libraries(test_version ${gtest_LIBRARIES} helloworld gtest gtest_main)

target_compile_options(helloworld_cli PRIVATE
    -Wall -Wextra -pedantic -Werror) 
target_compile_options(helloworld PRIVATE
    -Wall -Wextra -pedantic -Werror)
target_compile_options(test_version PRIVATE
    -Wall -Wextra -pedantic -Werror)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT examle@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
