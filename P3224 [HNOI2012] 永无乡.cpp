#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
const int N = 100000, LN = __lg(N) + 1;
struct Segt {
	int val;
	Segt *le, *ri;
	Segt() { le = ri = this, val = 0; }
} pool[N * LN + 10]; int psz;
Segt* node() {
	Segt* u = pool + ++psz;
	u->le = u->ri = pool;
	return u;
}
void pushup(Segt* u) { u->val = u->le->val + u->ri->val; }
void update(Segt*& u, int l, int r, int pos, int val) {
	if (u == pool) u = node();
	if (l == r) { u->val += val; return; }
	int mid = (l + r) >> 1;
	pos <= mid ? update(u->le, l, mid, pos, val) : update(u->ri, mid + 1, r, pos, val);
	pushup(u);
}
Segt* merge(Segt* u, Segt* v, int l, int r) {
	if (u == pool) return v;
	if (v == pool) return u;
	if (l == r) { u->val += v->val; return u; }
	int mid = (l + r) >> 1;
	u->le = merge(u->le, v->le, l, mid);
	u->ri = merge(u->ri, v->ri, mid + 1, r);
	pushup(u); return u;
}
int n, m, q, fa[N + 10], invp[N + 10];
Segt* root[N + 10];
int query(Segt* u, int k) {
	int prf = 0, l = 1, r = n;
	while (l < r) {
		int now = prf + u->le->val, mid = (l + r) >> 1;
		if (now < k) prf = now, u = u->ri, l = mid + 1;
		else u = u->le, r = mid;
		if (u == pool) return -1;
	} return invp[l];
}
int findf(int u) { return fa[u] == u ? u : fa[u] = findf(fa[u]); }
void link(int u, int v) {
	u = findf(u), v = findf(v);
	if (u == v) return;
	fa[v] = u, root[u] = merge(root[u], root[v], 1, n);
}
int main() { ffopen();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int p; cin >> p;
		update(root[i] = pool, 1, n, p, 1);
		invp[p] = fa[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		link(u, v);
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		char op; int x, y;
		cin >> op >> x >> y;
		if (op == 'Q') {
			cout << query(root[findf(x)], y) << "\n";
		} else link(x, y);
	}
	return 0;
}
