#pragma once
#include <iostream>
#include <deque>
#include "../../lexicalAnalyzer/lexer.h"
#include <string>
#include <vector>

struct ident {
    Types type;
    string name;
    string value;
};

struct Tid{
    vector<ident> ids;
    Tid* prev_ = nullptr;
};

class TidTree{
public:
    // --- constructors, destructors --- // 
    TidTree();
    ~TidTree();

    // --- main functions --- //
    void Create_Tid();
    void Push_id(ident v);
    bool Check_id(string name);
    void Del_Tid();

private:
    Tid* Global_;
    Tid* cur_;
};