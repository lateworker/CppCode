#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000;
int n, m, tn, q;
vector<int> tim[M + 10], evt[N * 3 + 10];
pair<int, int> e[M + 10];
struct DSU {
	int fa[N + 10], siz[N + 10];
	vector<tuple<int, int, int, int> > rec;
	int find(int u) { return fa[u] == u ? u : find(fa[u]); }
	void merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return;
		if (siz[u] < siz[v]) swap(u, v);
		rec.emplace_back(u, v, fa[v], siz[u]);
		fa[v] = u, siz[u] += siz[v];
	}
	void undo() {
		auto [u, v, fav, sizu] = rec.back();
		fa[v] = fav, siz[u] = sizu;
		rec.pop_back();
	}
} dsu;
void update(int l, int r, int i) {
	for (l += tn - 1, r += tn; l < r; l >>= 1, r >>= 1) {
		if (l & 1) evt[l++].push_back(i);
		if (r & 1) evt[--r].push_back(i);
	}
}
bool ans[N + 10];
void cdq(int u, int l, int r) {
	if (l >= q) return;
	int siz = dsu.rec.size();
	for (int i : evt[u]) dsu.merge(e[i].first, e[i].second);
	if (l == r) ans[l + 1] = (dsu.siz[dsu.find(1)] == n);
	else {
		int mid = (l + r) >> 1;
		cdq(u << 1, l, mid);
		cdq(u << 1 | 1, mid + 1, r);
	}
	while ((int) dsu.rec.size() > siz) dsu.undo();
}
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) dsu.fa[i] = i, dsu.siz[i] = 1;
	for (int i = 1; i <= m; i++) cin >> e[i].first >> e[i].second;
	cin >> q;
	for (tn = 1; tn <= q; tn <<= 1);
	for (int i = 1; i <= q; i++) {
		int c; cin >> c;
		for (int j = 1; j <= c; j++) {
			int x; cin >> x;
			tim[x].push_back(i);
		}
	}
	for (int i = 1; i <= m; i++) tim[i].push_back(q + 1);
	for (int i = 1; i <= m; i++) {
		int la = 0;
		for (int j : tim[i]) {
			if (la + 1 <= j - 1) update(la + 1, j - 1, i);
			la = j;
		}
	}
	cdq(1, 0, tn - 1);
	for (int i = 1; i <= q; i++) cout << (ans[i] ? "Connected" : "Disconnected") << "\n";
	return 0;
}
