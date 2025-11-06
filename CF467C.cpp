#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
using intl = long long;
const int N = 5000;
intl n, m, k, a[N + 10], f[N + 10][N + 10];
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	for (int j = 1; j <= k; j++) {
		for (int i = m; i <= n; i++) {
			f[j][i] = max(f[j][i - 1], f[j - 1][i - m] + a[i] - a[i - m]);
		}
	}
	cout << f[k][n] << "\n";
	return 0;
}
// wqs二分
