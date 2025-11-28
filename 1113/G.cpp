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
const intl Mod = 998244353, N = 500000, LGN = __lg(N);
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl fac[N + 10], ifac[N + 10];
intl nCr(intl n, intl m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod;
}
intl nPr(intl n, intl m) {
	return nCr(n, m) * fac[m] % Mod;
}
int n, m, a[N + 10], f[N + 10][LGN + 3], g[N + 10], las[N + 10];
int gtmax(int l, int r) {
	int d = __lg(r - l + 1);
	return max(f[l][d], f[r - (1 << d) + 1][d]);
}
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		g[i] = g[i - 1];
		if (a[i]) {
			f[i][0] = las[a[i]];
			las[a[i]] = i;
		} else ++g[i], f[i][0] = 0;
	}
	for (int j = 1; j <= __lg(n); j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		if (las[i] > 0) ++cnt;
	}
	intl ans = 0;
	for (int i = max(cnt, 1); i <= n && i <= m; i++) {
		bool tag = false;
		intl pi = nCr(m - cnt, i - cnt);
		for (int j = 1; j <= n; j += i) {
			int l = j, r = j + i - 1;
			if (gtmax(l, min(n, r)) >= l) { tag = true; break; }
			if (r <= n) pi = pi * fac[g[r] - g[l - 1]] % Mod;
			else {
				r = n;
				int c0 = g[r] - g[l - 1];
				pi = pi * nPr(i - (r - l + 1) + c0, c0) % Mod;
			}
		}
		if (tag) continue;
		ans += pi, ans %= Mod;
	}
	cout << ans << '\n';
}
int main() { ffopen();
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= m; i++) las[i] = 0;
//		memset(f, 0, sizeof f);
//		memset(g, 0, sizeof g);
	}
	return 0;
}
