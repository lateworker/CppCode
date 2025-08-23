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
const intl N = 500000, inf = 0x3f3f3f3f3f3f3f3f;
intl n, a[N + 10], vec[N + 10], m;
intl idx(intl x) { return lower_bound(vec + 1, vec + 1 + m, x) - vec; }
intl st[2][N * 2 + 10], ma[N + 10];
void modify(int i, int u, intl val) { for (u += m - 1; u; u >>= 1) chkmax(st[i][u], val); }
intl query(int i, int l, int r) {
	intl res = -inf; if (r < l) return res;
	for (l += m - 1, r += m; l < r; l >>= 1, r >>= 1) {
		if (l & 1) chkmax(res, st[i][l++]);
		if (r & 1) chkmax(res, st[i][--r]);
	} return res;
}
void slove() {
	cin >> n; m = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1], vec[++m] = a[i];
	sort(vec + 1, vec + m + 1);
	m = unique(vec + 1, vec + m + 1) - vec - 1;
	for (int i = 1; i <= (m << 1); i++) st[0][i] = st[1][i] = -inf;
	for (int i = 1; i <= m; i++) ma[i] = -inf;
	intl f = -inf;
	for (int i = 1; i <= n; i++) {
		f = a[i] == 0 ? 0 : a[i] < 0 ? -i : i;
		f = max({f, query(0, 1, idx(a[i]) - 1) + i, query(1, idx(a[i]) + 1, m) - i, ma[idx(a[i])]});
		modify(0, idx(a[i]), f - i), modify(1, idx(a[i]), f + i), chkmax(ma[idx(a[i])], f);
	}
	cout << f << "\n";
}
int main() {
	int T; cin >> T;
	while (T--) slove();
	return 0;
}
