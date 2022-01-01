//  sort.cpp
//  as of 2021-12-24 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <random>

using std::format;
using std::cout;
using std::string;
using std::vector;

void randomize(auto& c) {
    static std::random_device rd;
    static std::default_random_engine rng(rd());
    std::shuffle(c.begin(), c.end(), rng);
}

void check_sorted(auto &c) {
    if(!is_sorted(c.begin(), c.end())) cout << "un";
    cout << "sorted: ";
}

void printc(const auto &c) {
    check_sorted(c);
    for(auto& e : c) cout << e << ' ';
    cout << '\n';
}

void print_things(const auto& c) {
    for (auto& v : c) cout << v.str() << ' ';
    cout << '\n';
}

struct things {
    string s_;
    int i_;

    string str() const {
        return format("({}, {})", s_, i_);
    }
};

int main() {
    vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printc(v);

    vector<things> vthings{ {"button", 40}, {"hamburger", 20},
        {"blog", 1000}, {"page", 100}, {"science", 60} };

    for(int i{3}; i; --i) {
        randomize(v);
        printc(v);
    }

    std::sort(v.begin(), v.end());
    printc(v);

    cout << "partial_sort:\n";
    randomize(v);
    auto middle{ v.begin() + (v.size() / 2) };
    std::partial_sort(v.begin(), middle, v.end());
    printc(v);

    cout << "partition:\n";
    randomize(v);
    printc(v);
    partition(v.begin(), v.end(), [](int i) { return i > 5; });
    printc(v);

    cout << "things:\n";
    std::sort(vthings.begin(), vthings.end(), 
            [](const things &lhs, const things &rhs) {
        return lhs.i_ < rhs.i_;
    });
    print_things(vthings);

    std::sort(vthings.begin(), vthings.end(), 
            [](const things &lhs, const things &rhs) {
        return lhs.s_ < rhs.s_;
    });
    print_things(vthings);
}
