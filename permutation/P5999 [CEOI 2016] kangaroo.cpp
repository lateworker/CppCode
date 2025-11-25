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
const intl N = 2000, Mod = 1000000007;
int n, s, t;
intl f[N + 10][N + 10];
int main() {
	cin >> n >> s >> t;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (i == s || i == t) {
				f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
			} else {
				f[i][j] += f[i - 1][j - 1] * (j - (i > s) - (i > t)) % Mod;
				f[i][j] += f[i - 1][j + 1] * j % Mod;
			}
			f[i][j] %= Mod;
		}
	}
	cout << f[n][1] << '\n';
	return 0;
}
