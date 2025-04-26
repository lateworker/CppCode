#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 100000;
int n, m;
intl a[N + 10], b[N + 10], dp[N + 10];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], b[i] = b[i - 1] + a[i];
	memset(dp, 0x3f, sizeof dp), dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		intl ma = 0;
		for (int j = i; j >= 1 && b[i] - b[j - 1] <= m; j--) {
			ma = max(ma, a[j]);
			dp[i] = min(dp[i], dp[j - 1] + ma);
		}
	}
	cout << dp[n] << "\n";
	return 0;
}
