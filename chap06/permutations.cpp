//  permutations.cpp
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
using std::string;
using std::string_view;
using std::next_permutation;

void printc(const auto& c, string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    for(auto e : c) cout << format("{} ", e);
    cout << '\n';
}

string numstr(const long i) {
    string ns{std::to_string(i)};
    auto it = ns.end();
    while(it > ns.begin()) {
        it -= 3;
        if(it > ns.begin()) ns.insert(it, ',');
    }
    return ns;
}

int main() {
    vector<string> vs{ "dog", "cat", "velociraptor" };
    sort(vs.begin(), vs.end());

    do {
        printc(vs);
    } while (next_permutation(vs.begin(), vs.end()));

    vector<int> vi{ 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
    sort(vi.begin(), vi.end());
    printc(vi, "vi sorted");
    long count{};
    do {
        ++count;
    } while (next_permutation(vi.begin(), vi.end()));
    cout << format("number of permutations: {}\n", numstr(count));
}
