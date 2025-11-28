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
const intl N = 100000;
int n, q;
intl a[N + 10], b[N + 10];
intl calc(intl p) {
	intl i = upper_bound(a + 1, a + 1 + n, p) - a - 1;
	return b[i] + (n - i) * p;
}
intl query(intl m) {
	if (m == n) return 1;
	if (m < n) return m ? 2 : -1;
	intl l = 1, r = a[n] + 1;
	while (l < r) {
		intl mid = (l + r) >> 1;
		if (calc(mid) >= m) r = mid;
		else l = mid + 1;
	} return l == a[n] + 1 ? -1 : l;
}
void slove() {
	cin >> n >> q;
	int nn = n + 1;
	for (int i = 1; i <= n; i++) {
		intl x, y; cin >> x >> y;
		if (x == i - 1) b[i] = y;
		else chkmin(nn, i - 1);
	} n = nn;
	for (int i = 2; i <= n; i++) chkmin(b[i], b[i - 1]);
	for (int i = 1; i <= n; i++) a[n - i + 1] = b[i];
	for (int i = 1; i <= n; i++) b[i] = b[i - 1] + a[i];
	for (int i = 1; i <= q; i++) {
		intl m; cin >> m;
		cout << query(m) << '\n';
	}
}
int main() { ffopen(mexdnc);
	int T; cin >> T;
	while (T--) {
		slove();
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
	}
	return 0;
}
