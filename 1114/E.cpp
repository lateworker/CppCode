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
int n, a[N + 10], ans[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n, [&](int x, int y) { return x > y; } );
	ans[1] = a[1];
	for (int i = 2; i <= n; i++) {
		if ((ans[i - 1] & a[i]) == ans[i - 1]) {
			ans[i] = ans[i - 1]; continue;
		}
		sort(a + i, a + 1 + n, [&](int x, int y) { return (x & ans[i - 1]) > (y & ans[i - 1]); } );
		ans[i] = ans[i - 1] & a[i];
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
