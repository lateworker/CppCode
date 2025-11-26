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
const int N = 2000, M = N;
intl Mod = 1000000007, g[N * M + 10];
intl fpow(intl a, int b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
int n, m;
void slove() {
	cin >> n >> m;
	for (int j = 0; j <= n * m; j++) g[j] = 1;
	for (int i = 1; i <= n; i++) { 
		for (int j = 1; j <= n * m; j++) (g[j] += g[j - 1]) %= Mod;
//		for (int j = n * m; j > m; j--) g[j] = (g[j] - g[j - m - 1] + Mod) % Mod;
		for (int j = 0; j <= n * m; j++) cerr << g[j] << " \n"[j == n * m];
	}
	intl ans = 0;
	for (int i = 1; i <= n * m; i++) {
		ans += (g[i] - g[i - 1] + Mod) * g[i - 1] % Mod;
		ans %= Mod;
	}
	cout << ans * fpow(fpow(m + 1, n << 1), Mod - 2) % Mod << '\n';
}
int main() { ffopen();
	int T; cin >> Mod >> T;
	while (T--) {
		slove();
	}
	return 0;
}
/*
998244353
3
1 2
3 4
25 25
*/
