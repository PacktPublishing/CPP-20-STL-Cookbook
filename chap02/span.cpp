//  span.cpp
//  as of 2021-10-28 bw [bw.org]

#include <format>
#include <iostream>
#include <span>

using std::format;
using std::cout;
using std::span;

template<typename T>
void pspan(span<T> s) {
    cout << format("number of elements: {}\n", s.size());
    cout << format("size of span: {}\n", s.size_bytes());
    for(auto e : s) cout << format("{} ", e);
    cout << "\n";
}

int main() {
    int ca1[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    pspan<int>(ca1);
    
    return 0;
}
