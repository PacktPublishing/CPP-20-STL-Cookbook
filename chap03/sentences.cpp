//  sentences.cpp
//  as of 2021-11-23 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>

using std::format;
using std::cout;
using std::string;
using std::string_view;
using std::vector;
using std::ranges::sort;
using std::cin;
using std::unique_ptr;

bool is_eos(const string_view & str) {
    constexpr const char * end_punct{ ".!?" };
    for(auto c : str) {
        if(strchr(end_punct, c) != nullptr) return true;
    }
    return false;
}

int main() {
    vector<vector<string>> vv_sentences{vector<string>{}};

    for(string s{}; cin >> s; ) {
        vv_sentences.back().emplace_back(s);
        if(is_eos(s)) {
            vv_sentences.emplace_back(vector<string>{});
        }
    }

    // delete back if empty
    if(vv_sentences.back().empty()) vv_sentences.pop_back();

    sort(vv_sentences, [](const auto& l, const auto& r) {
            return l.size() > r.size();
        });

    constexpr int WLIMIT{10};
    for(auto& v : vv_sentences) {
        size_t size = v.size();
        size_t limit{WLIMIT};
        cout << format("{}: ", size);
        for(auto& s : v) {
            cout << format("{} ", s);
            if(--limit == 0) {
                if(size > WLIMIT) cout << "...";
                break;
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

