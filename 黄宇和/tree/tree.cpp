#include <bits/stdc++.h>
#define int long long
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 100000;
int q, n, a[N + 10][2], fa[N + 10], son[N + 10], siz[N + 10], dep[N + 10], dfn[N + 10], idfn[N + 10], top[N + 10], psz;
vector<int> g[N + 10];
int isq[N + 10];
void dfs(int u) {
	a[u][1] = a[fa[u]][0];
	siz[u] = 1, dep[u] = dep[fa[u]] + 1;
	for (int v : g[u]) {
		dfs(v);
		siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}
void build(int u, int t) {
	for (int i : {0, 1}) a[u][i] += a[fa[u]][i];
	top[u] = t, dfn[u] = ++psz, idfn[dfn[u]] = u;
	if (son[u]) build(son[u], t);
	for (int v : g[u]) if (v != son[u]) build(v, v);
}

int st[N * 4 + 10][2], tg[N * 4 + 10];
void pushup(int u) {
	for (int i : {0, 1})
		st[u][i] = st[u << 1][i] + st[u << 1 | 1][i];
}
void modify(int u, int l, int r, int val) {
	for (int i : {0, 1})
		st[u][i] += (a[idfn[r]][i] - a[fa[idfn[l]]][i]) * val;
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
int query(int u, int l, int r, int lf, int rt, int i) {
	if (lf <= l && r <= rt) return st[u][i];
	pushdown(u, l, r);
	int mid = (l + r) >> 1;
	if (rt <= mid) return query(u << 1, l, mid, lf, rt, i);
	if (mid < lf) return query(u << 1 | 1, mid + 1, r, lf, rt, i);
	return query(u << 1, l, mid, lf, rt, i) + query(u << 1 | 1, mid + 1, r, lf, rt, i);
}
void tupdate(int u) {
	while (u) {
		update(1, 1, n, dfn[top[u]], dfn[u], 1);
		u = fa[top[u]];
	}
}
int tquery(int u, int i) {
	int res = 0;
	while (u) {
		res += query(1, 1, n, dfn[top[u]], dfn[u], i);
		u = fa[top[u]];
	} return res;
}

int ans;
signed main() {
	ffopen("tree");
	cin >> q >> a[++n][0];
	for (int i = 1; i <= q; i++) {
		int op; cin >> op;
		if (op == 1) {
			isq[i] = ++n;
			cin >> a[n][0] >> fa[n];
			g[fa[n]].push_back(n);
		}
	}
	dfs(1), build(1, 1);
	ans = a[1][0]; tupdate(1);
	for (int i = 1; i <= q; i++) {
//		cout << i << "\n";
		if (isq[i]) {
			ans += tquery(fa[isq[i]], 0) - tquery(isq[i], 1);
			ans += a[isq[i]][0] - a[fa[isq[i]]][0];
			tupdate(isq[i]);
		} else cout << ans << "\n";
	}
	return 0;
}
