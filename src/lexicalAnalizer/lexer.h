#pragma once
#include "trie.h"

using std::isalpha;
using std::isalnum;
using std::isdigit;
using std::find;

const enum class Types { Keyword, Identificator, Literal, Operation, Punctuation, ELSE, END };

const vector <char> simple_oper = { '+', '*', '/', '=', '-', '!', '<', '>', '&', '|', '%', '^', '[', ']', '.' };
const vector <string> compound_oper = { "++", "--", "==", ">=", "<=", "!=", "||", "&&", "^=", "&=", "|=", "*=" };

pair<Types, string> get_lexem(const char*& current, const char* end, Trie& trie) {
    Types type = Types::Keyword;
    for (; current < end;) {
        string res = "";
        if (*current == ' ' or *current == '\n' or *current == '\r' or *current == '\t') {
            ++current;
            continue;
        }
        else if (*current == '/') {
            ++current;
            if (current < end and *current == '=') {
                type = Types::Operation;
                res += *(current++);
            }
            else if (current < end and *current == '*') {
                ++current;
                while (current < end) {
                    if (*(current++) == '*' and *current == '/') {
                        ++current;
                        break;
                    }
                }
                continue;
            }
            else if (current < end and *current == '/') {
                ++current;
                while (current < end and *(current++) != '\n') {}
                continue;
            }
            else {
                type = Types::Operation;
                res += '/';
            }
        }
        else if (isalpha(*current) or *current == '_') {
            res += (*(current++));
            while (current < end and (isalnum(*current) or *current == '_')) {
                res += (*(current++));
            }
            if (trie.isExisted(res)) {
                type = Types::Keyword;
            }
            else type = Types::Identificator;
        }
        else if (isdigit(*current)) {
            while (current < end and isdigit(*current)) {
                res += (*(current++));
            }
            if (current < end and *current == '.') {
                ++current;
                res += '.';
                while (current < end and isdigit(*current)) {
                    res += (*(current++));
                }
            }
            if (res[res.size() - 1] == '.') {
                type = Types::ELSE;
            }
            else type = Types::Literal;
        }
        else if (*current == ',' or *current == ';' or *current == '(' or *current == ')' or *current == '{' or *current == '}') {
            res += *current;
            type = Types::Punctuation;
            ++current;
        }
        else if (*current == '\0') {
            type = Types::Literal;
            res += *(current++);
        }
        else if (*current == '"') {
            res += *(current++);
            while (current < end and *current != '"') {
                res += *(current++);
            }
            if (current < end) {
                res += *(current++);
                type = Types::Literal;
            }
            else {
                type = Types::ELSE;
            }
        }
        else if (*current == '\'') {
            res += *(current++);
            while (current < end and *current != '\'') {
                res += *(current++);
            }
            if (current < end) {
                res += *(current++);
                type = Types::Literal;
            }
            else {
                type = Types::ELSE;
            }
        }
        else if (find(simple_oper.begin(), simple_oper.end(), *current) != simple_oper.end()) {
            res += *current;
            type = Types::Operation;
            ++current;
            if (current < end) {
                if (find(compound_oper.begin(), compound_oper.end(), res + *current) != compound_oper.end()) {
                    res += *(current++);
                }
            }
        }
        else if (*current == '\\') {
            type = Types::Literal;
            res += *(current++);
        }
        return { type, res };
    }
    return { Types::END, "" };
}