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
const intl N = 1000000, Mod = 1000000007;
int n, m, f[N + 10];
char s[N + 10], t[N * 2 + 10];
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> s[i];
	f[1] = 0;
	for (int i = 2; i <= n; i++) {
		int j = f[i - 1];
		while (j && s[j + 1] != s[i]) j = f[j];
		if (s[j + 1] == s[i]) ++j;
		f[i] = j;
	}
	for (int i = 1; i <= n; i++) t[i] = s[i], t[(n << 1) - i + 1] = s[i];
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	for (int i = 2, j = 0; i < (n << 1); i++) {
		while (j && s[j + 1] != t[i]) j = f[j];
		if (s[j + 1] == t[i]) ++j;
		if (j == n) ++cnt1, j = f[j];
	}
	for (int i = 1; i <= n; i++) t[i] = t[i + n], t[i + n] = s[i];
	for (int i = 1, j = 0; i < (n << 1); i++) {
		while (j && s[j + 1] != t[i]) j = f[j];
		if (s[j + 1] == t[i]) ++j;
		if (j == n) i == n ? ++cnt3 : ++cnt2, j = f[j];
	}
//	cerr << cnt1 << ' ' << cnt2 << ' ' << cnt3 << '\n';
	intl pw = fpow(2, m - 1);
	cout << (pw * cnt1 % Mod + (pw - 1) * cnt2 % Mod + pw * (cnt3 + 1) % Mod) % Mod << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
