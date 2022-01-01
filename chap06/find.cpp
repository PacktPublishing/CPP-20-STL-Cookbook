//  find.cpp
//  as of 2021-12-27 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>

using std::format;
using std::cout;
using std::string;
using std::string_view;
using std::vector;
using std::back_inserter;
using std::find;
using std::find_if;

namespace ranges = std::ranges;

struct City {
    string name{};
    unsigned pop{};
    bool operator==(const City& o) const {
        return name == o.name;
    }
    string str() const {
        return format("[{}, {}]", name, pop);
    }
};

int main() {
    const vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    cout << "find 7:\n";
    auto it1 = find(v.begin(), v.end(), 7);
    if(it1 != v.end()) cout << format("found: {}\n", *it1);
    else cout << "not found\n";

    const vector<City> c{
        { "London", 9425622 },
        { "Berlin", 3566791 },
        { "Tokyo",  37435191 },
        { "Cairo",  20485965 }
    };

    cout << "find Berlin:\n";
    auto it2 = find(c.begin(), c.end(), City("Berlin"));
    if(it2 != c.end()) cout << format("found: {}\n", it2->str());
    else cout << "not found\n";

    cout << "find pop > 20000000:\n";
    auto it3 = find_if(begin(c), end(c),
        [](const City& item) { return item.pop > 20000000; });
    if(it3 != c.end()) cout << format("found: {}\n", it3->str());
    else cout << "not found\n";

    cout << "views::filter pop > 20000000:\n";
    auto vw1 = ranges::views::filter(c, [](const City& c){ return c.pop > 20000000; });
    for(const City& e : vw1) cout << format("{}\n", e.str());
}
