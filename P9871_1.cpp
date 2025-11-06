#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int intl
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
using intl = long long;
const intl M = 200000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m, k;
struct Pair { int l, r, v; bool operator< (const Pair& b) const { return r < b.r; } } qry[M + 10];
intl st[M * 2 + 10], tg[M * 2 + 10], d;
void pushup(int u) { if (u) st[u] = max(st[u << 1], st[u << 1 | 1]); }
void modify(int u, intl val) { st[u] += val, tg[u] += val; }
void pushdown(int u) { if (tg[u]) modify(u << 1, tg[u]), modify(u << 1 | 1, tg[u]), tg[u] = 0; }
void updateAdd(int l, int r, intl val) {
	l += n, r += n + 1;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	}
}
void modifyMax(int u, intl val) {
	u += n;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(u >> i), chkmax(st[u >> i], val);
	chkmax(st[u], val);
}
intl queryMax(int l, int r) {
	if (l > r) return -inf;
	assert(l <= r);
	l += n, r += n + 1;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = -inf;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) chkmax(res, st[l++]);
		if (r & 1) chkmax(res, st[--r]);
	} return res;
}
vector<int> vec;
int lower(int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin(); }
void slove() {
	cin >> n >> m >> k >> d;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (y > k) continue;
		qry[i] = {x - y, x, z};
		vec.push_back(qry[i].l), vec.push_back(qry[i].r);
	}
	for (int i = 1; i <= n; i++) vec.push_back(i);
	sort(qry + 1, qry + m + 1);
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	n = vec.size() - 1;
	for (int i = 1; i <= (n << 1); i++) st[i] = -inf, tg[i] = 0;
	intl ans = 0, f = 0, ptr = 1;
	modifyMax(0, 0);
	for (int ii = 1; ii <= n; ii++) {
		const int& i = vec[ii];
		assert(ii == i);
		modifyMax(ii, f + (intl) d * i);
		for (; ptr <= m && qry[ptr].r == i; ++ptr) updateAdd(0, lower(qry[ptr].l), qry[ptr].v);
		chkmax(ans, chkmax(f, queryMax(lower(i - k), ii - 1) - (intl) d * i));
	}
	cout << ans << "\n";
}
signed main() { ffopen(run/run3);
	int C, T; cin >> C >> T;
	while (T--) {
		vec = {0};
		slove();
	}
	return 0;
}
