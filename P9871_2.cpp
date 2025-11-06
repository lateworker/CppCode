#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
using intl = long long;
const intl M = 100000, N = 100000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m, k;
vector<pair<int, int> > qry[N + 10];
intl st[N * 2 + 10], tg[N * 2 + 10], d;
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
	l += n, r += n + 1;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = -inf;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) chkmax(res, st[l++]);
		if (r & 1) chkmax(res, st[--r]);
	} return res;
}
vector<int> vec;
void slove() {
	cin >> n >> m >> k >> d;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (y > k) continue;
		int r = x, l = x - y;
		qry[r].emplace_back(l, z);
	}
//	for (int i = 2; i <= n; i++) vec.push_back(i);
//	sort(vec.begin(), vec.end());
//	vec.erase(unique(vec.begin(), vec.end()), vec.end());
//	n = vec.size() - 1;
	for (int i = 1; i <= (n << 1); i++) st[i] = -inf, tg[i] = 0;
	intl ans = 0, f = 0;
	modifyMax(0, 0);
	for (int i = 1; i <= n; i++) {
		modifyMax(i, f + d * i);
		for (const auto& [j, v] : qry[i]) updateAdd(0, j, v);
		chkmax(ans, chkmax(f, queryMax(max(i - k, 0), i - 1) - d * i));
	}
	cout << ans << "\n";
}
int main() { ffopen(run/run2);
	int C, T; cin >> C >> T;
	while (T--) {
		vec = {0, 1};
		slove();
		for (int i = 1; i <= n; i++) qry[i].clear();
	}
	return 0;
}
