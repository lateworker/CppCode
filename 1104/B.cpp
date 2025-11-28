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
const intl L = 1000000, N = L, Mod = 1000000007;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
intl fac[N + 10], ifac[N + 10];
int n, m;
bitset<L + 10> a_a;
#define a(i, j) (a_a[((i) - 1) * m + (j)])
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c; cin >> c;
			a(i, j) = c == '1';
		}
	}
	if (n == 1) { cout << "1\n"; return; }
	vector<int> vec;
	for (int j = 1; j <= m; j++) if (a(n, j)) vec.push_back(j);
	for (int i = n - 1; i > 1; i--) {
		vector<int> cur;
		for (int j = 1; j <= m; j++) if (a(i, j)) cur.push_back(j);
		if ((int)cur.size() <= 1) {
			vec.clear();
		} else {
			int cnt = 0;
			for (int j : vec) {
				if (a(i, j)) ++cnt;
			}
			if (cnt == 0) {
				vec = cur;
			} else {
				static bitset<N + 10> g;
				for (int j = 1; j <= m; j++) g[j] = false;
				for (int j : cur) g[j] = true;
				for (int j : vec) g[j] = true;
				vec.clear();
				for (int j = 1; j <= m; j++) if (g[j]) vec.push_back(j);
			}
		}
	}
	intl cnt[2] = {0, 0};
	for (int j : vec) ++cnt[a(1, j)];
	cout << (fac[cnt[0] + cnt[1]] * ifac[cnt[0]] % Mod * ifac[cnt[1]] % Mod) << '\n';
}
int main() {
	ffopen();
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[N] = fpow(fac[N], Mod - 2);
	for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
