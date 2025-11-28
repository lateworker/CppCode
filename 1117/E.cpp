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
intl n, a, b;
intl calc(intl m) {
	intl k = m / a;
	return k * (k + 1) / 2 + min(m - k * a, k);
}
void slove() {
	cin >> n >> a >> b;
	if (a == b) { cout << n / a << '\n'; return; }
	if (a > b) swap(a, b);
	cout << calc(min(n, a * (a - 1))) + max(0LL, n - a * (a - 1)) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
