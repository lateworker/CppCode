#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const intl Mod = 1000000007;
int n, m, s;
vector<pair<int, int> > f, g;
int main() { ffopen();
	cin >> m >> n;
	for (int l = 1, r; l <= m; l = r + 1) {
		r = m / (m / l);
		f.emplace_back(1, r - l + 1);
	} s = f.size();
	for (int i = 1; i < n; i++) {
		g = f; intl sum = 0;
		for (int l = 1, r, j = 0; l <= m; l = r + 1, j++) {
			r = m / (m / l);
			sum += (intl) g[j].first * g[j].second % Mod, sum %= Mod;
			f[s - j - 1].first = sum;
		}
	}
	intl ans = 0;
	for (int i = 0; i < s; i++) ans += (intl) f[i].first * f[i].second % Mod, ans %= Mod;
	cout << ans << "\n";
	return 0;
}
