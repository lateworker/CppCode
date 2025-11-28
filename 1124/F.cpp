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
const int N = 200000;
intl n, q, a[N + 10], f[N + 10], g[N + 10];
intl query(int l, int r, intl k) {
	intl x = f[r] - f[l], y = g[r] - g[l];
	if (x < y) swap(x, y);
	if (x + y <= k) return 0;
	if (x - y <= k) return (x + y - k + 1) >> 1;
	return x - k;
}
void slove() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = n; i > 1; i--) a[i] -= a[i - 1];
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1], g[i] = g[i - 1];
		if (a[i] > 0) f[i] += a[i];
		if (a[i] < 0) g[i] -= a[i];
	}
	for (int i = 1; i <= q; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << query(l, r, k) << '\n';
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
