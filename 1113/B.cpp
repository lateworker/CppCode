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
const int N = 300000, inf = 0x3f3f3f3f;
int n, f[N + 10], prf[N + 10], suf[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		prf[i] = prf[i - 1] + (c == 'a');
		suf[i] = (c == 'c');
		f[i] = c == 'b' ? i : f[i - 1];
	}
	suf[n + 1] = 0;
	for (int i = n; i >= 1; i--) suf[i] += suf[i + 1];
	int ans = inf;
	for (int i = 1; i <= n; i++) {
		chkmin(ans, suf[i + 1] + prf[f[i]]);
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
//		memset(f, 0, sizeof f);
//		memset(suf, 0, sizeof suf);
//		memset(prf, 0, sizeof prf);
	}
	return 0;
}
