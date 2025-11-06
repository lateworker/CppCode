#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
using intl = long long;
const intl N = 1000, M = 200, Mod = 1000000007;
intl n, m, k, f[N + 10][M + 10], g[N + 10][M + 10], h[N + 10][M + 10];
string a, b;
int main() {
	cin >> n >> m >> k >> a >> b;
	a = '#' + a, b = '#' + b;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i] == b[j]) h[i][j] = h[i - 1][j - 1] + 1;
	for (int i = 0; i <= n; i++) f[i][0] = 1;
	for (int kk = 1; kk <= k; kk++) {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++)
				g[i][j] = (g[i - 1][j - 1] + f[i][j]) % Mod, f[i][j] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				f[i][j] = f[i - 1][j] % Mod;
				if (a[i] != b[j]) continue;
				intl p = i > h[i][j] && j > h[i][j] ? g[i - h[i][j] - 1][j - h[i][j] - 1] : 0;
				f[i][j] += (g[i - 1][j - 1] - p + Mod) % Mod, f[i][j] %= Mod;
			}
		}
	}
	cout << (f[n][m] % Mod + Mod) % Mod << "\n";
	return 0;
}
