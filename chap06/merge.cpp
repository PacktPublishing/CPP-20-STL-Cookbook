//  merge.cpp
//  as of 2021-12-31 bw [bw.org]

#include <format>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

using std::format;
using std::cout;
using std::vector;
using std::sort;
using std::merge;
using std::back_inserter;
using std::string;
using std::string_view;

void printc(const auto& c, string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    for(auto e : c) cout << format("{} ", e);
    cout << '\n';
}

int main() {
    vector<string> vs1{ "dog", "cat", "velociraptor" };
    vector<string> vs2{ "kirk", "sulu", "spock" };
    vector<string> dest{};
    printc(vs1, "vs1");
    printc(vs2, "vs2");

    sort(vs1.begin(), vs1.end());
    sort(vs2.begin(), vs2.end());

    printc(vs1, "vs1 sorted");
    printc(vs2, "vs2 sorted");

    merge(vs1.begin(), vs1.end(), vs2.begin(), vs2.end(), back_inserter(dest));
    printc(dest, "dest");
}
