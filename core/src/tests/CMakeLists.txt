enable_testing()
include(CTest)

if (WIN32)
    find_package(GTest REQUIRED)
else()
    set(GTEST_LOCATION /home/sergv/Documents/googletest)
    add_library(GTest::gtest STATIC IMPORTED)
    set_property(TARGET GTest::gtest PROPERTY IMPORTED_LOCATION "${GTEST_LOCATION}/lib/libgtest.a")
    set_property(TARGET GTest::gtest PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GTEST_LOCATION}/include")
    target_link_libraries(GTest::gtest INTERFACE pthread)
    add_library(GTest::gtest_main STATIC IMPORTED)
    set_property(TARGET GTest::gtest_main PROPERTY IMPORTED_LOCATION "${GTEST_LOCATION}/lib/libgtest_main.a")
    set_property(TARGET GTest::gtest_main PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GTEST_LOCATION}/include")
    add_library(GTest::gmock STATIC IMPORTED)
    set_property(TARGET GTest::gmock PROPERTY IMPORTED_LOCATION "${GTEST_LOCATION}/lib/libgmock.a")
    set_property(TARGET GTest::gmock PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GTEST_LOCATION}/include")
    add_library(GTest::gmock_main STATIC IMPORTED)
    set_property(TARGET GTest::gmock_main PROPERTY IMPORTED_LOCATION "${GTEST_LOCATION}/lib/libgmock_main.a")
    set_property(TARGET GTest::gmock_main PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GTEST_LOCATION}/include")
endif()

add_executable(zxing_test test.cpp)

if (NOT WIN32)
    target_compile_definitions(zxing_test PUBLIC -DGTEST_LANG_CXX11=0 -D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
endif()

target_link_libraries(
  zxing_test
  zxing
  GTest::gtest
  GTest::gtest_main
  GTest::gmock
  GTest::gmock_main
)

add_custom_target(copy_images ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/images
)

add_test(NAME test_zxing COMMAND zxing_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)

add_dependencies(zxing_test copy_images)
