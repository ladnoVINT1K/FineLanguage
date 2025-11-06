#include "lexer.h"

Lexer::Lexer(string file, Trie& trie) : trie_(trie){
    std::ifstream in_program("Program.txt", std::ios::binary);
    in_program.seekg(0, std::ios::end);
    int size_text = in_program.tellg();
    in_program.seekg(0, std::ios::beg);
    text_ = new char[size_text];
    in_program.read(text_, size_text);
    pos_ = text_;
    end_ = text_ + size_text;
}

Lexer::~Lexer() {}

pair<Types, string> Lexer::get_lexem() {
    Types type = Types::Keyword;
    for (; pos_ < end_;) {
        string res = "";
        if (*pos_ == ' ' or *pos_ == '\n' or *pos_ == '\r' or *pos_ == '\t') {
            ++pos_;
            continue;
        } else if (*pos_ == '/') {
            ++pos_;
            if (pos_ < end_ and *pos_ == '=') {
                type = Types::Operation;
                res += *(pos_++);
            } else if (pos_ < end_ and *pos_ == '*') {
                ++pos_;
                while (pos_ < end_) {
                    if (*(pos_++) == '*' and *pos_ == '/') {
                        ++pos_;
                        break;
                    }
                }
                continue;
            } else if (pos_ < end_ and *pos_ == '/') {
                ++pos_;
                while (pos_ < end_ and *(pos_++) != '\n') {}
                continue;
            } else {
                type = Types::Operation;
                res += '/';
            }
        } else if (isalpha(*pos_) or *pos_ == '_') {
            res += (*(pos_++));
            while (pos_ < end_ and (isalnum(*pos_) or *pos_ == '_')) {
                res += (*(pos_++));
            }
            if (res == "not" or res == "and" or res == "or") {
                type = Types::Operation;
            }else if (trie_.isExisted(res)) {
                type = Types::Keyword;
            } else type = Types::Identificator;
        } else if (isdigit(*pos_)) {
            while (pos_ < end_ and isdigit(*pos_)) {
                res += (*(pos_++));
            }
            if (pos_ < end_ and *pos_ == '.') {
                ++pos_;
                res += '.';
                while (pos_ < end_ and isdigit(*pos_)) {
                    res += (*(pos_++));
                }
            }
            if (res[res.size() - 1] == '.') {
                type = Types::ELSE;
            } else type = Types::Literal;
        } else if (*pos_ == ',' or *pos_ == ';' or *pos_ == '(' or *pos_ == ')' or *pos_ == '{' or *pos_ == '}' or *pos_ == '<' or *pos_ == '>') {
            res += *pos_;
            type = Types::Punctuation;
            ++pos_;
        } else if (*pos_ == '\0') {
            type = Types::Literal;
            res += *(pos_++);
        } else if (*pos_ == '"') {
            res += *(pos_++);
            while (pos_ < end_ and *pos_ != '"') {
                res += *(pos_++);
            }
            if (pos_ < end_) {
                res += *(pos_++);
                type = Types::Literal;
            } else {
                type = Types::ELSE;
            }
        } else if (*pos_ == '\'') {
            res += *(pos_++);
            while (pos_ < end_ and *pos_ != '\'') {
                res += *(pos_++);
            }
            if (pos_ < end_) {
                res += *(pos_++);
                type = Types::Literal;
            } else {
                type = Types::ELSE;
            }
        } else if (find(simple_oper.begin(), simple_oper.end(), *pos_) != simple_oper.end()) {
            res += *pos_;
            type = Types::Operation;
            ++pos_;
            if (pos_ < end_) {
                if (find(compound_oper.begin(), compound_oper.end(), res + *pos_) != compound_oper.end()) {
                    res += *(pos_++);
                }
            }
        } else if (*pos_ == '\\') {
            type = Types::Literal;
            res += *(pos_++);
        }
        return { type, res };
    }
    return { Types::END, "" };
}

string type_to_string(Types type) {
    if (type == Types::Keyword) return "Keyword";
    else if (type == Types::Identificator) return "Identificator";
    else if (type == Types::Literal) return "Literal";
    else if (type == Types::Operation) return "Operation";
    else if (type == Types::Punctuation) return "Punctuation";
    else return "ELSE";
}