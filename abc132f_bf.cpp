#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int A = 10000;
int n, m, f[A + 10], g[A + 10];
int main() {
	cin >> m >> n;
	for (int i = 1; i <= m; i++) f[i] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) cout << f[j] << " \n"[j == m];
		for (int j = 1; j <= m; j++) g[j] = f[j], f[j] = 0;
		for (int l = 1, r; l <= m; l = r + 1) {
			r = m / (m / l);
			for (int k = 1; k <= m / l; k++) {
				for (int x = l; x <= r; x++) f[x] += g[k];
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) ans += f[i];
	cout << ans << "\n";
	return 0;
}
