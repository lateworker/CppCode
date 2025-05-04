#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl Mod = 998244353, N = 100000;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl inv(intl a) { return fpow(a, Mod - 2); }
int n, K;
intl fac[N + 10], ans[N + 10];
intl C(int n, int m) {
	return fac[n] * inv(fac[m] * fac[n - m] % Mod) % Mod;
}
intl calc(intl k) {
	intl m = n - k * 4;
	if (m < 0) return 0;
	return fac[m + k] * inv(fac[k]) % Mod * inv(fac[m]) % Mod * fpow(10, m) % Mod;
}
int main() {
	fac[0] = 1; for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	cin >> n >> K;
	int p = n / 4;
	for (int k = p; k >= K; k--) {
		ans[k] = calc(k);
		for (int j = k + 1; j <= p; j++) {
			ans[k] -= ans[j] * C(j, (n - k * 4) / 4) % Mod, ans[k] = (ans[k] % Mod + Mod) % Mod;
		}
	}
	cout << ans[K] << "\n";
	return 0;
}
