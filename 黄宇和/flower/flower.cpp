#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
const int N = 500000;
using namespace std;
int n, m, q, a[N + 10], b[N + 10], c[N + 10];
//map<int, int> merge(map<int, int>& x, map<int, int>& y) {
//	if (x.empty()) return y;
//	if (y.empty()) return x;
//	map<int, int> z = x;
//	for (auto& [u, v] : z) {
//		if (y.count(v)) v = y[v];
//	}
//	for (auto [u, v] : y) {
//		z[u] = v;
//	}
//	return z;
//}
//map<int, int> st[N * 2 + 10];
//map<int, int> query(int l, int r) {
//	map<int, int> res;
//	for (l += m - 1, r += m; l < r; l >>= 1, r >>= 1) {
//		if (l & 1) res = merge(st[l++], res);
//		if (r & 1) res = merge(res, st[--r]);
//	} return res;
//}
int main() { ffopen(flower);
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
//	for (int i = 1; i <= m; i++) st[m + i - 1][a[i]] = b[i];
//	for (int u = m - 1; u; u--) st[u] = merge(st[u << 1], st[u << 1 | 1]);
//	for (auto [x, y] : st[1]) cout << x << " -> " << y << "\n"; 
	for (int j = 1; j <= q; j++) {
		int l, r; cin >> l >> r;
		for (int i = 1; i <= n; i++) c[i] = i;
		for (int k = l; k <= r; k++) {
			for (int i = 1; i <= n; i++) if (c[i] == a[k]) c[i] = b[k];
		}
//		map<int, int> now = query(l, r);
//		for (int i = 1; i <= n; i++) {
//			if (now.count(i)) c[i] = now[i];
//			else c[i] = i;
//		}
		int cnt = 0, last = c[1];
		c[n + 1] = n + 1;
		for (int i = 2; i <= n + 1; i++) {
			if (c[i] != last) ++cnt, last = c[i];
		}
		cout << cnt << "\n";
	}
	return 0;
}
