#include <iostream>
#include <fstream>
#include <cmath>
#define MAX 1000000
using namespace std;

ifstream fin("colouring.in");
ofstream fout("colouring.out");

// Function for efficient exponentiation 
// Used to handle large cases when the result exceeds one billion

int fastPow(long base, int exponent, int mod) {
    if (exponent == 0) {
        return 1;
    }

    long aux = 1;
    while (exponent != 1) {
        if (exponent % 2 == 0) {
            base = (1LL * base * base) % (1LL * mod);
            exponent /= 2;
        } else {
            aux = (1LL * aux * base) % (1LL * mod);
            exponent--;
        }
    }

    return (int) ((1LL * aux * base) % (1LL * mod));
}

int main() {
    int n;
    int a[MAX], b[MAX];
    int power = pow(10, 9) + 7;
    long long res = 1, temp = 0;
    char c;

    fin >> n;

    // Forming the two arrays

    for (int i = 0; i < n; i++) {
        fin >> a[i] >> c;
        b[i] = c - 'A';
    }

    // The loop contains the 6 cases explained in README.md

    for (int i = 0; i < n; i++) {
        if (i == 0 && b[i] == 7) {
            temp = fastPow(3, a[i] - 1, power);
            res *= 6 * temp;
            res = res % power;
        } else if (i == 0 && b[i] == 21) {
            res = 3 * fastPow(2, a[i] - 1, power);
            res = res % power;
        } else if (b[i] == 7) {
            if (b[i - 1] == 7) {
                res *= fastPow(3, a[i], power);
                res = res % power;
            } else {
                res *= 2 * fastPow(3, a[i] - 1, power);
                res = res % power;
            }
        } else if (b[i] == 21) {
            if (b[i - 1] == 7) {
                res *= fastPow(2, a[i] - 1, power);
                res = res % power;
            } else if (b[i - 1] == 21) {
                res *= fastPow(2, a[i], power);
                res = res % power;
            }
        }
    }

    fout << res;

    return 0;
}
