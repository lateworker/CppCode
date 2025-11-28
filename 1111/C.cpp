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
const intl N = 100000, inf = 0x3f3f3f3f3f3f3f3f;
intl n, a[N + 10];
void slove() {
	cin >> n;
	intl ma = -inf, ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] += a[i - 1];
		chkmax(ans, abs(a[i] - ma) - (a[i] - ma));
		chkmax(ma, a[i - 1]);
	}
	cout << a[n] + ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
