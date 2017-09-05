cmake_minimum_required(VERSION 2.8)

project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES
    "main.cpp"
    "Token.hpp"
    "Token.cpp"
    "CodeReader.hpp"
    "FileCodeReader.hpp"
    "FileCodeReader.cpp"
    "TokenCategory.hpp"
    "LexicalTable.hpp"
    "LexicalTable.cpp"
    "LexicalAnalyzer.hpp"
    "LexicalAnalyzer.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
