cmake_minimum_required(VERSION 3.10)

project(LexicalAnalyzer)

# Создаем статическую библиотеку из trie.cxx
add_library(lexical STATIC
    trie.cxx
    lexer.cxx
)

# Делаем директорию доступной для include
target_include_directories(lexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(
    TARGET lexical
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/KeyWords.txt
            ${CMAKE_BINARY_DIR}/KeyWords.txt
)
