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
const int N = 500000, inf = 0x3f3f3f3f;
int n, a[N + 10], f[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	a[n + 1] = inf;
	for (int i = 2; i < n; i++) {
		if (a[i - 1] > a[i] && a[i] > a[i + 1]) { cout << "0\n"; return; }
	}
	f[n] = n;
	for (int i = n - 1; i >= 1; i--) {
		f[i] = a[i] < a[i + 1] ? max(f[i + 1], a[i + 1] - a[i]) : 0;
	}
	int l = 1, r = n;
	for (int i = 2; i <= n; i++) {
		if (a[i - 1] < a[i]) continue;
		chkmax(l, a[i - 1] - a[i]);
		chkmin(r, f[i]);
	}
	cout << (l <= r ? (intl) (l + r) * (r - l + 1) / 2 : 0) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
