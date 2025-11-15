#pragma once
#include "tid.h"

TidTree::TidTree() {
    Global_ = new Tid;
    cur_ = Global_;
};

void TidTree::Create_Tid() {
    auto tmp = cur_;
    cur_ = new Tid;
    cur_->prev_ = tmp;
    tmp = nullptr;
}

bool TidTree::Check_id(string name) {
    auto tmp = cur_;
    while (tmp != nullptr) {
        for (ident id : tmp -> ids) {
            if (id.name == name) return true;
        }
        tmp = tmp->prev_;
    }
    return false;
}

void TidTree::Push_id(ident v) {
    string name = v.name;
    if (Check_id(name)) throw("[TID ERROR]: " + name + "is already existed");
    else {
        cur_->ids.push_back(v); 
    }
}

void TidTree::Del_Tid() {
    try {
        auto tmp = cur_;
        cur_ = cur_->prev_; // nullptr exception (dont try to remove global)
        delete tmp;
    } catch (std::exception& e) {
        std::cerr << "[TID ERROR]: " << e.what() << std::endl;
        throw(1); // не ловить! пусть бьет в main!! 
    }
}

TidTree::~TidTree() {
    while (cur_ != Global_) {
        auto tmp = cur_;
        cur_ = cur_->prev_;
        delete tmp;
    }
    delete Global_;
}