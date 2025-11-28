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
intl n, q, a[N + 10];
intl calc() {
	intl mi = a[n], res = 0;
	for (int i = n - 1; i >= 1; i--) {
		intl now = max(0LL, mi - a[i]);
		res += now - mi, mi = now;
		chkmin(mi, a[i]);
		if (mi == 0) break;
	}
	return res;
}
void slove() {
	cin >> n >> q;
	intl sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	cout << sum + calc() << '\n';
	for (int i = 1; i <= q; i++) {
		intl x, y; cin >> x >> y;
		sum += y - a[x], a[x] = y;
		cout << sum + calc() << '\n';
	}
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
