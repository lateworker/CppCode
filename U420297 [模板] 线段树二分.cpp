#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 1000000, LN = __lg(N) + 1;
int n, tn, m, sz[N * 3 + 10];
intl st[N * 3 + 10], tg[N * 3 + 10];
void pushup(int u) { if (u) st[u] = st[u << 1] + st[u << 1 | 1]; }
void modify(int u, intl val) { st[u] += val * sz[u], tg[u] += val; }
void pushdown(int u) {
	if (tg[u]) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u]);
		tg[u] = 0;
	}
}
void update(int l, int r, intl val) {
	l += tn - 1, r += tn;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	}
}
void update(int u, intl val) {
	u += tn - 1;
	for (int i = __lg(tn); i; i--) pushdown(u >> i);
	st[u] = val; do pushup(u >>= 1); while (u);
}
intl query(int l, int r) {
	l += tn - 1, r += tn;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = 0;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += st[l++];
		if (r & 1) res += st[--r];
	} return res;
}
int fullbs(int u, intl x, intl prf) {
	while (u < tn) {
		pushdown(u);
		intl now = prf + st[u <<= 1];
		if (now < x) prf = now, u ^= 1;
	} return u - tn + 1;
}
int lowerbs(int l, int r, intl x) {
	static int rps[LN + 3];
	l += tn - 1, r += tn, *rps = 0;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	intl prf = 0;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) {
			int u = l++;
			intl now = prf + st[u];
			if (now >= x) return fullbs(u, x, prf);
			prf = now;
		}
		if (r & 1) rps[++*rps] = --r;
	}
	for (; *rps; --*rps) {
		int u = rps[*rps];
		intl now = prf + st[u];
		if (now >= x) return fullbs(u, x, prf);
		prf = now;
	}
	return r + 1;
}
int main() { ffopen();
	cin >> n >> m;
	for (tn = 1; tn <= n; tn <<= 1);
	for (int i = 1; i <= n; i++) {
		cin >> st[i + tn - 1];
		sz[i + tn - 1] = 1;
	}
	for (int u = tn - 1; u; u--) pushup(u), sz[u] = sz[u << 1] + sz[u << 1 | 1];
	for (int i = 1; i <= m; i++) {
		int op, x, y; intl z;
		cin >> op;
		if (op == 1) { cin >> x >> y >> z; update(x, y, z); }
		else if (op == 2) { cin >> x >> y; cout << query(x, y) << "\n"; }
		else if (op == 3) { cin >> x >> y >> z; cout << lowerbs(x, y, z) << "\n"; }
		else if (op == 4) { cin >> x >> z; update(x, z); }
	}
	return 0;
}
