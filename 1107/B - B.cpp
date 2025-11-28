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
const intl Mod = 998244353;
int n, x;
vector<int> vec;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
void slove() {
	cin >> n >> x;
	for (int i = 2, x0 = x; (intl) i * i <= x0; i++) {
		if (x % i) continue;
		int cnt = 0;
		while (x % i == 0) ++cnt, x /= i;
		vec.emplace_back(cnt);
	}
	if (x > 1) vec.push_back(1);
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		intl now = 1;
		for (int cnt : vec) now = now * (fpow(cnt + 1, i) - fpow(cnt, i) + Mod) % Mod;
		ans += now, ans %= Mod;
	}
	cout << ans << '\n';
	vec.clear();
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
