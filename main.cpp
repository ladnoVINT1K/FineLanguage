#include "src/lexicalAnalyzer/lexer.cxx"
#include "src/lexicalAnalyzer/trie.cxx"
#include "src/syntaxAnalyzer/syntaxer.cxx"

int main() {

    try {
        Trie trie;
        std::ifstream in_key("KeyWords.txt", std::ios::binary);
        loadFromfile(in_key, trie);
        Lexer lexer("Program.txt", trie);
        Syntaxer syntaxer(lexer);
        syntaxer.syntax();
    } catch (pair<Lexem, pair<Types, string>> error) {
        std::cerr << type_to_string(error.first.type) << " " << error.first.value << '\n'
            << "in line:" << error.first.line << " column:" << error.first.column << '\n'
            << "need " << type_to_string(error.second.first) << " " << error.second.second;
    } catch (pair<Lexem, Types> error) {
        std::cerr << type_to_string(error.first.type) << " " << error.first.value << '\n'
            << "in line:" << error.first.line << " column:" << error.first.column << '\n'
            << "need " << type_to_string(error.second);
    } catch (Lexem error) {
        std::cerr << "where type in line: " << error.line << " column:" << error.column; 
    }
}