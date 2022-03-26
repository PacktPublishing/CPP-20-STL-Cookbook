//  error-sum.cpp
//  as of 2022-03-19 bw [bw.org]

#include <format>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <numbers>

using std::format;
using std::cout;
using std::vector;
using std::inner_product;
using std::numbers::pi;

int main() {
    constexpr size_t vlen{ 100 };
    vector<double> ds(vlen);
    vector<int> is(vlen);
    size_t index{};

    // generate sine wave
    auto sin_gen = [&index]{ return 5.0 * sin(index++ * 2 * pi / 100); };
    for(auto& v : ds) v = sin_gen();

    // round to int and copy to is
    index = 0;
    for(auto& v : is) v = static_cast<int>(round(ds.at(index++)));

    // display ds
    for(const auto& v : ds) cout << format("{:-5.2f} ", v);
    cout << "\n\n";

    // display is
    for(const auto& v : is) cout << format("{:-3d} ", v);
    cout << "\n\n";

    // error sum
    double errsum = inner_product(ds.begin(), ds.end(), 
        is.begin(), 0.0, std::plus<double>(),
        [](double a, double b){ return pow(a - b, 2); });
    cout << format("error sum: {:.3f}\n\n", errsum);

    // accumulated error
    cout << "accumulated error:\n";
    for (auto it{ds.begin()}; it != ds.end(); ++it) {
        double accumsum = inner_product(ds.begin(), it, 
            is.begin(), 0.0, std::plus<double>(),
            [](double a, double b){ return pow(a - b, 2); });
        cout << format("{:-5.2f} ", accumsum);
    }
    cout << '\n';
}
