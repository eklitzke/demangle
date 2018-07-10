cmake_minimum_required(VERSION 3.0)
project(demangle)
add_executable(demangle src/demangle.cc)
install (TARGETS demangle DESTINATION bin)
