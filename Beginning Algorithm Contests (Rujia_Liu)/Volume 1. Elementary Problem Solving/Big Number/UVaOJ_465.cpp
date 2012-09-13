// UVaOJ 465
// Overflow
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int LIMITS_INT = 2147483647;
const int MAXD = 10000;

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

    bool operator<(const BigUnsigned& one) const {
        if (len != one.len) return len < one.len;
        for (int i = len - 1; i >= 0; i--)
            if (d[i] != one.d[i]) return d[i] < one.d[i];
        return false;
    }
    bool operator>(const BigUnsigned& one) const { return one < *this; }
    bool operator<=(const BigUnsigned& one) const { return !(one < *this); }
    bool operator>=(const BigUnsigned& one) const { return !(*this < one); }
    bool operator!=(const BigUnsigned& one) const { return one < *this || *this < one; }
    bool operator==(const BigUnsigned& one) const { return !(one < *this || *this < one); }
};

char str_a[MAXD];
char str_b[MAXD];
char optor;
BigUnsigned a, b, ans;

int main() {
    while (scanf("%s %c %s", str_a, &optor, str_b) != EOF) {
        a = str_a;
        b = str_b;
        cout << str_a << " " << optor << " " << str_b << endl;
        if (a > LIMITS_INT) printf("first number too big\n");
        if (b > LIMITS_INT) printf("second number too big\n");
        ans = optor == '+' ? a + b : a * b;
        if (ans > LIMITS_INT) printf("result too big\n");
    }

    return 0;
} 
