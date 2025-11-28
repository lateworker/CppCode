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
using pii = pair<int, int>;
const int N = 300000;
int n, k, stk[N + 10], pstk;
vector<int> g[N + 10], gn[N + 10];
bool isleaf(int u) { return u != 1 && g[u].size() == 1; }
void rebuild(int u, int p, int d) {
	stk[d] = u;
	if (isleaf(u)) {
		gn[u].push_back(stk[max(d - k, 1)]);
	}
	for (int v : g[u]) if (v != p) {
		gn[u].push_back(v);
		rebuild(v, u, d + 1);
	}
}
int dfn[N + 10], low[N + 10], bel[N + 10], psz;
int wei[N + 10], scc, f[N + 10];
void tarjan(int u) {
	stk[++pstk] = u;
	low[u] = dfn[u] = ++psz;
	for (int v : gn[u]) {
		if (!dfn[v]) tarjan(v), chkmin(low[u], low[v]);
		else if (!bel[v]) chkmin(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++scc;
		while (true) {
			int v = stk[pstk--];
			bel[v] = scc;
			wei[scc] += isleaf(v);
			if (u == v) break;
		}
	}
}
int dfs(int u) {
	if (~f[u]) return f[u];
	int ma = 0;
	for (int v : g[u]) {
		chkmax(ma, dfs(v));
	}
	return f[u] = ma + wei[u];
}
void slove() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	rebuild(1, 0, 1);
	tarjan(1);
	for (int i = 1; i <= n; i++) g[i].clear();
	for (int u = 1; u <= n; u++) {
		for (int v : gn[u]) {
			if (bel[u] == bel[v]) continue;
			g[bel[u]].push_back(bel[v]);
		}
	}
	memset(f, -1, (scc + 3) * sizeof(f[0]));
	cout << dfs(bel[1]) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) {
			g[i].clear();
			gn[i].clear();
			bel[i] = wei[i] = 0;
			dfn[i] = low[i] = 0;
		}
		psz = scc = pstk = 0;
	}
	return 0;
}
