#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using ldouble = long double;
intl calc(intl l, intl r) { return (l + r) * (r - l + 1) / 2; }
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		intl n, m1, m0;
		cin >> n >> m1;
		m0 = n * (n - 1) / 2 - m1;
		cout << calc(n - 1 - min(n - 1, m0), ({ ldouble p = (n << 1) - 1; intl(p - sqrtl(p * p - 8.0 * m1)) / 2; }) ) << '\n';
	}
	return 0;
}
