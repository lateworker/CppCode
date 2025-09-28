#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 100, Mod = 1000000007;
int n;
bitset<N + 10> g[N + 10];
void slove() {
	cin >> n;
	intl ans = 1, mi = 1;
	for (int i = 1; i <= n; i++) {
		intl cnt = 0;
		for (int j = 1; j <= n; j++) {
			char c; cin >> c;
			cnt += (g[i][j] = c == '1');
		}
		mi *= cnt, mi %= Mod;
	}
	ans = mi, mi = 1;
	for (int i = 1; i <= n >> 1; i++) {
		intl cnt = 0;
		for (int j = 1; j <= n; j++)
			cnt += g[i][j] && g[i + (n >> 1)][j];
		mi *= cnt, mi %= Mod;
	}
	ans -= mi, ans = (ans % Mod + Mod) % Mod;
	cout << ans << "\n";
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) { slove(); }
	return 0;
}
