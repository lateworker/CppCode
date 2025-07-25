#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 50000, Mod = 201314;
int n, m, fa[N + 10], dep[N + 10], siz[N + 10], son[N + 10], top[N + 10], dfn[N + 10], psz, ans[N + 10];
vector<int> g[N + 10];
vector<pair<int, int>> qry[N + 10];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1, siz[u] = 1;
	for (int v : g[u]) {
		dfs(v);
		siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}
void build(int u, int t) {
	top[u] = t, dfn[u] = ++psz;
	if (son[u]) build(son[u], t);
	for (int v : g[u]) if (v != son[u]) build(v, v);
}
struct Segt {
	int st[N * 4 + 10], tg[N * 4 + 10];
	void pushup(int u) { st[u] = st[u << 1] + st[u << 1 | 1]; }
	void modify(int u, int l, int r, int val) {
		st[u] += (r - l + 1) * val;
		tg[u] += val;
	}
	void pushdown(int u, int l, int r) {
		if (tg[u]) {
			int mid = (l + r) >> 1;
			modify(u << 1, l, mid, tg[u]);
			modify(u << 1 | 1, mid + 1, r, tg[u]);
			tg[u] = 0;
		}
	}
	void update(int u, int l, int r, int lf, int rt, int val) {
		if (lf <= l && r <= rt) return modify(u, l, r, val);
		pushdown(u, l, r);
		int mid = (l + r) >> 1;
		if (lf <= mid) update(u << 1, l, mid, lf, rt, val);
		if (mid < rt) update(u << 1 | 1, mid + 1, r, lf, rt, val);
		pushup(u);
	}
	int query(int u, int l, int r, int lf, int rt) {
		if (lf <= l && r <= rt) return st[u];
		pushdown(u, l, r);
		int mid = (l + r) >> 1;
		if (rt <= mid) return query(u << 1, l, mid, lf, rt);
		if (mid < lf) return query(u << 1 | 1, mid + 1, r, lf, rt);
		return query(u << 1, l, mid, lf, rt) + query(u << 1 | 1, mid + 1, r, lf, rt);
	}
} st;
void treeupdate(int u, int val) {
	while (u) {
		st.update(1, 1, n, dfn[top[u]], dfn[u], val);
		u = fa[top[u]];
	}
}
int treequery(int u) {
	int res = 0;
	while (u) {
		res += st.query(1, 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	} return res;
}
int main() {
	cin >> n >> m;
	for (int i = 2; i <= n; i++) {
		cin >> fa[i]; fa[i]++;
		g[fa[i]].push_back(i);
	} dfs(1), build(1, 1);
	for (int i = 1; i <= m; i++) {
		int l, r, z; cin >> l >> r >> z;
		++l, ++r, ++z;
		qry[r].emplace_back(z, i);
		qry[l - 1].emplace_back(z, -i);
	}
	for (int i = 1; i <= n; i++) {
		treeupdate(i, 1);
		for (auto [u, idx] : qry[i]) {
			ans[abs(idx)] += (idx < 0 ? -1 : 1) * treequery(u);
		}
	}
	for (int i = 1; i <= m; i++) cout << ans[i] % Mod << "\n";
	return 0;
}
