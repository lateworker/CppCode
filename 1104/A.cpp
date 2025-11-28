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
const intl Mod = 998244353;
intl n, m;
void slove() {
	cin >> n >> m;
	if (n < m) swap(n, m); 
	intl x = (n + 1) >> 1, ans;
	if (n == m) {
		ans = x * x % Mod;
		if (~ n & 1) {
			ans += (((x * (x + 1)) << 1) % Mod + (x + 1) * (x + 1) % Mod) % Mod, ans %= Mod;
		}
	} else {
		intl lx = max(m - n + x, 1LL), rx = min(1 + n - x, m);
		ans = (((rx + lx) * (rx - lx + 1)) >> 1) % Mod * x % Mod;
		if (~ n & 1) {
			ans += (((rx + lx) * (rx - lx + 1)) >> 1) % Mod * (x + 1) % Mod, ans %= Mod;
		}
	}
	cout << ans << '\n';
}
int main() {
	ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
