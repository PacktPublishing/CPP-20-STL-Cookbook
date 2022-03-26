// numword.h by Bill Weinman [bw.org]
// version as of 2022-03-24
#ifndef _NUMWORD_H
#define _NUMWORD_H

#include <string>
#include <memory>

namespace bw {

    using std::string;
    using std::string_view;
    using numnum = uint64_t;    // yummy numbers
    using bufstr = std::unique_ptr<string>;
    constexpr const char* _version{ "2022.03.24" };
    
    // maxnum is nine hundred ninety-nine quadrillion nine hundred ninety-nine trillion
    // nine hundred ninety-nine billion nine hundred ninety-nine million
    // nine hundred ninety-nine thousand nine hundred ninety-nine
    constexpr numnum maxnum = 999'999'999'999'999'999;

    constexpr int zero_i{ 0 };
    constexpr int five_i{ 5 };
    constexpr numnum zero{ 0 };
    constexpr numnum ten{ 10 };
    constexpr numnum twenty{ 20 };
    constexpr numnum hundred{ 100 };
    constexpr numnum thousand{ 1000 };

    constexpr string_view errnum{ "error" };
    
    constexpr string_view _singles[] {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    constexpr string_view _teens[] {
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    constexpr string_view _tens[] {
        errnum, errnum, "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety",
    };

    constexpr string_view _hundred_string = "hundred";

    constexpr string_view _powers[] {
        errnum, "thousand", "million", "billion", "trillion", "quadrillion"
    };

    constexpr char _hyphen{ '-' };
    constexpr char _space{ ' ' };

    class numword {
        bufstr _buf{ std::make_unique<string>(string{}) };
        numnum _num{};
        bool _hyphen_flag{ false };
        
        void clearbuf();
        size_t bufsize();
        void appendbuf(const string& s);
        void appendbuf(const string_view& s);
        void appendbuf(const char c);
        void appendspace();
        numnum pow_i(const numnum n, numnum p);
        
    public:
        numword(const numnum& num = 0) : _num(num) {}
        numword(const numword& nw) : _num(nw.getnum()) {}
        const char * version() const { return _version; }
        void setnum(const numnum& num) { _num = num; }
        numnum getnum() const { return _num; }
        numnum operator= (const numnum& num);
        const string& words();
        const string& words(const numnum& num);
        const string& operator() (const numnum& num) { return words(num); };
    };
    
}

#endif /* _NUMWORD_H */
