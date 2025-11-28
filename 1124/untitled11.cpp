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
intl a, b, k;
void slove() {
	cin >> a >> b >> k;
	if (!--k) {
		cout << "0\n";
		return;
	}
	if (a == b) {
		cout << ((k + 1) >> 1) * b << '\n';
		return;
	}
//	intl l = 0, r = 1000000000;
//	while (l < r) {
//		intl mid = (l + r + 1) >> 1;
//		if (a > mid * b) l = mid;
//		else r = mid - 1;
//	}
	intl l = a / b;
	if (k <= l) {
		cout << k * b << '\n';
	} else {
		k -= l, a -= l * b;
		cout << ((k >> 1) + l) * b + (k & 1) * a << '\n';
	}
}
int main() { //ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
