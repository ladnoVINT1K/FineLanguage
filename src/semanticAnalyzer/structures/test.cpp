#include "iterationstack.cpp"

int main() {
    try {
        TypeStack A;
        A.push("true");
        A.push("and");
        A.push("!");
        A.push("false");
        A.check_uno();
        A.check_bin();
        std::cout << (A.pop().type_ == base::Bool);
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}