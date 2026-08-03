# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(WIFI_NAME "$ENV{WIFI_NAME}")
set(WIFI_PASSWORD "$ENV{WIFI_PASSWORD}")

configure_file(
    ${CMAKE_SOURCE_DIR}/main/config.h.in
    ${CMAKE_SOURCE_DIR}/main/config.h
    @ONLY
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(bulbulator)
