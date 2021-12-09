//  iterator-constraint.cpp
//  as of 2021-11-30 bw [bw.org]

#include <format>
#include <iostream>
#include <vector>
#include <list>

using std::format;
using std::list;
using std::vector;
using std::cout;

template<typename T>
requires std::random_access_iterator<typename T::iterator>
void printc(const T & c) {
        for(auto e : c) {
        cout << format("{} ", e);
    }
    cout << '\n';
    cout << format("element 0: {}\n", c[0]);
}

int main() {
    vector<int> c{ 1, 2, 3, 4, 5 };
    printc(c);       
}
