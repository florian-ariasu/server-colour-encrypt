#include <fstream>
#define MAX 300000
using namespace std;

ifstream fin("compression.in");
ofstream fout("compression.out");

int main() {
    int n, m, a[MAX], b[MAX];
    int i, j, k, sum1 = 0, sum2 = 0;
    bool search = false, case1 = false, case2 = false;

    fin >> n;
    for (i = 0; i < n; i++) {
        fin >> a[i];
    }

    fin >> m;
    for (j = 0; j < m; j++) {
        fin >> b[j];
    }

    i = 0, j = 0, k = 0;

    // The problem is solved within this while loop, which has two conditions  
    // and two indices that allow simultaneous traversal of both arrays.

    while (i <= n && j <= m) {
        if (i == n && j == m) {
            break;
        }

        if (a[i] == b[j] && !search) {
            k++;
            i++, j++;
        } else {
            if (a[i] > b[j] && !search) {
                case1 = true;
                search = true;
                sum1 += b[j];
                j++;
            } else if (a[i] < b[j] && !search) {
                case2 = true;
                search = true;
                sum1 += a[i];
                i++;
            } else if (search) {
                if (case1) {
                    if (sum1 > a[i] && !sum2) {
                        sum2 += a[i];
                        i++;
                    } else if (sum1 < a[i]) {
                        sum1 += b[j];
                        j++;
                    }

                    if (sum1 < sum2 && sum1) {
                        sum1 += b[j];
                        j++;
                    } else if (sum1 > sum2 && sum2) {
                        sum2 += a[i];
                        i++;
                    }

                    if (sum1 == a[i] && !sum2) {
                        i++;
                        case1 = false;
                        search = false;
                        k++;
                        sum1 = 0;
                    }

                    if (sum1 == sum2 && sum1) {
                        case1 = false;
                        search = false;
                        k++;
                        sum1 = 0;
                        sum2 = 0;
                    }
                } else {
                    if (sum1 > b[j] && !sum2) {
                        sum2 += b[j];
                        j++;
                    } else if (sum1 < b[j]) {
                        sum1 += a[i];
                        i++;
                    }

                    if (sum1 < sum2 && sum1) {
                        sum1 += a[i];
                        i++;
                    } else if (sum1 > sum2 && sum2) {
                        sum2 += b[j];
                        j++;
                    }

                    if (sum1 == b[j] && !sum2) {
                        j++;
                        case2 = false;
                        search = false;
                        k++;
                        sum1 = 0;
                    }

                    if (sum1 == sum2 && sum1) {
                        case2 = false;
                        search = false;
                        k++;
                        sum1 = 0;
                        sum2 = 0;
                    }
                }
            }
        }
    }

    // This condition ensures that both arrays have been fully traversed  
    // rather than one being fully traversed while the other remains partially traversed.

    if ((i + j == n + m) && k) {
        fout << k;
    } else {
        fout << -1;
    }

    fin.close();
    fout.close();
    return 0;
}
