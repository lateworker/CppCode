#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl Mod = 19940417, Inv6 = 3323403;
intl n, m, ans;
intl gsum1(intl l, intl r) { return (l + r) * (r - l + 1) / 2 % Mod; }
intl gsum2(intl s) { return s * (s + 1) % Mod * (s << 1 | 1) % Mod * Inv6 % Mod; }
intl gsum3(intl l, intl r) { return (gsum2(r) - gsum2(l - 1) + (Mod << 1)) % Mod; }
int main() { ffopen();
	cin >> n >> m;
	if (n > m) swap(n, m);
	auto calc1 = [&](intl s, intl t) {
		intl res = 0;
		for (intl i = 1, j; i <= s; i = j + 1) {
			j = min(s, t / (t / i));
			res += (t / i) * gsum1(i, j) % Mod, res %= Mod;
		} return res;
	};
	ans = ((n * n - calc1(n, n)) % Mod) * ((m * m - calc1(m, m)) % Mod) % Mod;
	ans -= n * n % Mod * m % Mod, ans = (ans + (Mod << 1)) % Mod;
	ans += m * calc1(n, n) % Mod, ans %= Mod;
	ans += n * calc1(n, m) % Mod, ans %= Mod;
	for (intl i = 1, j; i <= n; i = j + 1) {
		intl x = n / i, y = m / i;
		j = min(n / x, m / y);
		ans -= x * y % Mod * gsum3(i, j) % Mod, ans = (ans + (Mod << 1)) % Mod;
	}
	cout << ans << "\n";
	return 0;
}
