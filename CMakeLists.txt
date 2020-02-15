cmake_minimum_required(VERSION 3.8)

if(DEFINED PROJECT_NAME)
  set(PPRINT_SUBPROJECT ON)
endif()

project(pprint VERSION 1.0.0 LANGUAGES CXX)
option(PPRINT_BUILD_TESTS OFF)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

add_library(pprint INTERFACE)
add_library(pprint::pprint ALIAS pprint)

target_compile_features(pprint INTERFACE cxx_std_17)
target_include_directories(pprint INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if(PPRINT_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

if(NOT PPRINT_SUBPROJECT)
  configure_file(pprint.pc.in pprint.pc @ONLY)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pprint.pc"
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  write_basic_package_version_file(pprintConfigVersion.cmake
                                   COMPATIBILITY AnyNewerVersion)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pprintConfigVersion.cmake
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pprint)
  install(TARGETS pprint EXPORT pprintConfig)
  install(EXPORT pprintConfig
          NAMESPACE pprint::
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pprint)
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/include/pprint.hpp
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pprint)
  install(FILES LICENSE
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/licenses/pprint)

  # Simple glob to regex conversion (.gitignore => CPACK_SOURCE_IGNORE_FILES)

  if(EXISTS ".gitignore")
    file(READ ".gitignore" DOT_GITIGNORE)
    string(REPLACE ";" "RANDOMSEQUENCE" DOT_GITIGNORE "${DOT_GITIGNORE}")
    string(REPLACE "\n" ";" DOT_GITIGNORE "${DOT_GITIGNORE}")
    string(REPLACE "RANDOMSEQUENCE" "\\;" DOT_GITIGNORE "${DOT_GITIGNORE}")
    foreach(IGNORE_LINE ${DOT_GITIGNORE})
      if(NOT IGNORE_LINE OR IGNORE_LINE MATCHES "^#")
        continue()
      endif()
      string(REPLACE "\\" "\\\\" IGNORE_LINE "${IGNORE_LINE}")
      string(REPLACE "." "\\\\." IGNORE_LINE "${IGNORE_LINE}")
      string(REPLACE "*" ".*" IGNORE_LINE "${IGNORE_LINE}")
      string(REPLACE "+" "\\\\+" IGNORE_LINE "${IGNORE_LINE}")
      list(APPEND CPACK_SOURCE_IGNORE_FILES "${IGNORE_LINE}")
    endforeach()
  endif()

  # extra ignored files
  list(APPEND CPACK_SOURCE_IGNORE_FILES
    .git
    .travis.yml
    .appveyor.yml
  )
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
  set(CPACK_GENERATOR "TGZ;TXZ")
  set(CPACK_SOURCE_GENERATOR "TGZ;TXZ")
  include(CPack)
endif()
