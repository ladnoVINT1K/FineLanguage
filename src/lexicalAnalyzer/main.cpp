#include "lexer.h"
#include "syntaxer.h"

int main() {

    try {
        Trie trie;
        std::ifstream in_key("KeyWords.txt", std::ios::binary);
        loadFromfile(in_key, trie);
        Lexer lexer("Program.txt", trie);
        Syntaxer syntaxer(lexer);
        syntaxer.syntax();
    } catch (string s) {
        std::cerr << s;
    } catch (Types t) {
        std::cerr << type_to_string(t);
    }
}