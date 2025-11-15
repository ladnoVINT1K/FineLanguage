#pragma once
#include <stack>
#include <string>
#include <exception>
#include <stdexcept>
#include <cctype>
#include <algorithm>

using std::exception;
using std::stack;
using std::string;

enum class base {
    Int, Float,
    Bool,
    Char, String, Void
};

enum class Oper {
    NumOper,   // +, -, *, /
    BoolOper,  // and, or
    Equal,     // ==, !=, <, >, <=, >=
    Unary      // любой унарный оп (пока так)
};

struct TypeInfo {
    TypeInfo(base t, int depth = 0) : type_(t), arrayDepth_(depth) {}

    base type_;
    int arrayDepth_ = 0;
    bool isArray() const { return arrayDepth_ > 0; }
};

// --- forward declaration --- //
class TidTree;

class TypeStack {
public:
    TypeStack() : typeStack_(), operStack_() {}
    ~TypeStack() = default;

    // --- main functions --- //
    void push(string lex);   
    TypeInfo pop();          
    void check_bin();
    void check_uno();
    bool check_if();

    void push(TypeInfo t) { typeStack_.push(t); }
private:
    stack<TypeInfo> typeStack_;
    stack<Oper> operStack_;

    void pushOp(Oper op) { operStack_.push(op); }

    Oper popop();
    TypeInfo poptype();
    TypeInfo topType() const;

    static bool isNumeric(base b) { return b == base::Int || b == base::Float; }
};
