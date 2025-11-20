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
const intl PN = 95, N = 500, ALL = (1 << 8) - 1;
int n, prm[PN + 10], pn, isnp[N + 10];
vector<int> gtprm(int x) {
	vector<int> res;
	while (x > 1) {
		if (res.empty() || res.back() != isnp[x]) res.push_back(isnp[x]);
		x /= prm[isnp[x]];
	} return res;
}
void initprm() {
	isnp[0] = isnp[1] = 0;
	for (int i = 2; i <= N; i++) {
		if (!isnp[i]) prm[++pn] = i;
		for (int j = 1; j <= pn && (intl) i * prm[j] <= N; j++) {
			isnp[i * prm[j]] = j;
			if (i % prm[j] == 0) break;
		}
	}
	for (int i = 1; i <= pn; i++) isnp[prm[i]] = i;
}
vector<int> g[PN + 10];
intl f[ALL + 3][ALL + 3], ff[ALL + 3][ALL + 3], pw2[N + 10], Mod;
intl calc(const vector<int>& vec) {
	memset(f, 0, sizeof f), f[0][0] = 1;
	for (int msk : vec) {
		for (int S = 0; S <= ALL; S++) {
			for (int T = 0; T <= ALL; T++) {
				ff[S][T] = f[S][T];
			}
		}
		for (int S = 0; S <= ALL; S++) {
			for (int T = 0; T <= ALL; T++) {
				if (S & T) continue;
				if ((msk & T) == 0) (f[S | msk][T] += ff[S][T]) %= Mod;
				if ((msk & S) == 0) (f[S][T | msk] += ff[S][T]) %= Mod;
			}
		}	
	}
	intl res = 0;
	for (int S = 0; S <= ALL; S++) {
		for (int T = 0; T <= ALL; T++) {
			if (S & T) continue;
			res += f[S][T], res %= Mod;
		}
	}
	return res;
}
int main() {
	initprm();
	cin >> n >> Mod;
	pw2[0] = 1;
	for (int i = 1; i <= n; i++) pw2[i] = (pw2[i - 1] << 1) % Mod;
	vector<int> ful;
	for (int i = 2; i <= n; i++) {
		vector<int> vec = gtprm(i);
		int msk = 0;
		for (int j : vec) {
			if (j <= 8) msk |= 1 << (j - 1);
		}
		if (msk) {
			if (vec.back() > 8) g[vec.back()].push_back(msk);
			ful.push_back(msk);
		}
	}
	intl ans = calc(ful);
	for (int i = 9; i <= pn; i++) {
		if (prm[i] > n) break;
		cerr << g[i].size() << '\n';
		ans += pw2[n - (g[i].size()) - 1] << 1, ans %= Mod;
//		if (g[i].empty()) continue;
		cerr << prm[i] << '\n';
		for (int msk : g[i]) cerr << msk << ' '; cerr << '\n';
		ans = (ans - calc(g[i]) + Mod) % Mod;
	}
	cout << ans << '\n';
	return 0;
}
