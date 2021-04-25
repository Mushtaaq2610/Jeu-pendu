cmake_minimum_required(VERSION 3.16.3)
project(pendu)

include_directories(../include)
set(SOURCES src/main.c
	     src/dico.c)
add_executable(pendu ${SOURCES})
