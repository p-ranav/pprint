option(PPRINT_WERROR "Treat warnings as error")

add_executable(pprint_test
  main.cpp
  test_list.hpp
  test_set.hpp
  test_vector.hpp
)
target_link_libraries(pprint_test PUBLIC pprint)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(pprint_test PRIVATE /W4 $<$<BOOL:${PPRINT_WERROR}>:/WX>)
  target_compile_definitions(pprint_test PRIVATE _CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "(GNU)|(Clang)|(AppleClang)")
  target_compile_options(pprint_test PRIVATE -Wall $<$<BOOL:${PPRINT_WERROR}>:-Werror>)
else()
  message(AUTHOR_WARNING "Unsupported compiler. Please consider adding support at ${PROJECT_HOMEPAGE_URL}.")
endif()

find_package(Catch2 QUIET)
if(TARGET Catch2::Catch2)
  include(Catch)
  target_link_libraries(pprint_test PUBLIC Catch2::Catch2)
  catch_discover_tests(pprint_test)
else()
  target_include_directories(pprint_test PRIVATE external/catch/include)
  add_test(NAME pprint_test COMMAND pprint_test -s)
endif()

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY VS_STARTUP_PROJECT pprint_test)
