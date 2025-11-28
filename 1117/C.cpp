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
const int N = 400000;
int n, m, q, a[N + 10], cnt[N + 10];
int main() { ffopen();
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i], chkmax(m, a[i]), ++cnt[a[i]];
	intl ans = 0;
	for (int i = 1; i <= m; i++) ans += (intl) cnt[i] * (cnt[i] + 1) / 2;
	for (int i = 1; i <= q; i++) {
		int x, y; cin >> x >> y;
		ans -= (intl) cnt[a[x]] * (cnt[a[x]] + 1) / 2, --cnt[a[x]], ans += (intl) cnt[a[x]] * (cnt[a[x]] + 1) / 2;
		a[x] = y;
		ans -= (intl) cnt[a[x]] * (cnt[a[x]] + 1) / 2, ++cnt[a[x]], ans += (intl) cnt[a[x]] * (cnt[a[x]] + 1) / 2;
		cout << ans << '\n';
	}
	return 0;
}
