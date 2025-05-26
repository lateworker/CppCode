#include <bits/stdc++.h>
using namespace std;
const int N = 50, M = 10000;
int n, x;
bool dp[N + 10][M + 10];
int main() {
	cin >> n >> x;
	dp[0][0] = true;
	for (int i = 1; i <= n; i++) {
		int a, b; cin >> a >> b;
		for (int j = 0; j <= b; j++)
			for (int k = x; k >= j * a; k--) {
				dp[i][k] |= dp[i - 1][k - j * a];
			}
	}
	cout << (dp[n][x] ? "Yes\n" : "No\n");
	return 0;
}
