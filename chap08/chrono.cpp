//  chrono.cpp
//  as of 2022-02-04 bw [bw.org]

#include <format>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

using std::format;
using std::cout;
using std::string;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

using seconds = duration<double>;
using milliseconds = duration<double, std::milli>;
using microseconds = duration<double, std::micro>;
using fps24 = duration<unsigned long, std::ratio<1, 24>>;

constexpr uint64_t MAX_PRIME{ 0x1FFFF };  // largest uint64_t is 0xFFFFFFFFFFFFFFFF

string make_commas(const uint64_t num) {
    string s{ std::to_string(num) };
    for(long l = s.length() - 3; l > 0; l -= 3) {
        s.insert((int)l, ",");
    }
    return s;
}

seconds timer(uint64_t(*f)()) {
    auto t1{ steady_clock::now() };
    uint64_t count{ f() };
    auto t2{ steady_clock::now() };
    seconds secs{ t2 - t1 };
    cout << format("there are {} primes in range\n", make_commas(count));
    return secs;
}

uint64_t count_primes() {
    constexpr auto isprime = [](const uint64_t n) {
        for(uint64_t i{ 2 }; i < n / 2; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    };
    uint64_t count{ 0 };
    uint64_t start{ 2 };
    uint64_t end{ MAX_PRIME };
    for(uint64_t i{ start }; i <= end ; ++i) {
        if(isprime(i)) ++count;
   }
   return count;
}

int main() {
    auto t = system_clock::now();
    cout << format("system_clock::now is {:%F %T %Z}\n", t);

    cout << format("counting primes up to {}...\n", make_commas(MAX_PRIME));
    auto secs{ timer(count_primes) };
    cout << format("time elapsed: {:.3f} sec\n", secs.count());
    cout << format("time elapsed: {:.3f} ms\n", milliseconds(secs).count());
    cout << format("time elapsed: {:.3e} μs\n", microseconds(secs).count());
    cout << format("time elapsed: {} frames at 24 fps\n", floor<fps24>(secs).count());

    cout << format("time elapsed: {:.3}\n", secs);
    cout << format("time elapsed: {:.3}\n", milliseconds(secs));
    cout << format("time elapsed: {:.3}\n", microseconds(secs));
}
