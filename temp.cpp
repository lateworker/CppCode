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
const int N = 1000000;
int n, m, f[N + 10];
string s, t;
int main() { ffopen();
	cin >> s >> t;
	n = s.size(); s = '#' + s;
	m = t.size(); t = '#' + t;
	for (int i = 2; i <= m; i++) {
		int j = f[i - 1];
		while (j && t[j + 1] != t[i]) j = f[j];
		f[i] = j + (t[j + 1] == t[i]);
	}
	for (int i = 1, j = 0; i <= n; i++) {
		while (j && t[j + 1] != s[i]) j = f[j];
		if (t[j + 1] == s[i]) ++j;
		if (j == m) {
			cout << i - j + 1 << '\n';
			j = f[j];
		}
	}
	for (int i = 1; i <= m; i++) cout << f[i] << " \n"[i == m];
	return 0;
}
