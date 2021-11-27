#include "cell.hpp"
#include "url.hpp"
#include <iostream>

int main() {
    string input;
    getline(std::cin, input);
    URL link(input);
    link.print();
    return 0;
}
