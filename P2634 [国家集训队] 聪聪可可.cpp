#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 20000;
vector< pair<int, int> > g[N + 10];
int n, siz[N + 10];
bool del[N + 10];
void gsz(int u, int p) {
	if (siz[u] = 0, del[u]) return;
	siz[u] = 1;
	for (auto [v, w] : g[u]) if (v != p)
		gsz(v, u), siz[u] += siz[v];
}
int gct(int u, int p, const int& sz) {
	if (del[u]) return 0;
	for (auto [v, w] : g[u]) if (v != p)
		if (siz[v] << 1 > sz) return gct(v, u, sz);
	return u;
}
void gvl(int u, int p, int d, vector<intl>& res) {
	if (del[u]) return;
	++res[d %= 3];
	for (auto [v, w] : g[u]) if (v != p)
		gvl(v, u, (d + w) % 3, res);
}
intl dfs(int u) {
	if (del[u]) return 0;
	gsz(u, 0); int c = gct(u, 0, siz[u]);
	intl ans = 0;
	vector<intl> now = {1, 0, 0};
	for (auto [v, w] : g[c]) {
		vector<intl> res(3);
		gvl(v, c, w % 3, res);
		ans += now[0] * res[0] + now[1] * res[2] + now[2] * res[1];
		now[0] += res[0], now[1] += res[1], now[2] += res[2];
	} del[c] = true;
	for (auto [v, w] : g[c]) ans += dfs(v);
	return ans;
}
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	intl p = dfs(1) * 2 + intl(n), q = intl(n) * n, d = gcd(p, q);
	cout << p / d << "/" << q / d << "\n";
	return 0;
}
