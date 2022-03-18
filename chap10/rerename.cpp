//  rerename.cpp
//  as of 2022-03-14 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <regex>
#include <filesystem>

using std::format;
using std::cout;
using std::string;
using std::vector;
using std::regex;

namespace fs = std::filesystem;
using dit = fs::directory_iterator;
using pat_v = vector<std::pair<regex, string>>;

template<>
struct std::formatter<fs::path>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) {
        return format_to(ctx.out(), "{}", p.string());
    }
};

string replace_str(string s, const pat_v& replacements) {
    for(const auto& [pattern, repl] : replacements) {
        s = regex_replace(s, pattern, repl);
    }
    return s;
}

int main(const int argc, const char** argv) {
    pat_v patterns{};

    if(argc < 3 || argc % 2 != 1) {
        fs::path cmdname{ fs::path{argv[0]}.filename() };
        cout << format("usage: {} [regex replacement] ...\n", cmdname);
        return 1;
    }

    for(int i{ 1 }; i < argc; i += 2) {
        patterns.emplace_back(argv[i], argv[i + 1]);
    }

    for(const auto& entry : dit{fs::current_path()}) {
        fs::path fpath{ entry.path() };
        string rname{ replace_str(fpath.filename().string(), patterns) };

        if(fpath.filename().string() != rname) {
            fs::path rpath{ fpath };
            rpath.replace_filename(rname);

            if(exists(rpath)) {
                cout << "Error: cannot rename - destination file exists.\n";
            } else {
                fs::rename(fpath, rpath);
                cout << format("{} -> {}\n", fpath.filename(), rpath.filename());
            }
        }
    }
}

