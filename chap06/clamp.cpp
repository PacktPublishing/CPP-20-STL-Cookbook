//  clamp.cpp
//  as of 2021-12-27 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using std::format;
using std::cout;
using std::string;
using std::string_view;
using std::vector;
using std::list;
using std::transform;
using std::clamp;

void printc(auto& c, string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    for(auto e : c) cout << format("{:>5} ", e);
    cout << '\n';
}

int main() {
    const auto il = { 0, -12, 2001, 4, 5, -14, 100, 200, 30000 };
    constexpr int ilow{0};
    constexpr int ihigh{500};

    vector<int> voi{ il };
    cout << "vector voi before:\n";
    printc(voi);

    cout << "vector voi after:\n";
    for(auto& e : voi) e = clamp(e, ilow, ihigh);
    printc(voi);

    list<int> loi{ il };
    cout << "list loi before:\n";
    printc(loi);

    transform(loi.begin(), loi.end(), loi.begin(), [=](auto e){ return clamp(e, ilow, ihigh); });
    cout << "list loi after:\n";
    printc(loi);
}
