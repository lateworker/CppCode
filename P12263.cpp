#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 500000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m;
struct Segt {
	intl st[N * 2 + 10], tg[N * 2 + 10];
	void pushup(int u) { if (u) st[u] = min(st[u << 1], st[u << 1 | 1]); }
	void modify(int u, intl val) { st[u] += val, tg[u] += val; }
	void pushdown(int u) {
		if (tg[u]) {
			modify(u << 1, tg[u]);
			modify(u << 1 | 1, tg[u]);
			tg[u] = 0;
		}
	}
	void update(int l, int r, intl val) {
		l += n - 1, r += n;
		for (int i = __lg(n) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
		for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
			if (l & 1) u = l, modify(l++, val);
			if (r & 1) v = r, modify(--r, val);
			do pushup(u >>= 1); while (l == r && u);
			do pushup(v >>= 1); while (l == r && v);
		}
	}
} st1, st2;
int main() {
	cin >> n >> m;
	memset(st1.st, 0x3f, sizeof st1.st);
	memset(st2.st, 0x3f, sizeof st2.st);
	for (int i = 1; i <= n; i++) {
		intl x; cin >> x;
		st1.st[i + n - 1] = x;
		st2.st[i + n - 1] = x - i + 1;
	}
	for (int i = n - 1; i; i--) st1.pushup(i), st2.pushup(i);
	for (int i = 1; i <= m; i++) {
		int l, r; intl v;
		cin >> l >> r >> v;
		st1.update(l, r, v), st2.update(l, r, v);
		cout << st1.st[1] - max(0LL, st2.st[1]) + 1 << "\n";
	}
	return 0;
}
