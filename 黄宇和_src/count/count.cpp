#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
using intll = __int128;
intll fpow(intll a, int b) { intll c = 1; for (; b; a *= a, b >>= 1) if (b & 1) c *= a; return c; }
intll gcdll(intll x, intll y) {
	while (y) {
		intll t = x % y;
		x = y, y = t;
	} return x;
}
intl n, m;
int main() { ffopen(count);
	cin >> n >> m;
	vector<intll> vec;
	for (intl i = 1; i * i <= n; i++) {
		if (n % i) continue;
		vec.push_back(i);
		if (i * i < n) vec.push_back(n / i);
		else break;
	}
	if ((int) vec.size() == 2) return cout << 1 << "\n", 0;
	int ans = 0;
	for (intll d : vec) {
		intll xy = fpow(d, m);
		intll x = n / (intl) d;
		if (xy % x) continue;
		intll y = xy / x;
		if (y % d) continue;
		if (gcdll(x, y / d) == 1) ++ans;
	}
	cout << ans << "\n";
	return 0;
}
