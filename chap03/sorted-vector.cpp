//  sorted-vector.cpp
//  as of 2021-11-11 bw [bw.org]

#include <format>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::format;
using std::cout;
using std::vector;
using std::string;

namespace ranges = std::ranges;

using Vstr = std::vector<std::string>;
using Vint = std::vector<int>;

// print a vector
void printv(const auto& v) {
    for(const auto& e : v) {
        cout << format("{} ", e);
    }
    cout << "\n";
}

// is it sorted? 
void psorted(const auto& v) {
    if(ranges::is_sorted(v)) cout<< "sorted: ";
    else cout << "unsorted: ";
    printv(v);
}

// insert sorted elements
template<typename C, typename E>
void insert_sorted(C& c, const E& e)
{
    const auto pos{ ranges::lower_bound(c, e) };
    c.insert(pos, e);
}

int main() {
    Vstr v{ 
        "Miles",
        "Hendrix",
        "Beatles",
        "Zappa",
        "Shostakovich"
    };
    psorted(v);

    // sort it
    ranges::sort(v);
    psorted(v);

    // insert music here
    insert_sorted(v, "Ella");
    insert_sorted(v, "Stones");
    psorted(v);

    // once more with ints! 
    Vint vi{ 192, 47, 71, 1914, 2001 };
    psorted(vi);
    ranges::sort(vi);
    psorted(vi);
    insert_sorted(vi, 300);
    insert_sorted(vi, 1999);
    psorted(vi);
}
