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
const int N = 2000, inf = 0x3f3f3f3f;
int n, m, f[N + 10], ff[N + 10];
char s[N + 10], t[N + 10];
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> s[i];
	for (int i = 1; i <= m; i++) cin >> t[i];
	s[++n] = '#', t[++m] = '#';
	memset(f, 0x3f, sizeof f);
	ff[0] = inf, f[0] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) ff[j] = min(ff[j - 1], f[j]);
		for (int j = n; j >= i; j--) {
			if (t[i] != s[j]) { f[j] = inf; continue; }
			f[j] = f[j - 1];
			if (j > 2) chkmin(f[j], ff[j - 2] + 1);
		}
		for (int j = 1; j < i; j++) f[j] = inf;
	}
	cout << (f[n] > n ? -1 : f[n]) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
