//  vector-access.cpp
//  as of 2021-11-29 bw [bw.org]

#include <format>
#include <iostream>
#include <vector> 

using std::format;
using std::cout;
using std::vector;

int main() {
    vector v{ 19, 71, 47, 192, 4004 };
    try {
        v.at(5) = 2001;
    } catch (const std::out_of_range & e) {
        std::cout << 
            format("Ouch!\n{}\n", e.what());
    }
    cout << format("end element is {}\n", v.back());
}

