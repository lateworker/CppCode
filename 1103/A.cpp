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
const int N = 500000;
int n, m, a[N + 10];
void slove() {
	cin >> n >> m;
	int ma = 0, mi = numeric_limits<int>::max();
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		chkmax(ma, a[i]);
		chkmin(mi, a[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += ma - a[i];
	}
	cout << max((ans + m - 1) / m, ma - mi) << '\n';
}
signed main() {
	ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	} 
	return 0;
}

