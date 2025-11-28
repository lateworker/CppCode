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
const intl Mod = 1000000007;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl n;
void slove() {
	cin >> n;
	intl ans = 0;
	for (intl i = 2; i <= n; i++) {
		ans += (i - 1) * (i - 1) % Mod * (n - i + 1) % Mod * fpow(2, n - i + 1) % Mod, ans %= Mod;
	}
	cout << ans << '\n';
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
