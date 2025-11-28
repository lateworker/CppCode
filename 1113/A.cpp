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
intl calc(intl n) { return ((n + 1) * n) >> 1; }
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	intl sum = calc(n), ma = 0;
	a[n + 1] = 0;
	for (int i = 1, j = 1; i <= n + 1; i++) {
		if (~ a[i] & 1) {
			int len = i - j;
			sum -= calc(len);
			int p = (len + 1) >> 1;
			for (int i = 1; i <= p; i++) {
				chkmin(ma, calc(i - 1) + calc(len - i) - calc(len));
			}
			j = i + 1;
		}
	}
	cout << sum - ma << '\n';
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
