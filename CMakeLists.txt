cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(allocator_cli VERSION ${PROJECT_VERSION})

add_executable(allocator_cli main.cpp)

set_target_properties(allocator_cli  PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON) 

#target_include_directories(allocator
#    PRIVATE "${CMAKE_BINARY_DIR}")

#set_target_properties(test_version PROPERTIES
#INCLUDE_DIRECTORIES ${gtest_SOURCE_DIR})

#target_link_libraries(allocator_cli PRIVATE allocator)
#target_link_libraries(test_version ${gtest_LIBRARIES} allocator gtest gtest_main)

target_compile_options(allocator_cli PRIVATE
    -Wall -Wextra -pedantic -Werror  -Wno-unused-parameter) 
#target_compile_options(allocator PRIVATE
#    -Wall -Wextra -pedantic -Werror  -Wno-unused-parameter)
#target_compile_options(test_version PRIVATE
#    -Wall -Wextra -pedantic -Werror  -Wno-unused-parameter)

install(TARGETS allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT examle@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
