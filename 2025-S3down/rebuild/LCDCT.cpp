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
const int prm[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
const intl N = 200000, PN = 17, Mod = 1000000007;
intl n, m, a[N + 10], b[(1 << PN) + 10], ALL, pw2[N + 10];
int chkp() {
	for (int i = 1; i <= PN; i++) {
		if (m == prm[i]) return i;
	} return 0;
}
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int p = chkp();
	if (!p) { cout << "0\n"; return; }
	ALL = (1 << (p - 1)) - 1;
	for (int i = 1; i <= n; i++) {
		if (a[i] % prm[p]) continue;
		int msk = 0;
		for (int j = 1; j < p; j++) {
			if (a[i] % prm[j] == 0) msk |= (1 << (j - 1));
		} ++b[msk];
	}
	for (int k = 1; k <= ALL; k <<= 1) {
		for (int i = 0; i <= ALL; i += k << 1) {
			for (int j = 0; j < k; j++) {
				(b[i + j] += b[i + j + k]) %= Mod;
			}
		}
	}
	intl ans = 0;
	for (int S = 0; S <= ALL; S++) {
		ans += (pw2[b[S]] + Mod - 1) % Mod * (__builtin_popcount(S) & 1 ? -1 : 1) % Mod;
		ans = (ans % Mod + Mod) % Mod;
	}
	cout << ans << '\n';
}
int main() { ffopen();
	pw2[0] = 1;
	for (int i = 1; i <= N; i++) pw2[i] = (pw2[i - 1] << 1) % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 0; i <= ALL; i++) b[i] = 0;
	}
	return 0;
}
