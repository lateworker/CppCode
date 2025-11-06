#include <bits/stdc++.h>
using namespace std;
const int N = 40000;
int n, m, siz[N + 10], ans;
vector<pair<int, int> > g[N + 10];
bool del[N + 10];
void gsiz(int u, int p) {
	siz[u] = 0;
	if (del[u]) return;
	siz[u] = 1;
	for (auto [v, w] : g[u]) if (v != p)
		gsiz(v, u), siz[u] += siz[v];
}
int gcenter(int u, int p, const int& n) {
	if (del[u]) return 0;
	for (auto [v, w] : g[u]) if (v != p)
		if (siz[v] * 2 > n) return gcenter(v, u, n);
	return u;
}
void dfs(int u, int p, int d, vector<int>& vec) {
	if (del[u]) return;
	if (d <= m) vec.push_back(d);
	for (auto [v, w] : g[u]) if (v != p)
		dfs(v, u, d + w, vec);
}
int st[N + 10], ver[N + 10], clk;
void clean(int u) { if (ver[u] != clk) st[u] = 0, ver[u] = clk; }
void update(int u, int val) { u++; for (; u <= m + 1; u += u & -u) clean(u), st[u] += val; }
int query(int u) { u++; int res = 0; for (; u; u -= u & -u) clean(u), res += st[u]; return res; }
void solve(int u) {
	if (del[u]) return;
	gsiz(u, 0); int ctr = gcenter(u, 0, siz[u]); ++clk;
	for (auto [v, w] : g[ctr]) {
		vector<int> vec;
		dfs(v, ctr, w, vec);
		ans += vec.size();
		for (int x : vec) ans += query(m - x);
		for (int x : vec) update(x, 1);
	} del[ctr] = true;
	for (auto [v, w] : g[ctr]) solve(v);
}
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	} 
	cin >> m; solve(1);
	cout << ans << "\n";
	return 0;
}
