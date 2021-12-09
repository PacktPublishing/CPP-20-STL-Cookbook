//  sentinel.cpp
//  as of 2021-12-05 bw [bw.org]

#include <format>
#include <iostream>

using std::format;
using std::cout;
using std::string_view;
using std::vector;

using sentinel_t = const char;
constexpr sentinel_t nullchar = '\0';

class cstr_it {
    const char *s{};

public:
    explicit cstr_it(const char *str) : s{str} {}

    char operator*() const { return *s; }

    cstr_it& operator++() {
        ++s;
        return *this;
    }

    bool operator!=(sentinel_t) const {
        return s != nullptr && *s != nullchar;
    }

    cstr_it begin() const { return *this; }
    sentinel_t end() const { return nullchar; }
};

void print_cstr(const char * s) {
    cout << format("{}: ", s);
    for (char c : cstr_it(s)) {
        std::cout << format("{:02x} ", c);
    }
    std::cout << '\n';
}

int main() {
    const char carray[]{"array"};
    print_cstr(carray);

    const char * cstr{"c-string"};
    print_cstr(cstr);
}
