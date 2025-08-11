#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 500;
int n, m, a[N + 10], w[N + 10][N + 10], f[N + 10][N + 10];
int main() { ffopen();
	cin >> n >> m;
	for (int i = 2; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int c = (i + j) >> 1;
			for (int k = i; k <= j; k++) w[i][j] += abs(a[k] - a[c]);
		}
	}
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= m; k++) {
			for (int j = 0; j < i; j++) f[i][k] = min(f[i][k], f[j][k - 1] + w[j + 1][i]);
		}
	}
	cout << f[n][m] << "\n";
	return 0;
}
