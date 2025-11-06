#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 100000;
int n, m;
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
	l += n, r += n + 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	} 
}
intl query(int l, int r) {
	l += n, r += n + 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = 0;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += st[l++];
		if (r & 1) res += st[--r];
	} return res;
}
int main() { ffopen();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> st[i + n];
		sz[i + n] = 1;
	}
	for (int i = n - 1; i; i--) {
		st[i] = st[i << 1] + st[i << 1 | 1];
		sz[i] = sz[i << 1] + sz[i << 1 | 1];
	}
	for (int i = 1; i <= m; i++) {
		int op, x, y; intl k;
		cin >> op >> x >> y;
		if (op == 1) { cin >> k; update(x, y, k); }
		if (op == 2) { cout << query(x, y) << "\n"; }
	}
	return 0;
}
