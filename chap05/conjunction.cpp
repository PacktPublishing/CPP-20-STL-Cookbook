//  conjunction.cpp
//  as of 2021-12-20 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

using std::format;
using std::cout;
using std::string;
using std::cin;
using std::istream_iterator;
using std::ostream_iterator;

template <typename F, typename A, typename B>
auto combine(F binary_func, A a, B b) {
    return [=](auto param) {
        return binary_func(a(param), b(param));
    };
}

int main() {
    auto begins_with = [](const string &s){ return s.find("a") == 0; };
    auto ends_with = [](const string &s){ return s.rfind("b") == s.length() - 1; };
    auto bool_and = [](const auto& l, const auto& r){ return l && r; };

    std::copy_if(istream_iterator<string>{cin}, {},
                 ostream_iterator<string>{cout, " "},
                 combine(bool_and, begins_with, ends_with));

    std::cout << '\n';
}

