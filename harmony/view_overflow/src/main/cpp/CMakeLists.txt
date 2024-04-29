cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB rnoh_view_overflow_SRC CONFIGURE_DEPENDS *.cpp)
add_library(rnoh_view_overflow SHARED ${rnoh_view_overflow_SRC})
target_include_directories(rnoh_view_overflow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rnoh_view_overflow PUBLIC rnoh)
