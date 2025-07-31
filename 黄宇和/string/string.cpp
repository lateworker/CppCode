#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int long long
using namespace std;
using intl = long long;
const intl N = 300000, Mod = 998244353;
inline intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
int n;
string s;
string query(int l, int r) { return s.substr(l, r - l + 1); }
intl ans, fac[N + 10], ifac[N + 10];
map<string, int> t;
signed main() { ffopen(string);
	cin >> s;
	n = s.size(); s = '#' + s;
	
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[n] = fpow(fac[n], Mod - 2);
	for (int i = n; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	
	for (int x = 1; x <= n; x++) {
		int m = n / x, y = n - m * x;
		t.clear();
		if (y) ++t[query(1, y)];
		for (int i = 0; i < m; i++) {
			++t[query(i * x + 1 + y, (i + 1) * x + y)];
		}
		intl res = fac[m];
		for (auto u = t.begin(); u != t.end(); u++) {
			res *= ifac[u->second], res %= Mod;
		}
		ans += res, ans %= Mod;
		if (!y) continue;
		for (int i = 1; i <= m; i++) {
			string now;
			
			now = query((i - 1) * x + 1, (i - 1) * x + y);
			res *= fac[t[now]], res %= Mod;
			--t[now];
			res *= ifac[t[now]], res %= Mod;
			
			now = query((i - 1) * x + y + 1, i * x + y);
			res *= fac[t[now]], res %= Mod;
			--t[now];
			res *= ifac[t[now]], res %= Mod;
			
			now = query((i - 1) * x + 1, i * x);
			res *= fac[t[now]], res %= Mod;
			++t[now];
			res *= ifac[t[now]], res %= Mod;
			
			now = query(i * x + 1, i * x + y);
			res *= fac[t[now]], res %= Mod;
			++t[now];
			res *= ifac[t[now]], res %= Mod;
			
			ans += res, ans %= Mod;
		}
	}
	
	cout << ans << "\n";
	return 0;
}
