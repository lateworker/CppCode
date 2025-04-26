#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 100000, A = 500000;
struct Treap { int lson, rson, idx, pri; } st[N * int(sqrt(A)) + 10]; int psz;
#define le(u) st[u].lson
#define ri(u) st[u].rson
int node(int idx) { st[++psz] = {0, 0, idx, rand()}; return psz; }
void split(int u, int idx, int& L, int& R) {
	if (u == 0) return L = R = 0, void();
	if (st[u].idx <= idx) L = u, split(ri(u), idx, ri(u), R);
	else R = u, split(le(u), idx, L, le(u));
}
int merge(int u, int v) {
	if (u == 0 || v == 0) return u + v;
	if (st[u].pri > st[v].pri) { ri(u) = merge(ri(u), v); return u; }
	else { le(v) = merge(u, le(v)); return v; }
}
int n, m, rt[A + 10];
intl a[N + 10], b[N + 10];
void tnumUpdate(int u, intl val) { for (; u <= n; u += u & -u) b[u] += val; }
intl tnumQuery(int u) { intl res = 0; for (; u; u -= u & -u) res += b[u]; return res; }
int dfs(int u, int x) {
	if (u == 0) return 0;
	int i = st[u].idx, L = le(u), R = ri(u), now = 0;
	if (a[i] % x == 0) {
		tnumUpdate(i, - a[i]);
		tnumUpdate(i, a[i] /= x);
		if (a[i] > 1) now = u, le(u) = ri(u) = 0;
	} return merge(merge(dfs(L, x), now), dfs(R, x));
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; tnumUpdate(i, a[i]);
		for (intl x = 2, y; x * x <= a[i]; x++) {
			if (a[i] % x) continue;
			rt[x] = merge(rt[x], node(i));
			if (x * x == a[i]) continue;
			y = a[i] / x;
			rt[y] = merge(rt[y], node(i));
		} rt[a[i]] = merge(rt[a[i]], node(i));
	}
	intl last = 0;
	for (int i = 1; i <= m; i++) {
		int op, l, r;
		cin >> op >> l >> r;
		l ^= last, r ^= last;
		if (op == 1) {
			intl x; cin >> x; x ^= last;
			if (x == 1) continue;
			int L, now, R;
			split(rt[x], r, L, R), split(L, l - 1, L, now);
			now = dfs(now, x);
			rt[x] = merge(merge(L, now), R);
		} else if (op == 2) {
			cout << (last = tnumQuery(r) - tnumQuery(l - 1)) << "\n";
		}
	}
	return 0;
}
