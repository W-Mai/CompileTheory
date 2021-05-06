cmake_minimum_required(VERSION 3.17)
project(CompileTheory)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompileTheory main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h)