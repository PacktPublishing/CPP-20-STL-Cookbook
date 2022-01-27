// bwprint.h by Bill Weinman <http://bw.org/>
// Copyright (c) 2021 BHG LLC
// This code is free and open source without restriction
// Please include attribution above
// updated 2022-01-17
//
// This code requires either the C++20 <format> library,
// or the libfmt library from <https://fmt.dev/>
//
// Once C++23 is released, along with std::print(), this code
// will become obsolete.

// NOTE BENE: It's generally considered extremely bad practice to add user code
// to the std namespace. In this case I chose to violate that rule with the
// knowledge that this code will be obsoleted by an equivalent function in C++23.
// At that time the user may simply drop this #include file and leave the rest of
// their code alone. I think that's a good reason to violate the rule. If you
// disagree, simply change the _BWP_NAMESPACE macro to whatever name you prefer.

#ifndef BW_PRINT
#define BW_PRINT

#include <version>
#include <iostream>
#include <string_view>
#include <cstdio>

// namespace for print() is std or bw
// make this std if you dare

// #define BWP_NAMESPACE bw
#define BWP_NAMESPACE std

#ifdef __cpp_lib_format
#   include <format>
#   define BWP_FMT_LIB "std"
#   define BWP_FMTNS std
#elif __has_include(<fmt/core.h>)
#   include <fmt/core.h>
#   define BWP_FMT_LIB "libfmt"
#   define BWP_FMTNS fmt
#else
#   error "no format lib"
#endif // __cpp_lib_format

#ifdef BWP_FMT_LIB

// print function is missing from c++20 format library
namespace BWP_NAMESPACE {

    using BWP_FMTNS::format;
    using BWP_FMTNS::formatter;
    using BWP_FMTNS::vformat;
    using BWP_FMTNS::make_format_args;

    constexpr const char * bwp_version = "1.0.12";

    // default to stdout
    // print(string_view format-string, args...)
    template<typename... Args> constexpr void print(const std::string_view str_fmt, Args&&... args) {
        fputs(vformat(str_fmt, make_format_args(args...)).c_str(), stdout);
    }

    // send to FILE*
    // print(FILE*, string_view format-string, args...)
    template<typename... Args> constexpr void print(FILE* fdest, const std::string_view str_fmt, Args&&... args) {
        fputs(vformat(str_fmt, make_format_args(args...)).c_str(), fdest);
    }

    // send to ostream
    // print(ostream, string_view format-string, args...)
    template<typename... Args> constexpr void print(std::ostream & ostream_dest, const std::string_view str_fmt, Args&&... args) {
        ostream_dest << vformat(str_fmt, make_format_args(args...));
    }

    // no parameter stack cstr
    // print(const char * str)
    void print(const char * str) {
        fputs(str, stdout);
    }

    // no parameter stack string
    // print(const string & str)
    void print(const std::string & str) {
        fputs(str.c_str(), stdout);
    }
}

using BWP_NAMESPACE::print;

#endif // BWP_FMT_LIB

#endif // BWPRINT
