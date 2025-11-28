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
const intl N = 200000, A = 60;
intl n, a[N + 10];
void slove() {
	cin >> n;
	intl x = 0, ans = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], x ^= a[i];
	for (int i = 1; i <= n; i++) {
		intl y = x ^ a[i];
		for (int j = A - 1; ~j; j--) {
			if ((~ y >> j & 1) && ((1LL << j) <= a[i])) y ^= 1LL << j, a[i] -= 1LL << j;
		}
		if (a[i]) y ^= a[i] & 1;
		chkmax(ans, y);
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
