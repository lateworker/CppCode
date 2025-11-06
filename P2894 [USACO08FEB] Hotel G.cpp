#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
const int N = 50000;
int n, m, tn;
short tg[N * 3 + 10];
struct segt { int ma, len, lma, rma; } st[N * 3 + 10];
segt merge(const segt& a, const segt& b) {
	return {
		max({a.ma, b.ma, a.rma + b.lma}),
		a.len + b.len,
		a.lma == a.len ? a.len + b.lma : a.lma,
		b.rma == b.len ? b.len + a.rma : b.rma
	};
}
void pushup(int u) { if (u) st[u] = merge(st[u << 1], st[u << 1 | 1]); }
void modify(int u, const short& val) {
	st[u].ma = st[u].lma = st[u].rma = int(val & 1) * st[u].len;
	tg[u] = val;
}
void pushdown(int u) {
	if (tg[u]) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u]);
		tg[u] = 0;
	}
}
void update(int l, int r, const short& val) {
	l += tn - 1, r += tn;
	for (int d = __lg(tn); d; d--) pushdown(l >> d), pushdown(r >> d);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	}
}
int query(int x) {
	int u = 1, l = 0, r = tn - 1;
	while (u < tn) {
		pushdown(u);
		int mid = (l + r) >> 1;
		if (st[u << 1].ma >= x) u = u << 1, r = mid;
		else if (st[u << 1].rma + st[u << 1 | 1].lma >= x) return mid - st[u << 1].rma + 2;
		else u = u << 1 | 1, l = mid + 1;
	} return u - tn + 1;
}
int main() { ffopen();
	cin >> n >> m;
	for (tn = 1; tn <= n; tn <<= 1);
	for (int i = 1; i <= n; i++) st[i + tn - 1] = {1, 1, 1, 1};
	for (int u = tn - 1; u; u--) pushup(u);
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		cin >> op >> x;
		if (op == 1) {
			if (st[1].ma < x) { cout << "0\n"; continue; }
			int pos = query(x);
			update(pos, pos + x - 1, 2);
			cout << pos << "\n";
		} else {
			cin >> y;
			update(x, x + y - 1, 1);
		}
	}
	return 0;
}
