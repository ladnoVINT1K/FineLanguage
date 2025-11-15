#pragma once
#include "tf.h"
#include <iostream>

string typeToStr(TypeInfo t) {
    string r;
    if (t.type_ == base::Int) r = "int";
    if (t.type_ == base::Float) r = "float";
    if (t.type_ == base::Char) r = "char";
    if (t.type_ == base::Let) r = "let";
    for (int i = 0; i < t.arrayDepth_; ++i) r = "massive<" + r;
    for (int i = 0; i < t.arrayDepth_; ++i) r += ">";
    return r;
}
// в деку передаем параметры как мн-во листов: {type_, depth}
TypeInfo TF::check_call(string name, deque<TypeInfo> params) {
    string lcl = name;
    for (auto i : params) {
        lcl += typeToStr(i);
    }

    for (auto i : table_) {
        if (i.localName == lcl) return i.res;
    }
    throw("There is no func with name" + name + " and this params");
}

void TF::new_func(string name, deque<TypeInfo> params, TypeInfo res) {
    try {
        check_call(name, params);
        return;
    } catch(string e) {
        if (e == "There is no func with name" + name + " and this params") {
            string lcl = name;
            for (auto i : params) {
                lcl += typeToStr(i);
            }
            table_.push_front({name, lcl, params, res});
        } else {
            throw(e);
        }
    }
}

int main() {
    TF t;
}