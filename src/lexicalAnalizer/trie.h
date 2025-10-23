#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <memory>

using std::vector;
using std::cout;
using std::ifstream;
using std::pair;
using std::string;

class Trie {
public:
    void addString(string &s);
    bool isExisted(string &s);

private:
    struct vertex {
        vertex* edges[26] = {0};
        bool isTerm = false;
    };

    vertex* root = new vertex();
};

void loadFromfile(std::ifstream& in, Trie B);
