//  lambdas.cpp
//  as of 2021-12-18 bw [bw.org]

#include <format>
#include <iostream>
#include <string>

using std::format;
using std::cout;
using std::string;

int main() {
    auto one = []() -> const char * { return "one"; };
    auto two = []{ return "two"; };

    cout << "one and two:\n";
    cout << one() << '\n';
    cout << format("{}\n", two());

    auto p = [](auto v){ cout << v() << '\n'; };
    p([]{ return "lambda call lambda"; });

    cout << "anonymous lambda: ";
    cout << [](auto l, auto r){ return l + r; }(47, 73) << '\n';
    
    cout << "capture by reference: ";
    int num{0};
    auto inc = [&num]{ num++; };
    for (size_t i{0}; i < 5; ++i) {
        inc();
    }
    cout << num << '\n';

    cout << "counter: ";
    auto counter = [n = 0]() mutable { return ++n; };
    for (size_t i{0}; i < 5; ++i) {
        cout << format("{}, ", counter());
    }
    cout << '\n';

    int a{ 47 };
    int b{ 73 };
    auto l1 = [=]{ return a + b; };
    cout << format("default capture: {}\n", l1());
}
