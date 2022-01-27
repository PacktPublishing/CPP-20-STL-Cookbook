//  count-words.cpp
//  as of 2022-01-27 bw [bw.org]

#include <format>
#include <iostream>
#include <fstream>
#include <string>

using std::format;
using std::cout;
using std::string;
using std::string_view;

size_t wordcount(auto& is) {
    using it_t = std::istream_iterator<string>;
    return std::distance(it_t{is}, it_t{});
}

int main() {
    const char * fn{ "the-raven.txt" };
    std::ifstream infile{fn, std::ios_base::in};
    size_t wc{ wordcount(infile) };
    cout << format("There are {} words in the file.\n", wc);
}
