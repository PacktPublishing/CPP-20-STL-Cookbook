//  dir-size.cpp
//  as of 2022-03-17 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <regex>
#include <filesystem>
#include <sstream>
#include <iomanip>

using std::format;
using std::cout;
using std::string;
using std::vector;
using std::regex;

namespace fs = std::filesystem;
using dit = fs::directory_iterator;
using de = fs::directory_entry;

template<>
struct std::formatter<fs::path>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) {
        return format_to(ctx.out(), "{}", p.string());
    }
};

string make_commas(const uintmax_t& num) {
    string s{ std::to_string(num) };
    for(long l = s.length() - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

// return a lowercase version of string s
string strlower(string s) {
    auto char_lower = [](const char& c) -> char {
        if(c >= 'A' && c <= 'Z') return c + ('a' - 'A');
        else return c;
    };
    std::transform(s.begin(), s.end(), s.begin(), char_lower);
    return s;
}

// compare directory_entry objects with strlower
bool dircmp_lc(const de& lhs, const de& rhs) {
    const auto lhstr{ lhs.path().string() };
    const auto rhstr{ rhs.path().string() };
    return strlower(lhstr) < strlower(rhstr);
}

string size_string(const uintmax_t fsize) {
    constexpr const uintmax_t kilo{ 1024 };
    constexpr const uintmax_t mega{ kilo * kilo };
    constexpr const uintmax_t giga{ mega * kilo };

    if(fsize >= giga ) return format("{}{}", (fsize + giga / 2) / giga, 'G');
    else if (fsize >= mega) return format("{}{}", (fsize + mega / 2) / mega, 'M');
    else if (fsize >= kilo) return format("{}{}", (fsize + kilo / 2) / kilo, 'K');
    else return format("{}B", fsize);
}

uintmax_t entry_size(const fs::path& p) {
    if(fs::is_regular_file(p)) return fs::file_size(p);

    uintmax_t accum{};
    if(fs::is_directory(p) && !fs::is_symlink(p)) {
        for(auto& e : dit{ p }) {
            accum += entry_size(e.path());
        }
    }
    return accum;
}

int main(const int argc, const char** argv) {
    auto dir{ argc > 1 ? fs::path(argv[1]) : fs::current_path() };
    vector<de> entries{};
    uintmax_t accum{};

    if (!exists(dir)) {
        cout << format("path {} does not exist\n", dir);
        return 1;
    }

    if(!is_directory(dir)) {
        cout << format("{} is not a directory\n", dir);
        return 1;
    }

    cout << format("{}:\n", absolute(dir));

    for (const auto& e : dit{ dir }) {
        entries.emplace_back(e.path());
    }
    std::sort(entries.begin(), entries.end(), dircmp_lc);

    for (const auto& e : entries) {
        fs::path p{ e };
        uintmax_t esize{ entry_size(p) };
        string dir_flag{};

        accum += esize;
        if(is_directory(p) && !is_symlink(p)) dir_flag = " ▽";
        cout << format("{:>5} {}{}\n", size_string(esize), p.filename(), dir_flag);
    }

    cout << format("{:->25}\n", "");
    cout << format("total bytes: {} ({})\n", make_commas(accum), size_string(accum));
}
