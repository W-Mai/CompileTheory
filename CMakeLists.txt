cmake_minimum_required(VERSION 3.17)
project(CompileTheory)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fexec-charset=gbk)
add_executable(CompileTheory main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h)