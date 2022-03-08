//  sleep.cpp
//  as of 2022-02-25 bw [bw.org]

#include <format>
#include <iostream>
#include <chrono>
#include <thread>

using std::format;
using std::cout;
using std::chrono::steady_clock;
using std::chrono::duration;

using namespace std::this_thread;
using namespace std::chrono_literals;

int main() {
    auto t1 = steady_clock::now();
    cout << "sleep for 1.3 seconds\n";
    sleep_for(1s + 300ms);

    cout << "sleep for 2 seconds\n";
    sleep_until(steady_clock::now() + 2s);

    duration<double> dur1 = steady_clock::now() - t1;
    cout << format("total duration: {:.5}s\n", dur1.count());
}
