#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 100, M = 500;
int n, m, a[N + 10], b[N + 10], fa[N + 10];
vector<int> g[N + 10];
vector<vector<int>> cir;
int vis[N + 10], clk;
void fcir(int u) {
	if (!u) return;
	vis[u] = clk;
	int v = fa[u];
	if (!vis[v]) return fcir(v);
	if (vis[v] == clk) {
		vector<int> vec;
		do vec.push_back(v); while((v = fa[v]) != u);
		vec.push_back(u);
		cir.push_back(vec);
	}
}
bool del[N + 10];
void build() {
	vector<int> tag(n + 3);
	for (const auto& vec : cir) {
		int t = vec.front();
		for (int i = 1; i < (int) vec.size(); i++) {
			int u = vec[i];
			tag[u] = t, del[u] = true;
			a[t] += a[u], b[t] += b[u];
		}
		fa[t] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (del[i]) continue;
		if (tag[fa[i]]) fa[i] = tag[fa[i]];
		g[fa[i]].push_back(i);
		g[i].push_back(fa[i]);
	}
}
int f[N + 10][M + 10];
void dfs(int u, int p) {
	for (int i = a[u]; i <= m; i++) f[u][i] = b[u];
	for (int v : g[u]) {
		if (v == p) continue;
		dfs(v, u);
		for (int i = m; i >= 0; i--) {
			for (int j = 0; j <= i; j++) {
				f[u][i] = max(f[u][i], f[u][i - j] + f[v][j]);
			}
		}
	}
}
int main() { ffopen();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> fa[i];
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		++clk, fcir(i);
	}
	build();
	memset(f, 0xc0, sizeof f);
	dfs(0, -1);
	cout << f[0][m] << "\n";
	return 0;
}
