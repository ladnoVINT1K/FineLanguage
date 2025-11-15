#pragma once
#include <iostream>
#include <deque>
#include "../../lexicalAnalyzer/lexer.h"
#include <string>

struct Tid{
    Types type;
    string name;
    string value;
};

class TidNode{
public:
    // --- constructors, destructors ---//
    TidNode();
    ~TidNode() = default;

    void add();
    void del();
    bool isExisted();

    TidNode* prev = nullptr;
private:
    Tid tid;
};

class TidTree{
public:
    // --- constructors, destructors --- // 
    TidTree();
    ~TidTree();

    // --- main functions --- //
    void Create_Tid();
    void Push_id();
    bool Check_id();
    void Del_Tid();

private:
    TidNode* Global;
    TidNode* cur;
};