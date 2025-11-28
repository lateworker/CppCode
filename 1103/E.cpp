#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const int N = 100000, LGN = __lg(N);
int n, dep[N + 10], siz[N + 10], fa[N + 10][LGN + 3];
vector<int> g[N + 10];
void dfs(int u, int p) {
	dep[u] = dep[p] + 1, fa[u][0] = p, siz[u] = 0;
	for (int i = 1; i <= LGN; i++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : g[u]) if (v != p) {
		dfs(v, u);
		siz[u] += siz[v];
	}
	if (!siz[u]) siz[u] = 1;
}
void out(int u, int p) {
	cerr << u << ' ' << dep[u] << ' ' << siz[u] << '\n';
	for (int v : g[u]) if (v != p) out(v, u);
}
void slove() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i == 1 || (int)g[i].size() > 1) continue;
		int d = (dep[i] - 1) >> 1, u = i;
		for (int j = LGN; ~j; j--) if (d >> j & 1) u = fa[u][j];
		if (u != i) chkmax(ans, siz[u]);
	}
	cout << ans << '\n';
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) g[i].clear();
	}
	return 0;
}

