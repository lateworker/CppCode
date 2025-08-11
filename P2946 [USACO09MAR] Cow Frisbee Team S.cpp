#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
using intl = long long;
const intl N = 2000, Mod = 100000000;
int n, m;
int main() { ffopen();
	cin >> n >> m;
	vector<int> f(m);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		vector<int> g = f;
		x %= m, ++f[x];
		for (int j = 0; j < m; j++)
			f[j] = ((intl) f[j] + g[(j - x + m) % m]) % Mod;
	}
	cout << f[0] << "\n";
	return 0;
}
