#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 100000;
intl n, m, Mod;
struct segt {
	intl val, siz, tagadd, tagmul;
	segt() { val = siz = tagadd = 0, tagmul = 1; }
} st[N * 2 + 10];
void pushup(int u) { st[u].val = (st[u << 1].val + st[u << 1 | 1].val) % Mod; }
void ModifyAdd(int u, intl val) {
	st[u].val += st[u].siz * val % Mod;
	st[u].tagadd += val;
	st[u].val %= Mod, st[u].tagadd %= Mod;
}
void ModifyMul(int u, intl val) {
	st[u].val *= val;
	st[u].tagadd *= val;
	st[u].tagmul *= val;
	st[u].val %= Mod, st[u].tagadd %= Mod, st[u].tagmul %= Mod;
}
void pushdown(int u) {
	if (st[u].tagmul != 1) {
		ModifyMul(u << 1, st[u].tagmul);
		ModifyMul(u << 1 | 1, st[u].tagmul);
		st[u].tagmul = 1;
	}
	if (st[u].tagadd) {
		ModifyAdd(u << 1, st[u].tagadd);
		ModifyAdd(u << 1 | 1, st[u].tagadd);
		st[u].tagadd = 0;
	}
}
void chkmax(int& x, const int& y) { x = max(x, y); }
void updateAdd(int l, int r, intl val) {
	l += n, r += n + 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	int u = 0, v = 0;
	while (l < r) {
		if (l & 1) chkmax(u, l), ModifyAdd(l++, val);
		if (r & 1) chkmax(v, r), ModifyAdd(--r, val);
		l >>= 1, r >>= 1;
	} while (u >>= 1) pushup(u); while (v >>= 1) pushup(v);
}
void updateMul(int l, int r, intl val) {
	l += n, r += n + 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	int u = 0, v = 0;
	while (l < r) {
		if (l & 1) chkmax(u, l), ModifyMul(l++, val);
		if (r & 1) chkmax(v, r), ModifyMul(--r, val);
		l >>= 1, r >>= 1;
	} while (u >>= 1) pushup(u); while (v >>= 1) pushup(v);
}
intl query(int l, int r) {
	l += n, r += n + 1;
	for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = 0;
	while (l < r) {
		if (l & 1) res += st[l++].val, res %= Mod;
		if (r & 1) res += st[--r].val, res %= Mod;
		l >>= 1, r >>= 1;
	} return res;
}
int main() { ffopen();
	cin >> n >> m >> Mod;
	for (int i = 1; i <= n; i++) {
		cin >> st[i + n].val;
		st[i + n].siz = 1;
	}
	for (int i = n - 1; i; i--) {
		st[i].val = (st[i << 1].val + st[i << 1 | 1].val) % Mod;
		st[i].siz = st[i << 1].siz + st[i << 1 | 1].siz;
	}
	for (int i = 1; i <= m; i++) {
		int op, x, y; intl k;
		cin >> op >> x >> y;
		if (op == 1) { cin >> k; updateMul(x, y, k); } else
		if (op == 2) { cin >> k; updateAdd(x, y, k); } else
		if (op == 3) { cout << query(x, y) << "\n"; }
	}
	return 0;
}
