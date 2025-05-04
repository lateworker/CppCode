#include <bits/stdc++.h>
using namespace std;
const int N = 10000, M = 100;
int n, m, d[M + 10];
vector<pair<int, int> > g[N + 10];
int siz[N + 10];
bool del[N + 10], ans[M + 10];
void calcSiz(int u, int p) {
	siz[u] = 0;
	if (del[u]) return;
	siz[u] = 1;
	for (auto [v, w] : g[u]) if (v != p) {
		calcSiz(v, u);
		siz[u] += siz[v];
	}
}
int calcCenter(int u, int p, const int& n) {
	if (del[u]) return 0;
	for (auto [v, w] : g[u]) if (v != p)
		if (siz[v] * 2 > n) return calcCenter(v, u, n);
	return u;
}
void dfs(int u, int p, int d, vector<int>& res) {
	res.push_back(d);
	if (del[u]) return;
	for (auto [v, w] : g[u]) if (v != p)
		dfs(v, u, d + w, res);
}
void solve(int u) {
	if (del[u]) return;
	calcSiz(u, 0);
	int c = calcCenter(u, 0, siz[u]);
	set<int> bst; bst.insert(0);
	for (auto [v, w] : g[c]) {
		vector<int> res;
		auto dfs = [&](int u, int p, int dd, auto dfs) -> void {
			res.push_back(dd);
			for (int i = 1; i <= m; i++)
				if (bst.count(d[i] - dd)) ans[i] = true;
			for (auto [v, w] : g[u])
				if (v != p) 
		}
		dfs(v, c, w, res);
		for (int i = 1; i <= m; i++)
			for (int x : res)
				if (bst.count(d[i] - x)) ans[i] = true;
		for (int x : res) bst.insert(x);
	} del[c] = true;
	for (auto [v, w] : g[c]) solve(v);
}
int main() {
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	for (int i = 1; i <= m; i++) cin >> d[i];
	solve(1);
	for (int i = 1; i <= m; i++) cout << (ans[i] ? "AYE" : "NAY") << "\n";
	return 0;
}
