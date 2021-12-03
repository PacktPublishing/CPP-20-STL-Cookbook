//  quick-delete.cpp
//  as of 2021-11-10 bw [bw.org]

#include <format>
#include <iostream>
#include <vector> 
#include <algorithm>

using std::format;
using std::cout;
using std::vector;
using std::move;
using std::ranges::find;

void printc(auto & r) {
    cout << format("size({}) ", r.size());
    for( auto & e : r ) cout << format("{} ", e);
    cout << "\n";
}

template<typename T>
void quick_delete(T& v, size_t idx) {
    if (idx < v.size()) {
        v[idx] = move(v.back());
        v.pop_back();
    }
}

template<typename T>
void quick_delete(T& v, typename T::iterator it) {
    if (it < v.end()) {
        *it = move(v.back());
        v.pop_back();
    }
}

int main() {
    vector v{ 12, 196, 47, 38, 19 };
    printc(v);
    auto it = find(v, 47);
    quick_delete(v, it);
    printc(v);
    quick_delete(v, 1);
    printc(v);
}

