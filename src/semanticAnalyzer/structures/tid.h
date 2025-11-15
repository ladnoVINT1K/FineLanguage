#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <vector>

using std::string;
using std::vector;

enum class Typeof {Int, Float, Literal}; 

struct ident {
    Typeof type;
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