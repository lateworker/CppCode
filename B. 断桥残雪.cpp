#include <bits/stdc++.h>
#define int long long
using namespace std;
using intl = long long;
const intl N = 200000, inf = 0x3f3f3f3f3f3f3f3fLL;
intl n, m, a[N + 10], dfn[N + 10], low[N + 10], blg[N + 10], b[N + 10], clk, psz;
vector<pair<int, int> > g[N + 10];
vector<int> brg, stk, h[N + 10];
void tarjan(int u, int f) {
	dfn[u] = low[u] = ++clk; stk.push_back(u);
	for (auto [v, i] : g[u]) {
		if (!dfn[v]) tarjan(v, i), low[u] = min(low[u], low[v]);
		else if (i != f) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		if (f != 0) brg.push_back(f);
		++psz;
		while (true) {
			int v = stk.back(); stk.pop_back();
			blg[v] = psz, b[psz] += a[v];
			if (v == u) break;
		}
	}
}
pair<int, int> e[N + 10];
void testout(int u, int p) {
	cout << u << " " << p << "\n";
	for (int v : h[u]) if (v != p) testout(v, u);
}
void dfs(int u, int p) {
	for (int v : h[u]) if (v != p) {
		dfs(v, u), b[u] += b[v];
	}
}
intl ans = inf;
void getans(int u, int p) {
	for (int v : h[u]) if (v != p) {
		intl x = b[v], y = b[1] - b[v];
		ans = min(ans, abs(x - y));
		getans(v, u);
	}
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		e[i] = {u, v};
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	} int cnt = 0;
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0), ++cnt;
	if (cnt == 2) {
		cout << abs(b[1] - b[2]) << "\n";
	} else if (cnt == 1) {
		for (int i : brg) {
			auto [u, v] = e[i];
			h[blg[u]].push_back(blg[v]);
			h[blg[v]].push_back(blg[u]);
		} dfs(1, 0), getans(1, 0);
		cout << ans << "\n";
	} else cout << "-1\n";
	return 0;
}
