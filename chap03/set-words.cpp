//  set-words.cpp
//  as of 2021-11-17 bw [bw.org]

#include <format>
#include <iostream>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>

using std::format;
using std::cout;
using std::set;
using std::string;
using std::istream_iterator;
using std::cin;
using std::copy;
using std::inserter;

using input_it = istream_iterator<string>;

int main() {
    set<string> words;

    input_it it{ cin };
    input_it end{};

    copy(it, end, inserter(words, words.end()));
    
    for(const string & w : words) {
        cout << format("{} ", w);
    }
    cout << '\n';
}
