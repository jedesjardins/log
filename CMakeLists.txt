cmake_minimum_required(VERSION 3.12)
project(log)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LOG_BUILD_EXAMPLES "Build documentation examples" OFF)
option(LOG_BUILD_TESTS "Build documentation tests" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
	FetchContent_Populate(spdlog)
	message(STATUS "spdlog source dir: ${spdlog_SOURCE_DIR}")
	message(STATUS "spdlog binary dir: ${spdlog_BINARY_DIR}")
	message(STATUS "spdlog include dir: ${spdlog_SOURCE_DIR}/include")
endif()

add_library(Log INTERFACE)
target_include_directories(Log
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<BUILD_INTERFACE:${spdlog_SOURCE_DIR}/include>
)

target_link_libraries(Log INTERFACE
	Log
)

add_library(JED::log ALIAS Log)

if(GFX_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

if(GFX_BUILD_TESTS)
	add_subdirectory(tests)
endif()