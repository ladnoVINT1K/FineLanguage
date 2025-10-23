#include <iostream>
#include <string>
#include <vector>
#include "trie.h"


using std::isalpha;
using std::isalnum;
using std::isdigit;
using std::cout;
using std::find;

Trie trie;
char* text = nullptr;
int size_text = 0;

const enum class Types { Keyword, Identificator, Literal, Operation, Punctuation, ELSE};

const std::vector <char> simple_oper = {'+', '*', '/', '=', '-', '!', '<', '>', '&', '|', '%', '^', '[', ']', '.'};
const std::vector <std::string> compound_oper = { "++", "--", "==", ">=", "<=", "!=", "||", "&&", "^=", "&=", "|=", "*="};
const std::vector <std::string> types = { "Keyword", "Identificator", "Literal", "Operation", "Punctuation", "ELSE"};

void Lexer() {
    Types type = Types::Keyword;
    for (char* current = text; current != text + size_text;) {
        std::string res = "";
        if (*current == ' ' or *current == '\n' or *current == '\r' or *current == '\t') {
            ++current;
            continue;
        } else if (*current == '/') {
            ++current;
            if (current != text + size_text and *current == '=') {
                type = Types::Operation;
                res += *(current++);
            } else if (current != text + size_text and *current == '*') {
                ++current;
                while (current != text + size_text) {
                    if (*(current++) == '*' and *current == '/') {
                        ++current;
                        break;
                    }
                }
                continue;
            } else if (current != text + size_text and *current == '/') {
                ++current;
                while (current != text + size_text and *(current++) != '\n') {}
                continue;
            } else {
                type = Types::Operation;
                res += '/';
            }
        } else if (isalpha(*current) or *current == '_') {
            res += (*(current++));
            while (current != text + size_text and (isalnum(*current) or *current == '_')) {
                res += (*(current++));
            }
            if (trie.isExisted(res)) {
                type = Types::Keyword;
            } else type = Types::Identificator;
        } else if (isdigit(*current)) {
            while (current != text + size_text and isdigit(*current)) {
                res += (*(current++));
            }
            if (current != text + size_text and *current == '.') {
                ++current;
                res += '.';
                while (current != text + size_text and isdigit(*current)) {
                    res += (*(current++));
                }
            }
            if (res[res.size() - 1] == '.') {
                type = Types::ELSE;
            } else type = Types::Literal;
        } else if (*current == ',' or *current == ';' or *current == '(' or *current == ')' or *current == '{' or *current == '}') {
            res += *current;
            Types::Punctuation;
            ++current;
        } else if (*current == '"') {
            res += *(current++);
            while (current != text + size_text and *current != '"') {
                res += *(current++);
            }
            if (current != text + size_text) {
                res += *(current++);
                type = Types::Literal;
            } else {
                type = Types::ELSE;
            }
        } else if (find(simple_oper.begin(), simple_oper.end(), *current) != simple_oper.end()) {
            res += *current;
            type = Types::Operation;
            ++current;
            if (current != text + size_text) {
                if (find(compound_oper.begin(), compound_oper.end(), res + *current) != compound_oper.end()) {
                    res += *(current++);
                }
            }
        }
        cout << res << " ";
        if (type == Types::Keyword) cout << "Keyword";
        else if (type == Types::Identificator) cout << "Identificator";
        else if (type == Types::Literal) cout << "Literal";
        else if (type == Types::Operation) cout << "Operation";
        else if (type == Types::Punctuation) cout << "Punctuation";
        else cout << "ELSE";
        cout << '\n';
    }
}

int main() {
    std::ifstream in_program("Program.txt", std::ios::binary);
    in_program.seekg(0, std::ios::end);
    size_text = in_program.tellg();
    in_program.seekg(0, std::ios::beg);
    text = new char[size_text];
    in_program.read(text, size_text);
    std::ifstream in_key("KeyWords.txt", std::ios::binary);
    loadFromfile(in_key, trie);
    Lexer();
}

