// bwprint-module.ixx
// module version 
// as of this writing, this module requires MSVC 
// as of 2021-10-20 bw [bw.org]

module;
#include <cstdio>

export module bwprint;
export import std.core;

// print function is missing from c++20 format library
namespace std {

    export constexpr const char * bwp_version = "1.0.9 [m]";

    // default to stdout
    // print(string_view format-string, args...)
    export template<typename... Args>
    constexpr void print(const std::string_view str_fmt, Args&&... args) {
        fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
    }

    // send to FILE*
    // print(FILE*, string_view format-string, args...)
    export template<typename... Args>
    constexpr void print(FILE* fdest, const std::string_view str_fmt, Args&&... args) {
        fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), fdest);
    }

    // send to ostream
    // print(ostream, string_view format-string, args...)
    export template<typename... Args>
    constexpr void print(std::ostream & ostream_dest, const std::string_view str_fmt, Args&&... args) {
        ostream_dest << std::vformat(str_fmt, std::make_format_args(args...));
    }

    // no parameter stack cstr
    // print(const char * str)
    export void print(const char * str) {
        fputs(str, stdout);
    }

    // no parameter stack string
    // print(const string & str)
    export void print(const std::string & str) {
        fputs(str.c_str(), stdout);
    }
}

