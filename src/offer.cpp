#include <fstream>
#include <iomanip>
#include <cmath>
#define MAX 10000
using namespace std;

ifstream fin("offer.in");
ofstream fout("offer.out");

// Function to find the minimum of three values.
double min3(double a, double b, double c) {
    return min(min(a, b), c);
}

int main() {
    int n, k;
    double prices[MAX];
    double dp[MAX];

    fin >> n >> k;

    for (int i = 0; i < n; i++) {
        fin >> prices[i];
    }

    // Dynamic programming is used to determine the minimum cost.
    // Three possible costs are considered for i >= 2:
    // 1. The cost using dp[i - 1] and prices[i].
    // 2. The cost using dp[i - 2] and a discount on the cheapest of the last two items.
    // 3. The cost using dp[i - 3] and a discount for purchasing three items together.

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[i] = prices[i];
        } else if (i == 1) {
            double option1 = dp[i - 1] + prices[i];
            double minPrice = min(dp[i - 1], prices[i]);
            double option2 = 0;

            if (minPrice == dp[i - 1]) {
                option2 = prices[i] + dp[i - 1] / 2;
            } else {
                option2 = prices[i] / 2 + dp[i - 1];
            }

            dp[i] = min(option1, option2);
        } else {
            double option1 = dp[i - 1] + prices[i];
            double minPair = min(prices[i - 1], prices[i]);
            double minTriple = min3(prices[i - 2], prices[i - 1], prices[i]);
            double option2 = 0, option3 = 0;

            // Compute the discount when buying two items together.
            if (minPair == prices[i - 1]) {
                option2 = dp[i - 2] + prices[i - 1] / 2 + prices[i];
            } else {
                option2 = dp[i - 2] + prices[i - 1] + prices[i] / 2;
            }

            // Compute the discount when buying three items together.
            if (minTriple == prices[i - 2]) {
                option3 = dp[i - 3] + prices[i - 1] + prices[i];
            } else if (minTriple == prices[i - 1]) {
                option3 = dp[i - 3] + prices[i - 2] + prices[i];
            } else {
                option3 = dp[i - 3] + prices[i - 2] + prices[i - 1];
            }

            dp[i] = min3(option1, option2, option3);
        }
    }

    // The last element in the dp array represents the minimum total cost for k = 1.
    fout << fixed << setprecision(1) << dp[n - 1];

    return 0;
}
