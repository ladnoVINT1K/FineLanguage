#pragma once
#include <string>
#include <deque>

using std::deque;
using std::string;

enum class Typeof {Int, Float, Literal}; 

struct TFFrame {
    string name;
    string localName; // для перегрузок
    deque<Typeof> params;
    Typeof res;
};

class TF {
public:
    // --- constructors, destructors --- //
    TF();
    ~TF();

    // --- main functions --- //
    

private:
    deque<TFFrame> table_;
};