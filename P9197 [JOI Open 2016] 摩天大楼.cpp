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
const intl N = 100, M = 1000, Mod = 1000000007;
int n, m, a[N + 10];
intl f[N + 10][M + 10][2][2], ff[N + 10][M + 10][2][2];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n, greater<int>());
	for (int cf : {0, 1})  {
		for (int cb : {0, 1}) f[1][0][cf][cb] = 1;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++) for (int k = 0; k <= m; k++) {
			for (int cf : {0, 1}) for (int cb : {0, 1}) {
				ff[j][k][cf][cb] = f[j][k][cf][cb];
				f[j][k][cf][cb] = 0;
			}
		}
		for (int j = 1; j < i; j++) for (int k = 0; k <= m; k++) {
			for (int cf : {0, 1}) for (int cb : {0, 1}) {
				int nk = k + ((j << 1) - cf - cb) * (a[i - 1] - a[i]);
				if (nk > m) continue;
				if (j > 1) {
					(f[j + 1][nk][cf][cb] 	+= ff[j][k][cf][cb] * (j - 1) 		% Mod) %= Mod;
					(f[j][nk][cf][cb] 	+= ff[j][k][cf][cb] * ((j - 1) << 1) 	% Mod) %= Mod;
					(f[j - 1][nk][cf][cb] 	+= ff[j][k][cf][cb] * (j - 1) 		% Mod) %= Mod;
				}
				if (!cf) {
					(f[j + 1][nk][0][cb] 	+= ff[j][k][0][cb]) %= Mod;
					(f[j + 1][nk][1][cb] 	+= ff[j][k][0][cb]) %= Mod;
					(f[j][nk][0][cb] 		+= ff[j][k][0][cb]) %= Mod;
					(f[j][nk][1][cb] 		+= ff[j][k][0][cb]) %= Mod;
				}
				if (!cb) {
					(f[j + 1][nk][cf][0] 	+= ff[j][k][cf][0]) %= Mod;
					(f[j + 1][nk][cf][1] 	+= ff[j][k][cf][0]) %= Mod;
					(f[j][nk][cf][0] 		+= ff[j][k][cf][0]) %= Mod;
					(f[j][nk][cf][1] 		+= ff[j][k][cf][0]) %= Mod;
				}
			}
		}
	}
	intl ans = 0;
	for (int k = 0; k <= m; k++) ans += f[1][k][1][1], ans %= Mod;
	cout << ans % Mod << '\n';
	return 0;
}
