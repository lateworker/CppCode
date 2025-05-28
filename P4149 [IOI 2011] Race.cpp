#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const intl N = 200000, M = 1000000, inf = 0x3f3f3f3f3f3f3f3f;
intl n, m, ans = inf;
vector< pair<intl, intl> > g[N + 10];
int siz[N + 10];
bool del[N + 10];
void gsiz(int u, int p) {
	if (siz[u] = 0, del[u]) return;
	siz[u] = 1;
	for (auto [v, w] : g[u]) if (v != p) gsiz(v, u), siz[u] += siz[v];
}
int gcet(int u, int p, const int& t) {
	if (del[u]) return 0;
	for (auto [v, w] : g[u]) if (v != p)
		if (siz[v] << 1 > t) return gcet(v, u, t);
	return u;
}
void dfs(int u, int p, intl dis, intl dep, vector< pair<intl, intl> >& res) {
	if (del[u] || dis > m) return;
	res.emplace_back(dis, dep);
	for (auto [v, w] : g[u]) if (v != p)
		dfs(v, u, dis + w, dep + 1, res);
}
template<class T_, size_t N_, T_ DEFAULT>
struct Array {
	T_ dat[N_];
	size_t ver[N_], clk;
	Array() { clk = 1; }
	void clear() { ++clk; }
	T_& operator[] (size_t i) {
		if (ver[i] != clk) ver[i] = clk, dat[i] = DEFAULT;
		return dat[i];
	}
};
Array<intl, M + 10, inf> now;
void solve(int u) {
	if (del[u]) return;
	gsiz(u, 0); int cet = gcet(u, 0, siz[u]);
	now[0] = 0;
	for (auto [v, w] : g[cet]) {
		vector< pair<intl, intl> > res; dfs(v, cet, w, 1, res);
		for (auto [dis, dep] : res) ans = min(ans, now[m - dis] + dep);
		for (auto [dis, dep] : res) now[dis] = min(now[dis], dep);
	} del[cet] = true, now.clear();
	for (auto [v, w] : g[cet]) solve(v);
}
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		intl u, v, w; cin >> u >> v >> w; ++u, ++v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	} solve(1);
	cout << (ans == inf ? -1 : ans) << "\n";
	return 0;
}
