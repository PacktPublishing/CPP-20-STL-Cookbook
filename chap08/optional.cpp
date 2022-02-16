//  optional.cpp
//  as of 2022-01-29 bw [bw.org]

#include <format>
#include <iostream>
#include <optional>

using std::format;
using std::cout;
using std::optional;

using oint = std::optional<int>;
using olong = std::optional<long>;

oint operator+(const oint& a, const oint& b) {
    if(a && b) return *a + *b;
    else return {};
}

oint operator+(const oint& a, const int b) {
    if(a) return *a + b;
    else return {};
}

olong factor(const olong& n) {
    if(!n) return {};
    for (long i = 2; i <= *n / 2; ++i) {
        if (*n % i == 0) return {i};
    }
    return {};
}

int main() {
    oint a{ 42 };
    oint b{ 73 };

    auto sum{ a + b };

    if(sum) {
        cout << format("{} + {} = {}\n", *a, *b, *sum);
    } else {
        cout << "NAN\n";
    }

    auto x = factor(a);
    auto y = factor(b);
    if(x) cout << format("lowest factor of {} is {}\n", *a, *x);
    else cout << format("{} is prime\n", *a);
    if(y) cout << format("lowest factor of {} is {}\n", *b, *y);
    else cout << format("{} is prime\n", *b);

    b.reset();
    try {
        cout << b.value() << '\n';
    } catch(const std::bad_optional_access& e) {
        cout << format("b.value(): {}\n", e.what());
    }
}
