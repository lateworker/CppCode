#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#include <iostream>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const intl N = 200, Mod = 998244353;
int n, m, b;
bitset<N + 10> dgt;
void rds() {
	string s; cin >> s;
	n = s.size();
	for (int i = 0; i < n; i++) {
		dgt[i + 1] = s[i] == '1';
	}
}
int g[N + 10][2][N + 10];
int dfs(int i, int t, int cnt) {
	if (cnt < 0) return 0;
	if (!i) return !cnt;
	if (~g[i][t][cnt]) return g[i][t][cnt];
	int k = t ? dgt[i] : 1;
	intl res = dfs(i - 1, t && !k, cnt); // j = 0
	if (k) res += dfs(i - 1, t, cnt - 1); // j = 1
	return g[i][t][cnt] = res % Mod;
}
int main() {
	rds(); cin >> m >> b;
	memset(g, -1, sizeof g);
	
	return 0;
}

//	for (int j = 0; j <= k; j++) {
//		res += dfs(i - 1, t && j == k, cnt - j);
//		res %= Mod;
//	}
