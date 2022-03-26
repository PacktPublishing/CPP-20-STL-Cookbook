//  trie.cpp
//  as of 2022-03-25 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <optional>
#include <map>
#include <deque>

using std::format;
using std::cout;
using std::string;
using std::initializer_list;
using std::optional;

using ilcstr = initializer_list<const char *>;

namespace bw {
    using std::map;
    using std::deque;

    class trie {
        using get_t = deque<deque<string>>;
        using nodes_t = map<string, trie>;
        using result_t = optional<const trie*>;

        nodes_t nodes{};

        mutable get_t result_dq{};
        mutable deque<string> prefix_dq{};

        // private member functions

        template <typename It>
        void _insert(It it, It end_it) {
            if(it == end_it) return;
            nodes[*it]._insert(++it, end_it);
        }

        void _get(deque<string>& dq, get_t& r_dq) const {
            if(empty()) {
                r_dq.emplace_back(dq);
                dq.clear();
            }
            for(const auto& p : nodes) {
                dq.emplace_back(p.first);
                p.second._get(dq, r_dq);
            }
        }

        void _find_prefix(const string& s, auto& pre_dq) const {
            if(empty()) return;
            for(const auto& [k, v] : nodes) {
                if(k.starts_with(s)) {
                    pre_dq.emplace_back(k);
                    v._find_prefix(k, pre_dq);
                }
            }
        }

        template <typename It>
        result_t _search(It it, It end_it) const {
            if(it == end_it) return {this};
            auto found_it = nodes.find(*it);
            if(found_it == nodes.end()) return {};
            return found_it->second._search(++it, end_it);
        }

    public:
        void insert(const ilcstr& il) {
            _insert(il.begin(), il.end());
        }

        get_t& get() const {
            result_dq.clear();
            deque<string> dq{};
            _get(dq, result_dq);
            return result_dq;
        }

        result_t search(const ilcstr& il) const {
            return _search(il.begin(), il.end());
        }

        result_t search(const string& s) const {
            const ilcstr il{s.c_str()};
            return _search(il.begin(), il.end());
        }

        bool empty() const { return nodes.empty(); }

        const nodes_t& get_nodes() const { return nodes; }

        deque<string>& find_prefix(const char * s) const {
            _find_prefix(s, prefix_dq);
            return prefix_dq;
        }
    };
}

void print_trie_prefix(const bw::trie& t, const string& prefix) {
    auto& trie_strings = t.get();
    cout << format("results for \"{}...\":\n", prefix);
    for(auto& dq : trie_strings) {
        cout << format("{} ", prefix);
        for(const auto& s : dq) cout << format("{} ", s);
        cout << '\n';
    }
}

void print_trie_prefix(const bw::trie& t, const ilcstr& prefix) {
    string sprefix{};
    for(const auto& s : prefix) sprefix += format("{} ", s);
    print_trie_prefix(t, sprefix);
}

int main() {
    bw::trie ts{};
    ts.insert({ "all", "along", "the", "watchtower" });
    ts.insert({ "all", "you", "need", "is", "love" });
    ts.insert({ "all", "shook", "up" });
    ts.insert({ "all", "the", "best" });
    ts.insert({ "all", "the", "gold", "in", "california" });
    ts.insert({ "at", "last" });
    ts.insert({ "love", "the", "one", "you're", "with" });
    ts.insert({ "love", "me", "do" });
    ts.insert({ "love", "is", "the", "answer" });
    ts.insert({ "loving", "you" });
    ts.insert({ "long", "tall", "sally" });

    {
        const string prefix = { "love" };
        if (auto st = ts.search(prefix); st) {
            print_trie_prefix(**st, prefix);
        }
        cout << '\n';
    }

    {
        const auto prefix = { "all", "the" };
        if (auto st = ts.search(prefix); st) {
            print_trie_prefix(**st, prefix);
        }
        cout << '\n';
    }

    {
        const char * prefix{ "lo" };
        auto prefix_dq = ts.find_prefix(prefix);
        for(const auto& s : prefix_dq) {
            cout << format("match: {} -> {}\n", prefix, s);
            if (auto st = ts.search(s); st) {
                print_trie_prefix(**st, s);
            }
        }
        cout << '\n';
    }
}
