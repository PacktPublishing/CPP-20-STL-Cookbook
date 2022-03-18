//  path-ops.cpp
//  as of 2022-03-09 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <filesystem>

using std::format;
using std::cout;

namespace fs = std::filesystem;

template<>
struct std::formatter<fs::path>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) {
        return format_to(ctx.out(), "{}", p.string());
    }
};

int main() {
    constexpr const char* fp{ "testdir/foo.txt" };
    try {
        fs::path p{ fp };
        cout << format("p: {}\n", p);

        cout << format("current_path: {}\n", fs::current_path());
        cout << format("absolute(p): {}\n", fs::absolute(p));
        cout << format("concatenate: {}\n", fs::path{ "testdir" } += "foo.txt");
        cout << format("append: {}\n", fs::path{ "testdir" } /= "foo.txt");
        cout << format("canonical: {}\n", fs::canonical(fs::path{ "." } /= "testdir"));
        cout << format("equivalent: {}\n", fs::equivalent("testdir/foo.txt", "testdir/../testdir/foo.txt"));
    } catch (const fs::filesystem_error& e) {
        cout << format("{}\n", e.what());
        cout << format("path1: {}\n", e.path1());
        cout << format("path2: {}\n", e.path2());
    }
}
