#include "iterationstack.h"
#include <stdexcept>
#include <iostream>

Oper TypeStack::popop() {
    if (operStack_.empty())
        throw std::logic_error("oper stack underflow");
    Oper op = operStack_.top();
    operStack_.pop();
    return op;
}

TypeInfo TypeStack::poptype() {
    if (typeStack_.empty())
        throw std::logic_error("type stack underflow");
    TypeInfo t = typeStack_.top();
    typeStack_.pop();
    return t;
}

TypeInfo TypeStack::topType() const {
    if (typeStack_.empty())
        throw std::logic_error("type stack empty");
    return typeStack_.top();
}

TypeInfo TypeStack::pop() {
    return poptype();
}

static bool isFloatLit(const std::string& s) {
    bool dotSeen = false;
    bool leftDigit = false;
    bool rightDigit = false;

    for (char ch : s) {
        if (std::isdigit((unsigned char)ch)) {
            if (!dotSeen) leftDigit = true;
            else          rightDigit = true;
        } else if (ch == '.' && !dotSeen) {
            dotSeen = true;
        } else {
            return false; // ни цифра, ни первая точка -> не float
        }
    }

    return dotSeen && leftDigit && rightDigit;
}

// --- main functions --- //

void TypeStack::push(string lex) {
    // операторы

    if (lex == "+" || lex == "-" || lex == "*" || lex == "/") {
        pushOp(Oper::NumOper);
        return;
    }

    if (lex == "and" || lex == "or") {
        pushOp(Oper::BoolOper);
        return;
    }

    if (lex == "==" || lex == "!=" ||
        lex == "<"  || lex == ">"  ||
        lex == "<=" || lex == ">=") {
        pushOp(Oper::Equal);
        return;
    }

    if (lex == "not" or lex == "!") {
        // std::cout << "un";
        pushOp(Oper::Unary);
        return;
    }

    // УНАРНЫЙ "-" я бы НЕ обрабатывал через push(lex),
    // а в синтаксере явно делал: pushOp(Oper::Unary), потом check_uno();
    // иначе стек не поймет, унарный это "-" или бинарный и будет пиздец)

    // литералы
    if (lex == "true" || lex == "false") {
        typeStack_.push(TypeInfo(base::Bool));
        return;
    }
    // int
    if (!lex.empty() && std::all_of(lex.begin(), lex.end(),
                                    [](unsigned char c){ return std::isdigit(c); })) {
        typeStack_.push(TypeInfo(base::Int));
        return;
    }
    //float
    if (isFloatLit(lex)) {
        typeStack_.push(TypeInfo(base::Float));
        return;
    }

    typeStack_.push(TypeInfo(base::String));
}

void TypeStack::check_bin() {
    TypeInfo rhs = poptype();
    TypeInfo lhs = poptype();
    Oper op = popop();

    switch (op) {
    case Oper::NumOper:
        if (lhs.isArray() || rhs.isArray())
            throw std::logic_error("numeric op on array");

        if (!isNumeric(lhs.type_) || !isNumeric(rhs.type_))
            throw std::logic_error("numeric op requires Int/Float");

        if (lhs.type_ == base::Float || rhs.type_ == base::Float)
            typeStack_.push(TypeInfo(base::Float));
        else
            typeStack_.push(TypeInfo(base::Int));
        break;

    case Oper::BoolOper:
        if (lhs.isArray() || rhs.isArray())
            throw std::logic_error("bool op on array");

        if (lhs.type_ != base::Bool || rhs.type_ != base::Bool)
            throw std::logic_error("bool op requires Bool && Bool");

        typeStack_.push(TypeInfo(base::Bool));
        break;

    case Oper::Equal:
        if (lhs.isArray() || rhs.isArray()) {
            throw std::logic_error("equal op on array not supported");
        }

        if (lhs.type_ != rhs.type_) { // TODO: совместимость интов и флотов... шел бы ты своей дорогой... (мне лень)
            if (!(isNumeric(lhs.type_) && isNumeric(rhs.type_)))
                throw std::logic_error("cannot compare different non-numeric types");
        }

        typeStack_.push(TypeInfo(base::Bool));
        break;

    default:
        throw std::logic_error("unknown operator in check_bin");
    }
}

void TypeStack::check_uno() {
    TypeInfo t = poptype();
    Oper op = popop();

    if (op != Oper::Unary)
        throw std::logic_error("check_uno called for non-unary operator");

    if (t.isArray() ||
        (t.type_ != base::Bool &&
        t.type_ != base::Int  &&
        t.type_ != base::Float)) {
        throw std::logic_error("unary op requires Bool");
    }

    typeStack_.push(TypeInfo(base::Bool));
}

bool TypeStack::check_if() {
    TypeInfo t = topType();
    return (!t.isArray() && t.type_ == base::Bool) or t.type_ == base::Int or t.type_ == base::Float;
    // хочешь, напиши чтобы кидало ешки
}
