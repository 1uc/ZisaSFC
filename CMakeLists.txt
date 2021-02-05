cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ZisaSFC VERSION 0.1)

include("cmake/has_build_type.cmake")
include("cmake/warning_flags.cmake")
include("cmake/fast_debug.cmake")
include("cmake/sanitizers.cmake")
include("cmake/gperftools.cmake")
include("cmake/clang_tidy.cmake")

# -- Dependencies --------------------------------------------------------------
add_library(sfc_dependencies INTERFACE)

# experimental/filesystem
target_link_libraries(sfc_dependencies INTERFACE stdc++fs)

# Logging
if(ZISA_LOG_LEVEL)
  target_compile_definitions(sfc_dependencies INTERFACE ZISA_LOG_LEVEL=${ZISA_LOG_LEVEL})
endif()

# This component does not actually require MPI. However, the core header
# libraries depend on the value of `ZISA_HAS_MPI`.
if(ZISA_HAS_MPI)
  find_package(MPI REQUIRED COMPONENTS CXX)
  target_compile_definitions(sfc_dependencies INTERFACE ZISA_HAS_MPI=1)
endif()

# -- Zisa ----------------------------------------------------------------------
# -- core ----------------------------------------------------------------------
find_package(ZisaCore REQUIRED)

# -- sfc -----------------------------------------------------------------------
add_library(sfc STATIC "")
set_target_properties(sfc PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(sfc PROPERTIES OUTPUT_NAME zisa_sfc)
set_target_properties(sfc PROPERTIES CXX_STANDARD 17)
target_include_directories(sfc PUBLIC
  $<BUILD_INTERFACE:${ZisaSFC_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(sfc PUBLIC sfc_dependencies)
target_link_libraries(sfc PUBLIC Zisa::core)
target_link_libraries(sfc PRIVATE sfc_warning_flags)

# -- clang tidy ----------------------------------------------------------------
if(CLANG_TIDY_EXE)
  set_target_properties(sfc PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()

# -- install -------------------------------------------------------------------
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ZisaSFCConfigVersion.cmake"
  VERSION ${ZisaSFC_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
  "cmake/ZisaSFCConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/ZisaSFCConfigVersion.cmake"
  DESTINATION lib/cmake/zisa
)

add_library(Zisa::sfc ALIAS sfc)
install(
  TARGETS sfc sfc_dependencies sfc_warning_flags
  EXPORT ZisaSFCTargets
)
include(GNUInstallDirs)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ZisaSFCTargets
  FILE ZisaSFCTargets.cmake
  NAMESPACE Zisa::
  DESTINATION lib/cmake/zisa
)


# -- Tests ---------------------------------------------------------------------
find_package(Catch2 REQUIRED)

add_executable(sfc_unit_tests "")
set_target_properties(sfc_unit_tests PROPERTIES OUTPUT_NAME unit_tests)
set_target_properties(sfc_unit_tests PROPERTIES CXX_STANDARD 17)
target_include_directories(sfc_unit_tests PUBLIC test)
target_link_libraries(sfc_unit_tests PUBLIC Zisa::sfc Catch2::Catch2)

enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)

# -- Subdirectories ------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(test)
