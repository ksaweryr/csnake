cmake_minimum_required(VERSION 3.12)

project(csnake CXX)

option(NO_TUI "Don't compile Renderer class" OFF)

if(NO_TUI)
	add_definitions(-DCSNAKE_NO_TUI)
endif()

add_library(${PROJECT_NAME} STATIC csnake.cpp)
