//  join.cpp
//  as of 2021-12-22 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <sstream>
#include <ranges>
#include <numbers>

using std::format;
using std::cout;
using std::ostream;
using std::string;
using std::string_view;
using std::ostringstream;
using std::vector;
using std::list;

namespace ranges = std::ranges;
namespace views = std::ranges::views;

namespace bw {
    template<typename I>
    ostream& join(I it, I end_it, ostream& o, string_view sep = "") {
        if(it != end_it) o << *it++;
        while(it != end_it) o << sep << *it++;
        return o;
    }

    template<typename I>
    string join(I it, I end_it, string_view sep = "") {
        ostringstream ostr;
        join(it, end_it, ostr, sep);
        return ostr.str();
    }

    string join(const auto& c, string_view sep = "") {
        return join(begin(c), end(c), sep);
    }
}

int main() {
    vector<string> greek{ "alpha", "beta", "gamma", "delta", "epsilon" };

    cout << "views::join: ";
    auto greek_view = views::join(greek);
    for(const char c : greek_view) cout << c;
    cout << '\n';

    cout << "bw::join (cout): ";
    bw::join(greek.begin(), greek.end(), cout, ", ") << '\n';

    cout << "bw::join (string): ";
    string s = bw::join(greek, ", ");
    cout << s << '\n';

    namespace num = std::numbers;
    cout << "bw::join (constants): ";
    list<double> constants { num::pi, num::e, num::sqrt2 };
    cout << bw::join(constants, ", ") << '\n';

    cout << "bw::join (greek_view): ";
    cout << bw::join(greek_view, ":") << '\n';
}
