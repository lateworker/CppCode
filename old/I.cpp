#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 100000;
int n, m, dfn[N + 10], low[N + 10], siz[N + 10], deg[N + 10], psz;
vector<pair<int, intl> > g[N + 10], gn[N + 10];
void tarjan(int u, int p) {
	low[u] = dfn[u] = ++psz, siz[u] = 1;
	for (auto e : g[u]) {
		int v; intl w; tie(v, w) = e;
		if (v == p) continue;
		if (dfn[v]) chkmin(low[u], dfn[v]);
		else {
			tarjan(v, u), chkmin(low[u], low[v]), siz[u] += siz[v];
			if (dfn[v] == low[v]) {
				intl wn = w * siz[v] * (n - siz[v]);
				gn[u].emplace_back(v, wn), ++deg[u];
				gn[v].emplace_back(u, wn), ++deg[v];
			}
		}
	}
}
intl a[N + 10];
bitset<N + 10> vis;
void dfs(int u, bool& res, const intl& cap) {
	vis[u] = true;
	for (auto e : gn[u]) {
		int v; intl w; tie(v, w) = e;
		if (vis[v]) continue;
		dfs(v, res, cap);
		intl det = min(w, cap - a[v]);
		a[v] += det, a[u] += w - det;
		if (a[u] > cap) { res = false; break; }
	}
}
bool check(intl cap) {
	for (int i = 1; i <= n; i++) a[i] = vis[i] = 0;
	for (int i = 1; i <= n; i++) {
		bool res = true;
		if (!vis[i] && deg[i] >= 2) dfs(i, res, cap);
		if (!res) return false;
	}
	for (int i = 1; i <= n; i++) {
		bool res = true;
		if (!vis[i] && deg[i] == 1) dfs(i, res, cap);
		if (!res) return false;
	}
	return true;
}
int main() { ffopen();
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v; intl w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	tarjan(1, 0);
	intl l = 0, r = intl(1e15);
	while (l < r) {
		intl mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << '\n';
	return 0;
}
