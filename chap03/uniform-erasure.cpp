//  uniform-erasure.cpp
//  as of 2021-11-10 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

using std::format;
using std::cout;
using std::string, std::vector, std::map, std::list;
using std::erase, std::erase_if;

void printc(auto& r) {
    cout << format("size: {}: ", r.size());
    for( auto& e : r ) cout << format("{} ", e);
    cout << "\n";
}

void print_assoc(auto& r) {
    cout << format("size: {}: ", r.size());
    for( auto& [k, v] : r ) cout << format("{}:{} ", k, v);
    cout << "\n";
}

int main() {
    {
        puts("initialize vector:");
        vector v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        printc(v);
        puts("erase 5:");
        erase(v, 5);
        printc(v);
    }

    {
        puts("initialize vector:");
        vector v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        printc(v);
        puts("erase_if even:");
        erase_if(v, [](auto x) { return x % 2 == 0; });
        printc(v);
    }

    puts("initialize map:");
    map<int, string> m{ {1, "uno"}, {2, "dos"}, {3, "tres"}, {4, "quatro"}, {5, "cinco"} };
    print_assoc(m);
    puts("erase_if even:");
    erase_if(m, [](auto& p) { auto& [k, v] = p; return k % 2 == 0; });
    print_assoc(m);
}

