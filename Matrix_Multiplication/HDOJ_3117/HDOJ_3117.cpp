// HDOJ 3117
// Fibonacci Numbers
// by A Code Rabbit

#include <cstdio>
#include <cmath>

const int ORDER = 2;
const int DIVISOR_SHOW = 10000;

enum Need {
    ALL,
    FIRST,
    LAST,
};

struct Matrix {
    long long element[ORDER][ORDER];
};

int n;

Matrix mat_unit;
Matrix mat_one;

int Fibonacci(int x, Need need);
void INIT();
Matrix QuickPower(Matrix mat_unit, Matrix mat_one, int index, Need need);
Matrix Multiply(Matrix mat_a, Matrix mat_b, Need need);
/* if bo is true, it means that the program is competing the first four numbers of Fibonacci numbers. */

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n < 40) {
            printf("%d\n", Fibonacci(n, ALL));
        } else {
            printf("%d...%04d\n", Fibonacci(n, FIRST), Fibonacci(n, LAST));
        }
    }

    return 0;
}

int Fibonacci(int x, Need need) {
    if (need == FIRST) {
        double ans = x * log10((1.0 + sqrt(5.0)) / 2.0) - 0.5 * log10(5.0);
        ans = ans - (int)ans;
        ans = pow(10, ans);
        return (int)(ans * 1000);
    }
    INIT();
    Matrix mat_ans = QuickPower(mat_unit, mat_one, x, need);
    int ans = mat_ans.element[1][0];
    return ans;
}

void INIT() {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat_unit.element[i][j] = i == j ? 1 : 0;
        }
    }
    mat_one.element[0][0] = 1;
    mat_one.element[0][1] = 1;
    mat_one.element[1][0] = 1;
    mat_one.element[1][1] = 0;
}

Matrix QuickPower(Matrix mat_unit, Matrix mat_one, int index, Need need) {
    Matrix mat_result = mat_unit;
    while (index) {
        if (index & 1) {
            mat_result = Multiply(mat_result, mat_one, need); 
        }
        mat_one = Multiply(mat_one, mat_one, need);
        index >>= 1;
    }
    return mat_result;
}

Matrix Multiply(Matrix mat_a, Matrix mat_b, Need need) {
    Matrix mat_result;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat_result.element[i][j] = 0;
            for (int k = 0; k < ORDER; ++k) {
                mat_result.element[i][j] += mat_a.element[i][k] * mat_b.element[k][j];
            }
            if (need == ALL) {
            } else 
            if (need == LAST){
                mat_result.element[i][j] %= DIVISOR_SHOW;
            }
        }
    }
    return mat_result;
}
