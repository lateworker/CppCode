#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const intl N = 2000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m;
intl lim, f[N + 10][2];
struct Segt {
	intl st[N * 3 + 10], tg[N * 3 + 10]; int tn;
	void pushup(int u) { if (u) st[u] = max(st[u << 1], st[u << 1 | 1]); }
	void modify(int u, intl val) { st[u] += val, tg[u] += val; }
	void pushdown(int u) { if (tg[u]) modify(u << 1, tg[u]), modify(u << 1 | 1, tg[u]), tg[u] = 0; }
	void build(int n) {
		for (tn = 1; tn <= n + 1; tn <<= 1);
		memset(st, 0xc0, (tn + n + 3) * sizeof(*st));
		memset(tg, 0, (tn + n + 3) * sizeof(*tg));
	}
	void update(int u, intl val) {
		u += tn;
		for (int i = __lg(tn); i; i--) pushdown(u >> i);
		chkmax(st[u], val);
		do pushup(u >>= 1); while (u);
	}
	void update(int l, int r, intl val) {
		if (r < l) return;
		l += tn, r += tn + 1;
		for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
		for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
			if (l & 1) u = l, modify(l++, val);
			if (r & 1) v = r, modify(--r, val);
			do pushup(u >>= 1); while (l == r && u);
			do pushup(v >>= 1); while (l == r && v);
		}
	}
	intl query(int l, int r) {
		if (r < l) return -inf;
		l += tn, r += tn + 1;
		for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
		intl res = -inf;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) chkmax(res, st[l++]);
			if (r & 1) chkmax(res, st[--r]);
		} return res;
	}
} st[N + 10][2];
vector<pair<int, intl> > seg[N + 10];
int main() { ffopen();
	cin >> n >> m >> lim;
	intl sum = 0; int maxlen = 0;
	for (int i = 1; i <= n; i++) {
		int lx, rx; intl a;
		cin >> lx >> rx >> a;
		chkmax(maxlen, rx - lx + 1);
		sum += a, seg[rx].emplace_back(lx, a);
	}
	for (int j = 0; j <= m; j++) {
		st[j][0].build(m);
		st[j][1].build(m);
	} memset(f, 0xc0, sizeof f);
	f[0][0] = 0, st[0][0].update(0, 0);
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j <= i; j++) {
			for (auto [pos, val] : seg[i]) {
				st[j][0].update(0, pos - 1, val);
				st[j][1].update(0, pos - 1, val);
			}
		}
		for (int j = i; j >= 1; j--) {
			f[j][0] = f[j - 1][0];
			f[j][1] = f[j - 1][1];
		} f[0][0] = f[0][1] = -inf;
		for (int j = 0; j <= i; j++) {
			int p = max(i - maxlen + 1, 0);
			chkmax(f[j][1], max(st[j][0].query(0, p - 1), st[j][1].query(0, p - 1)));
			chkmax(f[j][0], st[j][0].query(p, i - 1));
			chkmax(f[j][1], st[j][1].query(p, i - 1));
			st[j][0].update(i, f[j][0]);
			st[j][1].update(i, f[j][1]);
		}
	}
	for (int j = m; j >= 0; j--) {
		if (sum - f[j][1] <= lim)
			{ cout << j << '\n'; break; }
	}
	return 0;
}
