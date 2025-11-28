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
int n, a[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int k = i; k >= 1 && i - k + 1 <= 100; k--) {
			intl x = abs(a[i] - a[k]);
			if (x == i - k) ans += intl(i - k + 1) << (i != k);
			if ((x + i + k) % 2 == 0 && ((x + i + k) >> 1) > i && ((x + i + k) >> 1) <= n) ans += 1LL << (i != k);
			if ((i + k - x) % 2 == 0 && ((i + k - x) >> 1) < k && ((i + k - x) >> 1) >= 1) ans += 1LL << (i != k);
		}
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
