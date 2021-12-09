//  iterator-adapters.cpp
//  as of 2021-12-02 bw [bw.org]

#include <format>
#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using std::format;
using std::cout;
using std::cin;
using std::vector;
using std::deque;
using std::string_view;
using std::string;
using std::ostream_iterator;
using std::istream_iterator;

void printc(const auto & v, const string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    for(auto e : v) cout << format("{} ", e);
    cout << '\n';
}

int main() {
    deque<int> d1{ 1, 2, 3, 4, 5 };
    deque<int> d2(d1.size());

    copy(d1.begin(), d1.end(), d2.begin());
    printc(d1);
    printc(d2, "d2 after copy");

    copy(d1.begin(), d1.end(), back_inserter(d2));
    printc(d2, "d2 after back_inserter");

    deque<int> d3{ 47, 73, 114, 138, 54 };
    copy(d3.begin(), d3.end(), front_inserter(d2));
    printc(d2, "d2 after front_inserter");

    auto it2{ d2.begin() + 2};
    copy(d1.begin(), d1.end(), inserter(d2, it2));
    printc(d2, "d2 after middle insert");

    cout << "ostream_iterator: ";
    copy(d1.begin(), d1.end(), ostream_iterator<int>(cout));
    cout << '\n';

    vector<string> vs{};
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(vs));
    printc(vs, "vs2 from istream");

    cout << "Reverse iterator: ";
    for(auto it = d1.rbegin(); it != d1.rend(); ++it) {
        cout << format("{} ", *it);
    }
    cout << '\n';
}
