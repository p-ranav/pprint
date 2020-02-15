option(PPRINT_WERROR "Treat warnings as error")

if (MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(pprint_test
  main.cpp
  test_list.hpp
  test_set.hpp
  test_vector.hpp
  catch.hpp
)
target_link_libraries(pprint_test PUBLIC pprint)

if(MSVC)
  target_compile_options(pprint_test PRIVATE /W4 $<$<BOOL:${PPRINT_WERROR}>:/WX>)
else()
  target_compile_options(pprint_test PRIVATE -Wall $<$<BOOL:${PPRINT_WERROR}>:-Werror>)
endif()

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY VS_STARTUP_PROJECT pprint_test)
