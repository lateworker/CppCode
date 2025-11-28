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
int a, b, n, m;
void slove() {
	cin >> a >> b;
	n = a + b, m = (n + 1) * n, n >>= 1;
	
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
//	intl xx; cin >> xx;
//	int n = 20;
//	for (int x = 1; x <= xx; x++) {
//		for (int i = 1; i <= n; i++) {
//			cout << x + x * (x - 1) / 2 + (x + x + i - 2) * (i - 1) / 2 << " \n"[i == n];
//		}
//	}
	return 0;
}
