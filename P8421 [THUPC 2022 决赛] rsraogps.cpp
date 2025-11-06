#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000, Q = 5000000;
int n, m;
unsigned a[N + 10], b[N + 10], c[N + 10];
unsigned ans[Q + 10], s[N + 10], t[N + 10], tg[N + 10], clk;
vector<pair<int, int>> qry[N + 10];
unsigned gs(int i) {
	return s[i] + tg[i] * (clk - t[i]);
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= m; i++) {
		int l, r; cin >> l >> r;
		qry[r].emplace_back(l, i);
	}
	for (int r = 1, p; r <= n; r++) {
		for (p = r - 1; p; p--) {
			auto [na, nb, nc] = make_tuple(a[p] & a[r], b[p] | b[r], gcd(c[p], c[r]));
			if (na == a[p] && nb == b[p] && nc == c[p]) break;
			tie(a[p], b[p], c[p]) = make_tuple(na, nb, nc);
		}
		s[r] = gs(r - 1);
		for (int i = p + 1; i <= r; i++) {
			s[i] = gs(i);
			tg[i] = tg[i - 1] + a[i] * b[i] * c[i];
			t[i] = clk;
		}
		++clk;
		for (auto [l, idx] : qry[r]) ans[idx] = gs(r) - gs(l - 1);
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
	return 0;
}
