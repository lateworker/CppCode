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
const int N = 300000;
int n, a[N + 10], g[N + 10], cnt[N * 2 + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	a[n + 1] = 0;
	for (int i = n; i >= 1; i--) {
		g[i] = a[i] == a[i + 1] ? g[i + 1] : i;
	}
	int f = 0; intl ans = 0;
	for (int i = 1; i <= n; i = g[i] + 1) {
		if (a[i] != a[i - 1]) f = i;
		ans += (intl) (a[i] != 2) * (g[i] - f + 1) * (g[i] - f + 2) / 2;
	}
	for (int i = 1; i <= n; i++) {
		g[i] = g[i - 1] + a[i] - 2;
	}
	memset(cnt, 0, (n * 2 + 7) * sizeof(*cnt));
	for (int i = 1, k = 1; i <= n; i++) {
		while (a[i] == 2 && k <= i) ++cnt[g[(k++) - 1] + n + 1];
		ans += cnt[g[i] + n + 1];
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
