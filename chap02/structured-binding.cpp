//  structured-binding.cpp
//  as of 2021-10-31 bw [bw.org]

#include <format>
#include <iostream>
#include <cstdint>
#include <string>
#include <array>
#include <map>

using std::string, std::array, std::map;
using std::cout, std::format;

// datum -----

struct things {
    int i{};
    char c{};
    long l{};
    string s{};
};

struct div_result {
    long quo;
    long rem;
};

// can't use size_t on MVSVC b/c it's 32-bits
map<string, uint64_t> inhabitants {
    { "humans",   7000000001 },
    { "pokemon", 17863376 },
    { "klingons",   24246291 },
    { "cats",    1086881528 }
};

// workers -----

div_result int_div(const long & num, const long & denom) {
    struct div_result r{};
    r.quo = num / denom;
    r.rem = num % denom;
    return r;
}

// I like commas
string make_commas(const uint64_t num) {
    string s{ std::to_string(num) };
    for(int l = s.length() - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

// main -----

int main() {
    array<int,5> nums { 1, 2, 3, 4, 5 };
    auto [ a, b, c, d, e ] = nums;
    cout << format("{} {} {} {} {}\n", a, b, c, d, e);

    auto [quo, rem] = int_div(47, 5);
    cout << format("quotient: {}, remainder {}\n", quo, rem);

    cout << "we got creatures --\n";
    for( const auto & [creature, pop] : inhabitants ) {
        cout << format("there are {} {}\n", 
            make_commas(pop), creature);
    }
}
