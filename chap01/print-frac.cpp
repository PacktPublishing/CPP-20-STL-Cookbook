// print-frac.cpp
// as of 2021-09-04 bw [bw.org]

#include <bwprint.h>
#include <string_view>
#include <string>

// support for std:: or fmt:: (reference implementation)
// see j.bw.org/fmt
#ifdef __cpp_lib_format
#define formatter std::formatter
#else
#define formatter fmt::formatter
#endif // __cpp_lib_format

using std::string_view;
using std::string;
using std::print;

struct Frac {
    long n;
    long d;
};
 
template<>
struct formatter<Frac> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const Frac& f, FormatContext& ctx) {
        return format_to(ctx.out(), "{0:d}/{1:d}", f.n, f.d);
    }
};

int main() {
    Frac f{ 5, 3 };
    print("Frac: {}\n", f);
}

