#include <fstream>
#include <iomanip>
#include <cmath>
#define MAX 100000
using namespace std;

ifstream fin("server.in");
ofstream fout("server.out");

// Function for efficient exponentiation

double findMin(double mid, int n, int p[], int c[]) {
    double min = 999999999.00;

    for (int i = 0; i < n; i++) {
        double temp = p[i] - abs(mid - c[i]);
        if (temp < min) {
            min = temp;
        }
    }

    return min;
}

int main() {
    int n, p[MAX], c[MAX];
    long long maxC = -999999999;
    double val = 0.00;
    bool found = false;

    fin >> n;

    for (int i = 0; i < n; i++) {
        fin >> p[i];
    }

    for (int i = 0; i < n; i++) {
        fin >> c[i];

        if (c[i] > maxC) {
            maxC = c[i];
        }
    }

    double bound = 0.10;
    double left = 0, right = maxC;

    // Binary search with the steps explained in README.md

    while (!found) {
        double mid = (left + right) / 2;

        double min1 = findMin(mid + bound, n, p, c);
        double min2 = findMin(mid - bound, n, p, c);

        if (abs(min1 - min2) < 0.01) {
            found = true;
            val = min1 + bound;
            break;
        } else {
            if (min1 > min2) {
                left = mid;
            } else {
                right = mid;
            }
        }
    }

    // Displaying the result with precision

    fout << fixed << setprecision(1) << val << endl;

    return 0;
}
