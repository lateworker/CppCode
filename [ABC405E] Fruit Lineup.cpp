#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const intl N = 4000000, Mod = 998244353;
intl fpow(intl a, intl b) { intl c = 1; for (a %= Mod; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl a, b, c, d, fac[N + 10], ifac[N + 10], ans;
int main() {
	fac[0] = 1; for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2); for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	cin >> a >> b >> c >> d;
	for (int i = a; i <= a + b; i++)
		ans += fac[i - 1] * ifac[a - 1] % Mod * ifac[i - a] % Mod * fac[a + b + c + d - i] % Mod * ifac[b - i + a + d] % Mod * ifac[c] % Mod, ans %= Mod;
	cout << ans << "\n";
	return 0;
}
