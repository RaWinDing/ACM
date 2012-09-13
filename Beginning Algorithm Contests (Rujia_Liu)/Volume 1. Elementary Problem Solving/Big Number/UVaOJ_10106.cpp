// UVaOJ 10106
// Product
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MAXD = 502;

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

    BigUnsigned operator*(const BigUnsigned& one) {
        BigUnsigned res;
        res.len = len + one.len;
        for(int i = 0; i < len; i++)
            for(int j = 0; j < one.len; j++)
                res.d[i + j] += d[i] * one.d[j];
        for(int i = 0; i < res.len - 1; i++){
            res.d[i + 1] += res.d[i] / 10;
            res.d[i] %= 10;
        }
        res.Clean();
        return res;
    }
};

BigUnsigned a, b;

int main() {
    while (cin >> a >> b) {
        cout << a * b << endl;
    }

    return 0;
}
