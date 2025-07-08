#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 100, M = 50000, inf = 0x3f3f3f3f;
int n, p, q, dp[M + 10];
void slove() {
	cin >> n >> p >> q;
	int ans = inf;
	memset(dp, 0, sizeof dp);
	for (int i = 1; i <= n; i++) {
		int x, y; cin >> x >> y;
		for (int j = q; j >= 0; j--) {
			if (j - y >= 0)
				dp[j] = max(dp[j], dp[j - y] + x);
		}
		for (int j = 0; j <= q; j++) {
			if (dp[j] >= p) ans = min(ans, j);
		}
	}
	cout << (ans == inf ? -1 : ans) << "\n";
}
int main() { cin.tie(0)->sync_with_stdio(0);
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
