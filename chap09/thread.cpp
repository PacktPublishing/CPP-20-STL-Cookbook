//  thread.cpp
//  as of 2022-02-22 bw [bw.org]

#include <format>
#include <iostream>
#include <chrono>
#include <thread>

using std::format;
using std::cout;
using std::thread;

void sleepms(const unsigned ms) {
    using std::chrono::milliseconds;
    std::this_thread::sleep_for(milliseconds(ms));
}

void fthread(const int n) {
    cout << format("This is t{}\n", n);

    for(size_t i{}; i < 5; ++i) {
        sleepms(100 * n);
        cout << format("t{}: {}\n", n, i + 1);
    }
    cout << format("Finishing t{}\n", n);
}

int main() {
    thread t1(fthread, 1);
    thread t2(fthread, 2);
    t1.detach();
    t2.detach();

    cout << "main() sleep 2 sec\n";
    sleepms(2000);

    cout << "end of main()\n";
}
