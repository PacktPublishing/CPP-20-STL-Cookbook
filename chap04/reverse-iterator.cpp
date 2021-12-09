//  reverse-iterator.cpp
//  as of 2021-12-04 bw [bw.org]

#include <format>
#include <iostream>
#include <string_view>
#include <vector>
#include <iterator>
#include <list>

using std::format;
using std::cout;
using std::string_view;
using std::vector;


void printc(const auto & c, const string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    for(auto e : c) cout << format("{} ", e);
    cout << '\n';
}

void printr(const auto & c, const string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    auto it = std::rbegin(c);
    auto end_it = std::rend(c);
    while(it != end_it) {
        cout << format("{} ", *it++);
    }
    cout << '\n';
}

int main() {
    int array[]{ 1, 2, 3, 4, 5 };
    printc(array, "c-array");
    printr(array, "rev c-array");

    vector<int> v{ 1, 2, 3, 4, 5 };
    printc(v, "vector");
    printr(v, "rev vector");
}
