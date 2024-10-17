cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(EmbeddedTerminal LANGUAGES C)

add_subdirectory(libs/avr-extends)
add_subdirectory(src)