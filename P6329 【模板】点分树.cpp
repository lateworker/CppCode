#include <bits/stdc++.h>
using namespace std;
const int N = 100000, L = __lg(N + 1) + 1;
int n, m, a[N + 10];
vector<int> g[N + 10];
int dep[N + 10], dfn[N + 10], ST[N + 10][L + 1], psz;
void gST(int u, int p) {
	dep[u] = dep[p] + 1, ST[dfn[u] = ++psz][0] = p;
	for (int v : g[u]) if (v != p) gST(v, u);
}
int minST(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
int LCA(int u, int v) {
	if (u == v) return u;
	u = dfn[u], v = dfn[v];
	if (u > v) swap(u, v);
	int d = __lg(v - u); ++u;
	return minST(ST[u][d], ST[v - (1 << d) + 1][d]);
}
int gdis(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }
bool del[N + 10];
int siz[N + 10], vfa[N + 10];
void gsiz(int u, int p) {
	if (siz[u] = 0, del[u]) return;
	siz[u] = 1;
	for (int v : g[u]) if (v != p)
		gsiz(v, u), siz[u] += siz[v];
}
int gcet(int u, int p, const int& szt) {
	if (del[u]) return 0;
	for (int v : g[u]) if (v != p)
		if (siz[v] << 1 > szt) return gcet(v, u, szt);
	return u;
}
void build(int u, int p) {
	if (del[u]) return;
	gsiz(u, 0); int c = gcet(u, 0, siz[u]);
	vfa[c] = p, del[c] = true;
	for (int v : g[c]) build(v, c);
}
struct Tnum {
	vector<int> dat;
	void modify(int pos, int val);
	int query(int pos);
};
void Tnum::modify(int pos, int val) {
	if (pos + 1 > (int) dat.size()) dat.resize(pos + 1);
	for (int u = pos; u < (int) dat.size(); u++) dat[u] += val;
}
void update(int pos, int val) {
	for (int u = pos; u; u = vfa[u]) {
		
	}
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	gST(1, 0);
	for (int j = 1; j <= L; j++)
		for (int i = 1; i <= n - (1 << j) + 1; i++)
			ST[i][j] = minST(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
	build(1, 0);
	
	for (int i = 1; i <= n; i++) cout << vfa[i] << " \n"[i == n];
	return 0;
}
