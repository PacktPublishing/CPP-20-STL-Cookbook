//  formatter.cpp
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

int main(const int argc, const char** argv) {
    if (argc != 2) {
        fs::path fn{ argv[0] };
        cout << format("usage: {} <path>\n", fn.filename());
        return 0;
    }

    fs::path dir{ argv[1] };
    if (!fs::exists(dir)) {
        cout << format("path: {} does not exist\n", dir);
        return 1;
    }

    cout << format("path: {}\n", dir);
    cout << format("filename: {}\n", dir.filename());
    cout << format("cannonical: {}\n", fs::canonical(dir));
}
