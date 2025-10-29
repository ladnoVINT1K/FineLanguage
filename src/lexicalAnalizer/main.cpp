#include "lexer.h"

int main() {
    try {

        std::ifstream in_program("Program.txt", std::ios::binary);
        in_program.seekg(0, std::ios::end);
        int size_text = in_program.tellg();
        in_program.seekg(0, std::ios::beg);
        char* text = new char[size_text];
        in_program.read(text, size_text);

        Trie trie;
        std::ifstream in_key("KeyWords.txt", std::ios::binary);
        loadFromfile(in_key, trie);

        const char* pos = text;
        pair<Types, string> res = get_lexem(pos, text + size_text, trie);
        while (res.first != Types::END) {
            cout << res.second << " ";
            if (res.first == Types::Keyword) cout << "Keyword";
            else if (res.first == Types::Identificator) cout << "Identificator";
            else if (res.first == Types::Literal) cout << "Literal";
            else if (res.first == Types::Operation) cout << "Operation";
            else if (res.first == Types::Punctuation) cout << "Punctuation";
            else cout << "ELSE";
            cout << '\n';
            res = get_lexem(pos, text + size_text, trie);
        }
    }
    catch (...) {
        std::cerr << "Trie error: No caps in programm";
    }
}