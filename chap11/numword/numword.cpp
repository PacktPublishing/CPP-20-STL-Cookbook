// numword.cpp by Bill Weinman [bw.org]
// version as of 2022-03-24

#include "numword.h"
using namespace bw;

// assignment operator
numnum numword::operator= (const numnum& num) {
    setnum(num);
    return getnum();
}

const string& numword::words() {
    return words(_num);
}

// convert to words
const string& numword::words( const numnum& num ) {
    numnum n{ num };
    clearbuf();

    if(n > maxnum) {
        appendbuf(errnum);
        return *_buf;
    }

    if (n == 0) {
        appendbuf(_singles[n]);
        return *_buf;
    }

    // powers of 1000
    if (n >= thousand) {
        for(int i{ five_i }; i > zero_i; --i) {
                numnum power{ pow_i(thousand, i) };
                numnum _n{ ( n - ( n % power ) ) / power };
                if (_n) {
                    int index = i;
                    numword _nw{ _n };
                    appendbuf(_nw.words());
                    appendbuf(_powers[index]);
                    n -= _n * power;
                }
        }
    }
    // hundreds
    if (n >= hundred && n < thousand) {
        numnum _n{ ( n - ( n % hundred ) ) / hundred };
        numword _nw{ _n };
        appendbuf(_nw.words());
        appendbuf(_hundred_string);
        n -= _n * hundred;
    }
    // tens
    if (n >= twenty && n < hundred) {
        numnum _n{ ( n - ( n % ten ) ) / ten };
        appendbuf(_tens[_n]);
        n -= _n * ten;
        _hyphen_flag = true;
    }
    // teens
    if (n >= ten && n < twenty) {
        appendbuf(_teens[n - ten]);
        n = zero;
    }
    // singles
    if (n > zero && n < ten) {
        appendbuf(_singles[n]);
    }

    return *_buf;
}

// MARK: - private methods

// reset the buffer
void numword::clearbuf() {
    *_buf = string{};
}

size_t numword::bufsize() {
    return _buf->size();
}

// append text to the string buffer
void numword::appendbuf(const string& s) {
    appendspace();
    _buf->append(s);
}

void numword::appendbuf(const string_view& s) {
    appendspace();
    _buf->append(s.data());
}

void numword::appendbuf(const char c) {
    _buf->append(1, c);
}

// append space (or hyphen)
void numword::appendspace() {
    if(bufsize()) {
        appendbuf( _hyphen_flag ? _hyphen : _space);
        _hyphen_flag = false;
    }
}

numnum numword::pow_i(const numnum n, numnum p) {
    numnum out{ n };
    while(--p) out *= n;
    return out;
}
