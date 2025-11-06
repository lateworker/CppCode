#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
const int inf = 0x3f3f3f3f, N = 12;
int n, m, dp[N + 10][(1 << N) + 10], g[N + 10][N + 10], co[(1 << N) + 10][(1 << N) + 10];
int main() {
	cin >> n >> m;
	memset(g, 0x3f, sizeof g);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v, chkmin(g[u][v], w), chkmin(g[v][u], w);
	}
	int ALL = (1 << n) - 1;
	for (int S = 0; S <= ALL; ++S)
		for (int T = S; T; T = (T - 1) & S) {
			int dif = S ^ T;
			for (int i = n - 1; i >= 0; --i) if (dif >= (1 << i)) {
				int dis = inf;
				for (int j = 0; j < n; ++j) if (T >> j & 1) chkmin(dis, g[i][j]);
				if (dis == inf) { co[T][S] = co[S][T] = inf; break; }
				co[T][S] += dis, co[S][T] += dis, dif ^= (1 << i);
			}
		}
	memset(dp, 0x3f, sizeof dp);
	for (int i = 0; i < n; ++i) dp[1][(1 << i)] = 0;
	for (int i = 2; i <= n; ++i) {
		for (int S = 0; S <= ALL; ++S)
			for (int T = S; T; T = (T - 1) & S)
				if (co[T][S] != inf) chkmin(dp[i][S], dp[i - 1][T] + co[T][S] * (i - 1));
	}
	int ans = inf;
	for (int i = 1; i <= n; ++i) chkmin(ans, dp[i][ALL]);
	cout << ans;
	return 0;
}
