//  delws.cpp
//  as of 2022-03-22 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <algorithm>

using std::format;
using std::cout;
using std::string;

namespace bw {

using std::unique;

template<typename T>
bool isws(const T& c) {
    constexpr const T whitespace[]{ " \t\r\n\v\f" };
    for(const T& wsc : whitespace) if(c == wsc) return true;
    return false;
}

string delws(const string& s) {
    string outstr{s};
    auto its = unique(outstr.begin(), outstr.end(),
        [](const auto &a, const auto &b) {
            return isws(a) && isws(b);
        });
    outstr.erase(its, outstr.end());
    outstr.shrink_to_fit();
    return outstr;
}

};

int main() {
    const string s{ "big     bad    \t   wolf" };
    const string s2{ bw::delws(s) };
    cout << format("[{}]\n", s);
    cout << format("[{}]\n", s2);
    return 0;
}
