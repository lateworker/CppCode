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
const intl N = 200000, Mod = 1000000007;
intl n, f[3];
string s;
void slove() {
	cin >> s;
	n = s.size(); s = '#' + s;
	f[0] = f[1] = f[2] = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'a') f[0] += f[0] + 1, f[2] += f[1];
		else f[1] += f[0], f[1] += f[2];
		f[0] %= Mod, f[1] %= Mod, f[2] %= Mod;
	}
	cout << (f[0] + f[1]) % Mod << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
