#pragma once
#include "trie.h"

using std::isalpha;
using std::isalnum;
using std::isdigit;
using std::find;

const enum class Types { Keyword, Identificator, Literal, Operation, Punctuation, ELSE, END };

string type_to_string(Types type);

class Lexer {
public:
    Lexer(string file, Trie& trie);
    ~Lexer();
    pair<Types, string> get_lexem();
private:
    char* text_;
    char* pos_, * end_;
    Trie& trie_;
    const vector <char> simple_oper = { '+', '*', '/', '=', '-', '!', '<', '>', '&', '|', '%', '^', '[', ']', '.', '!'};
    const vector <string> compound_oper = { "==", ">=", "<=", "!=", "^=", "&=", "|=", "*=" };
};
