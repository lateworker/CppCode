#include <bits/stdc++.h>
#define C__ const
#define int long long
using namespace std;
C__ int N_ = 1e5 + 10;
int n, m, a[N_];
int st[N_ << 2], tg[N_ << 2], tn, td;
#define le (u << 1)
#define ri (u << 1 | 1)
void pushup(int u) { if (u < tn) st[u] = st[le] + st[ri]; }
void modify(int u, int dep, int val) { st[u] += (1 << dep) * val, tg[u] += val; }
void pushdown(int u, int dep) {
	if (u < tn && tg[u]) {
		modify(le, dep - 1, tg[u]);
		modify(ri, dep - 1, tg[u]);
		tg[u] = 0;
	}
}
void build() {
	for (tn = 1, td = 0; tn <= n + 1; tn <<= 1, td++);
	for (int i = 1; i <= n; i++) st[i + tn] = a[i];
	for (int u = tn - 1; u; u--) pushup(u);
}
void maintain(int l, int r) {
	for (int dep = td; dep; dep--)
		pushdown(l >> dep, dep), pushdown(r >> dep, dep);
}
void update(int l, int r, int val) {
	maintain(l += tn, r += tn + 1);
	maintain(l - 1, r - 1);
	--l;
	for (int dep = 0; l ^ r ^ 1; l >>= 1, r >>= 1, dep++) {
		if (~ l & 1) modify(l ^ 1, dep, val);
		if (r & 1) modify(r ^ 1, dep, val);
		pushup(l), pushup(r);
	} for (pushup(r); l; l >>= 1) pushup(l);
}
int query(int l, int r) {
	maintain(l += tn, r += tn + 1);
	maintain(l - 1, r - 1);
	--l;
	int res = 0;
	for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~ l & 1) res += st[l ^ 1];
		if (r & 1) res += st[r ^ 1];
	} return res;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	build();
	while (m--) {
		int op, x, y, k;
		cin >> op >> x >> y;
		if (op == 1) cin >> k, update(x, y, k);
		if (op == 2) cout << query(x, y) << "\n";
	}
	return 0;
}
