#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 500, inf = 0x3f3f3f3f;
int n, a[N + 10][N + 10], ma[2][N + 10][N + 10], mi[2][N + 10][N + 10];
int f[N + 10][N + 10], g[N + 10][N + 10];
int main() {
//	ffopen("walk");
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) cin >> a[i][j];
	for (int j = 1; j <= n; j++) {
		ma[0][0][j] = -inf, mi[0][0][j] = inf;
		ma[1][0][j] = -inf, mi[1][0][j] = inf;
		for (int i = 1; i <= n; i++) {
			ma[0][i][j] = max(ma[0][i - 1][j], a[i][j]);
			mi[0][i][j] = min(mi[0][i - 1][j], a[i][j]);
		}
		ma[0][n + 1][j] = -inf, mi[0][n + 1][j] = inf;
		ma[1][n + 1][j] = -inf, mi[1][n + 1][j] = inf;
		for (int i = n; i >= 1; i--) {
			ma[1][i][j] = max(ma[1][i + 1][j], a[i][j]);
			mi[1][i][j] = min(mi[1][i + 1][j], a[i][j]);
		}
	}
	memset(f, -inf, sizeof f);
	memset(g, inf, sizeof g);
	for (int j = 1; j <= n; j++) {
		for (int i = 0; i <= n; i++) {
			int now = 0;
			for (int k = 0; k <= i; k++) {
				int x = max(f[k][j - 1], ma[0][i][j]);
				int y = min(g[k][j - 1], mi[0][i + 1][j]);
				if (x - y > now) {
					now = x - y;
					f[i][j] = x, g[i][j] = y;
				}
			}
		}
	}
	int ans = inf;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, f[i][n] - g[i][n]);
	}
	cout << ans << "\n";
	return 0;
}
