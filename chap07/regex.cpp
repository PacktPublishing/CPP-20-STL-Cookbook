//  regex.cpp
//  as of 2022-01-26 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <regex>
#include <iomanip>

using std::format;
using std::cout;
using std::cin;
using std::string;

template<typename It>
void get_links(It it) {
    for(It end_it{}; it != end_it; ) {
        const string link{ *it++ };
        if(it == end_it) break;
        const string desc{ *it++ };

        cout << format("{:.<24} {}\n", desc, link);
    }
}

int main() {
    const char * fn{ "the-end.html" };
    const std::regex link_re{ "<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>" };

    string in{};
    std::ifstream infile(fn, std::ios_base::in);
    for(string line{}; getline(infile, line);) in += line;

    std::sregex_token_iterator it{ in.begin(), in.end(), link_re, {1, 2} };
    get_links(it);
}
