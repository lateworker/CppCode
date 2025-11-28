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
int n, a[N + 10], b[N + 10], f[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int ans = 1;
	for (int i = 1; i < n; i++) {
		b[i] = max(b[i - 1], a[i]);
		int w = ((b[i - 1] == i && a[i + 1] < i) || (b[i - 1] == i - 1 && a[i + 1] == i)) - (b[i] == i);
		ans += b[i] == i;
//		cerr << w << " \n"[i == n - 1];
		f[i] = w;
		if (i >= 3) chkmax(f[i], f[i - 2] + w);
	}
	cout << ans + max(0, *max_element(f + 1, f + n)) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
