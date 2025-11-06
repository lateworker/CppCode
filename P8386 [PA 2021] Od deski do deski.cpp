#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 3000, Mod = 1000000007;
intl n, m, dp[2][N + 10][N + 10];
int main() {
	cin >> n >> m;
	dp[1][0][0] = 1;
	for (intl i = 1; i <= n; i++) {
		for (intl j = i; j >= 1; j--) {
			dp[1][i][j] = dp[0][i - 1][j] * j % Mod + dp[1][i - 1][j] * j % Mod;
			dp[0][i][j] = dp[1][i - 1][j - 1] * (m - j + 1) % Mod + dp[0][i - 1][j] * (m - j) % Mod;
			dp[0][i][j] %= Mod, dp[1][i][j] %= Mod;
		}
	}
	intl ans = 0;
	for (intl j = 1; j <= n; j++) {
		ans += dp[1][n][j], ans %= Mod;
	}
	cout << ans << "\n";
	return 0;
}
