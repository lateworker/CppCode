#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 100000;
int n, tn, m;
intl st[N * 2 + 10], tg[N * 2 + 10], sz[N * 2 + 10];
void pushup(int u) {
	st[u] = st[u << 1] + st[u << 1 | 1];
}
void modify(int u, intl val) {
	st[u] += sz[u] * val;
	tg[u] += val;
}
void pushdown(int u) {
	if (tg[u]) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u]);
		tg[u] = 0;
	}
}
void update(int l, int r, intl val) {
	l += tn - 1, r += tn + 1;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	for (; l ^ r ^ 1; pushup(l >>= 1), pushup(r >>= 1)) {
		if (~l & 1) modify(l ^ 1, val);
		if (r & 1) modify(r ^ 1, val);
	} while (l >>= 1) pushup(l);
}
intl query(int l, int r) {
	l += tn - 1, r += tn + 1;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = 0;
	for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) res += st[l ^ 1];
		if (r & 1) res += st[r ^ 1];
	} return res;
}
int main() { ffopen();
	cin >> n >> m;
	for (tn = 1; tn <= n + 1; tn <<= 1);
	for (int i = 1; i <= n; i++) {
		cin >> st[i + tn];
		sz[i + tn] = 1;
	}
	for (int i = tn - 1; i; i--) {
		st[i] = st[i << 1] + st[i << 1 | 1];
		sz[i] = sz[i << 1] + sz[i << 1 | 1];
	}
	for (int i = 1; i <= m; i++) {
		int op; cin >> op;
		if (op == 1) {
			intl x, y, k;
			cin >> x >> y >> k;
			update(x, y, k);
		} else {
			int x, y;
			cin >> x >> y;
			cout << query(x, y) << "\n";
		}
	}
	return 0;
}
