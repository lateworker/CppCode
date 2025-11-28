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
const int M = 300000;
int n, m, fa[M + 10];
map<pii, int> g;
int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u != v) fa[u] = v;
}
pii dr[] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
pii operator+ (const pii& x, const pii& y) { return {x.first + y.first, x.second + y.second}; }
void slove() {
	cin >> n >> m;
	for (int i = 0; i <= m + 1; i++) fa[i] = i;
	g.clear();
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		g[{x, y}] = i;
	}
	for (auto [p, i] : g) {
		for (int c = 0; c < 8; c++) {
			pii np = p + dr[c];
			if (g.count(np)) merge(i, g[np]);
		}
		if (p.first == n || p.second == 1) merge(i, 0);
		if (p.first == 1 || p.second == n) merge(i, m + 1);
	}
	cout << (find(0) == find(m + 1) ? "nO" : "YeS") << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
