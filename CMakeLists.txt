cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDART 17)

project(BeQuietLanguage)

add_subdirectory(src/lexicalAnalyzer)
#add_subdirectory(src/syntaxAnalyzer)

add_executable(main.cpp)