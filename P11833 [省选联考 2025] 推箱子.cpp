#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200000;
using intl = long long;
intl n, tn, a[N + 10], b[N + 10], t[N + 10];
struct Segt { intl val, lef, rit; } st[N * 4 + 10];
int tg[N * 4 + 10], sz[N * 2 + 10];
Segt operator + (const Segt& a, const Segt& b) { return {a.val + b.val, a.lef ? a.lef : b.lef, b.rit ? b.rit : a.rit}; }
void pushup(int u) {
	if (!u) return;
	st[u] = st[u << 1] + st[u << 1 | 1];
}
void modify(int u, intl val) {
	st[u] = {val * sz[u] + sz[u] * (sz[u] - 1) / 2, val, val + sz[u] - 1};
	tg[u] = val;
}
void pushdown(int u) {
	if (tg[u]) {
		modify(u << 1, tg[u]);
		modify(u << 1 | 1, tg[u] + sz[u << 1]);
		tg[u] = 0;
	}
}
void build() {
	for (tn = 1; tn <= n + 1; tn <<= 1);
	for (int i = 1; i <= n; i++) st[i + tn] = {a[i], a[i], a[i]}, sz[i + tn] = 1;
	for (int u = n - 1; u; u--) pushup(u), sz[u] = sz[u << 1] + sz[u << 1 | 1];
}
void update(int l, int r, int val) {
	int lf = l;
	auto gw = [&](int u) { return val + (u << (__lg(tn) - __lg(u))) - tn - lf; };
	l += tn, r += tn + 1;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l, gw(l)), l++;
		if (r & 1) v = r, --r, modify(r, gw(r));
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	}
}
Segt query(int l, int r) {
	if (r < l) return {0, 0, 0};
	l += tn, r += tn + 1;
	for (int i = __lg(tn); i; i--) pushdown(l >> i), pushdown(r >> i);
	Segt res = {0, 0, 0};
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = st[l++] + res;
		if (r & 1) res = res + st[--r];
	} return res;
}
int queryR(int u, int l, int r, int i, int bi, Segt& res) {
	Segt now = res + st[u];
	if (l >= i && now.rit < bi + r - i) return res = now, r;
	if (l == r) return l - 1;
	pushdown(u, l, r);
	int mid = (l + r) >> 1, pp = n;
	if (i <= mid) pp = queryR(le, l, mid, i, bi, res);
	return pp < mid ? pp : queryR(ri, mid + 1, r, i, bi, res);
}
int queryL(int u, int l, int r, int i, int bi, Segt& res) {
	Segt now = st[u] + res;
	if (r <= i && now.lef > bi - i + l) return res = now, l;
	if (l == r) return r + 1;
	pushdown(u, l, r);
	int mid = (l + r) >> 1, pp = 1;
	if (mid < i) pp = queryL(ri, mid + 1, r, i, bi, res);
	return pp > mid + 1 ? pp : queryL(le, l, mid, i, bi, res);
}
intl calc(int l, int r, intl tar) {
	intl s = tar, t = tar + r - l;
	return (t + s) * (t - s + 1) / 2;
}
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i] >> t[i];
	build();
	vector<int> idx(n);
	iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return t[i] < t[j]; } );
	int now = 0; bool ans = true;
	for (int i : idx) {
		intl ai = query(i, i).val;
		if (b[i] == ai) continue;
		Segt res = {0, 0, 0};
		if (b[i] > ai) {
			int pp = queryR(1, 1, n, i, b[i], res);
			int delt = calc(i, pp, b[i]) - res.val;
			now += delt;
			update(i, pp, b[i]);
		}
		if (b[i] < ai) {
			int pp = queryL(1, 1, n, i, b[i], res);
			int delt = res.val - calc(pp, i, b[i] - (i - pp));
			now += delt;
			update(pp, i, b[i] - (i - pp));
		}
		if (now > t[i]) { ans = false; break; }
	}
	cout << (ans ? "Yes" : "No") << "\n";
}
void celar() {
	memset(tg, 0, sizeof tg);
}
signed main() {
	cin.tie(0)->sync_with_stdio(0);
	int c, T;
	cin >> c >> T;
	while (T--) slove(), celar();
	return 0;
}
