cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

find_package(PkgConfig REQUIRED)

project(bare_x11_xtest C)

pkg_check_modules(X11 REQUIRED IMPORTED_TARGET GLOBAL x11 xtst)

add_bare_module(bare_x11_xtest)

target_sources(
  ${bare_x11_xtest}
  PRIVATE
    binding.c
)

target_include_directories(
  ${bare_x11_xtest}
  PRIVATE
    node_modules/bare-x11/lib
)

target_link_libraries(
  ${bare_x11_xtest}
  PUBLIC
    PkgConfig::X11
)
