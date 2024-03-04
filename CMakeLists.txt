cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
#  It is used as your project's main executable name.
set(PROJECT_NAME WhateverGame)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too many problems for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS OFF)

#! Always use PVS Studio while developing.
set(ENABLE_PVS_STUDIO OFF)

#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of the Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan).
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
#  Info: https://clang.llvm.org/docs/ThreadSanitizer.html
set(ENABLE_TSan OFF)
#! MemorySanitizer -- detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-fsanitize=thread" COMPILER_SUPPORTS_TSAN)
if (COMPILER_SUPPORTS_TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no Thread Sanitizer support.")
endif()

##########################################################
# Preprocessor definitions
##########################################################

add_definitions(-DASIO_STANDALONE)

##########################################################
# Project files, packages, libraries and so on
##########################################################

#file(GLOB NETWORK_SOURCES source/network/*)
#file(GLOB_RECURSE SOURCES source/*.cpp)
#! Project main executable source compilation
#add_executable(${PROJECT_NAME} ${SOURCES})

#add_executable(Server source/server.cpp ${NETWORK_SOURCES})
#add_executable(Client source/client.cpp ${NETWORK_SOURCES})
add_executable(${PROJECT_NAME} source/main.cpp)

########
# SFML #
########
add_subdirectory(vendor/sfml)
# Link library to SFML privately.
#target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-system sfml-window)
#include_directories(${PROJECT_NAME} vendor/sfml/include)



########
# Asio #
########
include_directories(${PROJECT_NAME} vendor/asio/asio/include)
#include_directories(Server vendor/asio/asio/include)
#include_directories(Client vendor/asio/asio/include)

########################
# Tine process library #
########################
add_subdirectory(vendor/tiny-process-library)
target_link_libraries(${PROJECT_NAME} PRIVATE tiny-process-library)
include_directories(${PROJECT_NAME} vendor/tiny-process-library)

#target_link_libraries(Client PRIVATE tiny-process-library)
#include_directories(Client vendor/tiny-process-library)

##########################################################
# Fixed CMakeLists.txt part
##########################################################

INSTALL(PROGRAMS
        $<TARGET_FILE:${PROJECT_NAME}> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        #$<TARGET_FILE:Server>
        #<TARGET_FILE:Client>
        DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME})
#set(ALL_TARGETS Server Client)

# Include CMake setup
include(cmake/main-config.cmake)