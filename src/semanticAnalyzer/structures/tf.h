#pragma once
#include <string>
#include <deque>
#include "iterationstack.h"

using std::deque;
using std::string;

string typeToStr(TypeInfo t);

struct TFFrame {
    string name;
    string localName; // для перегрузок
    deque<TypeInfo> params;
    TypeInfo res;
};

class TF {
public:
    // --- constructors, destructors --- //
    TF() = default;
    ~TF() = default;

    // --- main functions --- //
    void new_func(string name, deque<TypeInfo> params, TypeInfo res);
    TypeInfo check_call(string name, deque<TypeInfo> params);

private:
    deque<TFFrame> table_;
};