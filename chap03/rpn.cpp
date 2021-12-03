//  rpn.cpp
//  as of 2021-11-29 bw [bw.org]

#include <format>
#include <iostream>
#include <stack>
#include <deque>
#include <map>
#include <string>
#include <utility>
#include <cctype>
#include <cmath>
#include <iterator>
#include <limits>

using std::format;
using std::cout;
using std::stack;
using std::deque;
using std::map;
using std::string;
using std::pair;
using std::istream_iterator;
using std::cin;

class RPN {
    deque<double> deq_{};
    constexpr static double zero_{0.0};
    constexpr static double inf_{ std::numeric_limits<double>::infinity() };

public:
    // process an operand/operator
    double op(const string & s) {
        if(is_numeric(s)) {
            double v{stod(s, nullptr)};
            deq_.push_front(v);
            return v;
        }
        else return optor(s);
    }

    // empty the stack
    void clear() {
        deq_.clear();
    }

    // print the stack
    string get_stack_string() const {
        string s{};
        for(auto v : deq_) {
            s += format("{} ", v);
        }
        return s;
    }

private:    // utility functions
    // pop and get two operands
    pair<double, double> pop_get2() {
        if(deq_.size() < 2) return {zero_, zero_};
        double v1{deq_.front()};
        deq_.pop_front();
        double v2{deq_.front()};
        deq_.pop_front();
        return {v2, v1};
    }

    bool is_numeric(const string& s) {
        for(const char c : s) {
            if(c != '.' && !std::isdigit(c)) return false;
        }
        return true;
    }

    // operators 
    double optor(const string& op) {
        map<string, double (*)(double, double)> opmap {
            {"+", [](double l, double r){ return l + r; }},
            {"-", [](double l, double r){ return l - r; }},
            {"*", [](double l, double r){ return l * r; }},
            {"/", [](double l, double r){ return l / r; }},
            {"^", [](double l, double r){ return pow(l, r); }},
            {"%", [](double l, double r){ return fmod(l, r); }}
        };

        if(opmap.find(op) == opmap.end()) return zero_;
        auto [l, r] = pop_get2();

        // don’t divide by zero
        if(op == "/" && r == zero_) deq_.push_front(inf_);
        else deq_.push_front(opmap.at(op)(l, r));
        return deq_.front();
    }
};

int main() {
    RPN rpn;

    for(string o{}; cin >> o; ) {
        rpn.op(o);
        auto stack_str{rpn.get_stack_string()};
        cout << format("{}: {}\n", o, stack_str);
    }
}
