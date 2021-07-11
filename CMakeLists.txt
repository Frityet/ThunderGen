CMAKE_MINIMUM_REQUIRED(VERSION 3.19)
PROJECT(ThunderGen C)

SET(CMAKE_C_STANDARD 99)


ADD_EXECUTABLE(ThunderGen
                main.c
                common.h    common.c
                manifest.h  manifest.c)

FIND_PACKAGE(json-c CONFIG REQUIRED)
TARGET_LINK_LIBRARIES(ThunderGen PRIVATE json-c::json-c)