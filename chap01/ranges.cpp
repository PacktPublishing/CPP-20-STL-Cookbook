// ranges.cpp
// as of 2021-10-27 bw [bw.org]

#include <iostream>
#include <vector>
#include <ranges>

namespace ranges = std::ranges;
namespace views = std::ranges::views;
using std::cout;

auto even = [](auto i) { return 0 == i % 2; };
auto times2 = [](auto i) { return i * 2; };

auto nl = [](){ cout << "\n"; };
auto printr = [](auto r) { for(auto e : r) cout << e << " "; nl(); };

int main() {
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printr(v | views::take(5));
    printr(v | views::reverse);
    printr(views::iota(100) | views::take(12) | views::reverse);
    printr(v | views::filter(even));
    printr(v | views::filter(even) | views::transform(times2));
}
