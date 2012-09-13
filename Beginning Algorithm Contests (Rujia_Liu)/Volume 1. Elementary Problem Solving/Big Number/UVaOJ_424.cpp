// UVaOJ 424
// Integer Inquiry
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MAXD = 1000;

struct BigUnsigned {
    int len, d[MAXD];
    BigUnsigned() { memset(d, 0, sizeof(d)); len = 0; }
    BigUnsigned(int num) { *this = num; }
    BigUnsigned(const char* str) { *this = str; }
    void Clean() { while (len > 1 && !d[len - 1]) len--; }
    BigUnsigned operator=(int num) {
        char str[MAXD];
        sprintf(str, "%d", num);
        *this = str;
        return *this;
    }
    BigUnsigned operator=(const char* str) {
        memset(d, 0, sizeof(d));
        len = strlen(str);
        for (int i = 0; i < len; i++) d[i] = str[len - i - 1] - '0';
        Clean();
        return *this;
    }

    string ToStr() const {
        string res = "";
        for (int i = 0; i < len; i++) res = (char)(d[i] + '0') + res;
        return res == "" ? "0" : res;
    }
    friend istream& operator>>(istream &in, BigUnsigned& one) {
        string str;
        in >> str;
        one = str.c_str();
        return in;
    }
    friend ostream& operator<<(ostream &out, const BigUnsigned& x) {
        out << x.ToStr();
        return out;
    }

    BigUnsigned operator+(const BigUnsigned& one) const {
        BigUnsigned res;
        for (int i = 0, x = 0; i < max(len, one.len) + 1; i++) {
            int tmp = d[i] + one.d[i] + x;
            res.d[res.len++] = tmp % 10;
            x = tmp / 10;
        }
        res.Clean();
        return res;
    }

    BigUnsigned operator+=(const BigUnsigned& one) { return *this = *this + one; }

    bool operator<(const BigUnsigned& one) const {
        if (len != one.len) return len < one.len;
        for (int i = len - 1; i >= 0; i--)
            if (d[i] != one.d[i]) return d[i] < one.d[i];
        return false;
    }
    bool operator!=(const BigUnsigned& one) const { return one < *this || *this < one; }
};

BigUnsigned ans = 0;
BigUnsigned one;

int main() {
    while (cin >> one && one != 0) {
        ans += one;
    }
    cout << ans << endl;

    return 0;
}
