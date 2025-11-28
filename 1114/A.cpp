#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define int long long
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const int N = 200000, inf = 0x3f3f3f3f3f3f3f3f;
int n, a[N + 10], f[N + 10], g[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		f[i] = g[i] = inf;
	}
	a[n + 1] = -inf;
	f[1] = 0;
	for (int i = 1; i <= n; ) {
		for (int j = i + 1; j <= n + 1; j++) {
			if (a[j] <= a[i]) {
				f[j] = f[i] + (j - i) * max(a[i], a[j]);
				i = j;
				break;
			}
		}
	}
	a[0] = -inf;
	g[n] = 0;
	for (int i = n; i >= 1; ) {
		for (int j = i - 1; j >= 0; j--) {
			if (a[j] <= a[i]) {
				g[j] = g[i] + (i - j) * max(a[i], a[j]);
				i = j;
				break;
			}
		}
	}
	int ans = inf;
	for (int i = 1; i <= n; i++) {
//		cerr << f[i] << ' ' << g[i] << '\n';
		chkmin(ans, f[i] + g[i]);
	}
	cout << ans << '\n';
}
signed main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
