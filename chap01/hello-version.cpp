//  hello-version.cpp
//  as of 2021-10-27 bw [bw.org]

#include <bwprint.h>

#if defined(__clang__)
constexpr const char * cc_version_string{ "Clang version" };
constexpr const char * cc_version{ __VERSION__ };
constexpr bool msvc_flag{ false };
#elif defined(__GNUC__)
constexpr const char * cc_version_string{ "GCC version" };
constexpr const char * cc_version{ __VERSION__ };
constexpr bool msvc_flag{ false };
#elif defined(_MSC_VER)
constexpr const char * cc_version_string{ "MSVC version" };
constexpr long int cc_version{ _MSC_VER };
constexpr bool msvc_flag{ true };
#endif // __VERSION__

using std::print;

constexpr long int cpp_version{ __cplusplus };
constexpr const char * cpp_msvc_disclaimer{ msvc_flag ? " (wrong on MSVC)" : "" };

int main() {
    print("Hello version of 2021-10-27\n");
    print("{} {}\n", cc_version_string, cc_version);
    print("C++ version {}{}\n", cpp_version, cpp_msvc_disclaimer);
    print("Format source {}\n", BWP_FMT_LIB);
    print(stdout, "bw::print() version {}\n", std::bwp_version);

    return 0;
}
