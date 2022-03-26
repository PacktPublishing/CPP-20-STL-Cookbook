//  split.cpp
//  as of 2022-03-25 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

using std::format;
using std::cout;
using std::string;
using std::vector;

namespace bw {

    template<typename It, typename Oc, typename V, typename Pred>
    It split(It it, const It end_it, Oc& dest, const V& sep, Pred& f) {
        using SliceContainer = typename Oc::value_type;
        while(it != end_it) {
            SliceContainer dest_elm{};
            auto slice{ it };
            while(slice != end_it) {
                if(f(*slice, sep)) break;
                dest_elm.push_back(*slice++);
            }
            dest.push_back(dest_elm);
            if(slice == end_it) return end_it;
            it = ++slice;
        }
        return it;
    }

    constexpr auto eq = [](const auto& el, const auto& sep) {
        return el == sep;
    };

    template<typename It, typename Oc, typename V>
    It split(It it, const It end_it, Oc& dest, const V& sep) {
        return split(it, end_it, dest, sep, eq);
    }

    template<typename Cin, typename Cout, typename V>
    Cout& strsplit(const Cin& str, Cout& dest, const V& sep) {
        split(str.begin(), str.end(), dest, sep, eq);
        return dest;
    }

};

int main() {
    constexpr char strsep{ ':' };
    const string str{ "sync:x:4:65534:sync:/bin:/bin/sync" };
    vector<string> dest_vs{};

    bw::split(str.begin(), str.end(), dest_vs, strsep, bw::eq);
    for(const auto& e : dest_vs) cout << format("[{}] ", e);
    cout << '\n';

    vector<string> dest_vs2{};
    bw::strsplit(str, dest_vs2, strsep);
    for(const auto& e : dest_vs2) cout << format("[{}] ", e);
    cout << '\n';

    constexpr int intsep{ -1 };
    vector<int> vi{ 1, 2, 3, 4, intsep, 5, 6, 7, 8, intsep, 9, 10, 11, 12 };
    vector<vector<int>> dest_vi{};
    bw::split(vi.begin(), vi.end(), dest_vi, intsep);
    for(const auto& v : dest_vi) {
        string s;
        for(const auto& e : v) s += format("{}", e);
        cout << format("[{}] ", s);
    }
    cout << '\n';
}
