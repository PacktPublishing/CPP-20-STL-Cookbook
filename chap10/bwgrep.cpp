//  bwgrep.cpp
//  as of 2022-03-14 bw [bw.org]

#include <format>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <filesystem>

using std::format;
using std::cout;
using std::string;
using std::vector;
using std::getline;
using std::regex;

namespace fs = std::filesystem;
using de = fs::directory_entry;
using rdit = fs::recursive_directory_iterator;
using match_v = vector<std::pair<size_t, std::string>>;

template<>
struct std::formatter<fs::path>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) {
        return format_to(ctx.out(), "{}", p.string());
    }
};

match_v matches(const fs::path& fpath, const regex& re) {
    match_v matches{};
    std::ifstream instrm(fpath.string(), std::ios_base::in);

    string s;
    for(size_t lineno{ 1 }; getline(instrm, s); ++lineno) {
        if(std::regex_search(s.begin(), s.end(), re)) {
            matches.emplace_back(lineno, move(s));
        }
    }
    return matches;
}

size_t pmatches(const regex& re, const fs::path& epath, const fs::path& search_path) {
    fs::path target{epath};
    auto regmatches{ matches(epath, re) };
    auto matchcount{ regmatches.size() };
    if(!matchcount) return 0;

    if(!(search_path == epath)) {
        target = epath.lexically_relative(search_path);
    }
    for (const auto& [lineno, line] : regmatches) {
        cout << format("{} {}: {}\n", target, lineno, line);
    }
    return regmatches.size();
}

int main(const int argc, const char** argv) {
    const char * arg_pat{};
    regex re{};
    fs::path search_path{};
    size_t matchcount{};

    if(argc < 2) {
        auto cmdname{ fs::path(argv[0]).filename() };
        cout << format("usage: {} pattern [path/file]\n", cmdname);
        return 1;
    }
    
    arg_pat = argv[1];
    try {
        re = regex(arg_pat, std::regex_constants::icase);
    } catch(const std::regex_error& e) {
        cout << format("{}: {}\n", e.what(), arg_pat);
        return 1;
    }

    if(argc == 2) {
        search_path = ".";
        for (const auto& entry : rdit{ search_path }) {
            const auto epath{ entry.path() };
            matchcount += pmatches(re, epath, search_path);
        }
    }

    int count{ argc - 2 };
    while(count-- > 0) {
        fs::path p{ argv[count + 2] };
        if(!exists(p)) {
            cout << format("not found: {}\n", p);
            continue;
        }
        if(is_directory(p)) {
            for (const auto& entry : rdit{ p }) {
                const auto epath{ entry.path() };
                matchcount += pmatches(re, epath, p);
            }
        } else {
            matchcount += pmatches(re, p, p);
        }
    }

    if(matchcount) {
        cout << format("found {} matches\n", matchcount);
    } else {
        cout << "no matches\n";
    }
}
