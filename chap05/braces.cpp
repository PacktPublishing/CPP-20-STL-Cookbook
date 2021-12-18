//  braces.cpp
//  as of 2021-12-16 bw [bw.org]

#include <format>
#include <iostream>
#include <string>

using std::format;
using std::cout;

auto braces (const char a, const char b) {
    return [a, b](const auto v) {
        cout << format("{}{}{} ", a, v, b);
    };
}

int main() {
    auto a = braces('(', ')');
    auto b = braces('[', ']');
    auto c = braces('{', '}');
    auto d = braces('|', '|');

    for( int i : { 1, 2, 3, 4, 5 } ) {
        for( auto x : { a, b, c, d } ) x(i);
        cout << '\n';
    }
}
