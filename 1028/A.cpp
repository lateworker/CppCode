#define MultiCase (cin >> CaseId)
#define Main(Callback) main() { int CaseId = 1; { Callback } CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else return 0
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
const int N = 300000;
int n, a[N + 10], b[N + 10], na, nb, c[N + 10], nc;
int Main(ffopen(); MultiCase; ) {
	cin >> n; na = nb = nc = 0;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		(x & 1 ? a[++na] : b[++nb]) = x;
	}
	if (na & 1) { cout << "-1\n"; Return; }
	sort(a + 1, a + 1 + na);
	sort(b + 1, b + 1 + nb);
	for (int i = 1, j = na; i < j; i++, j--) {
		++nc;
		c[nc] = (a[j] + a[i]) >> 1;
		c[nc + (n >> 1)] = (a[j] - a[i]) >> 1;
	}
	for (int i = 1, j = nb; i < j; i++, j--) {
		++nc;
		c[nc] = (b[j] + b[i]) >> 1;
		c[nc + (n >> 1)] = (b[j] - b[i]) >> 1;
	}
	for (int i = 1; i <= n; i++) cout << c[i] << " \n"[i == n];
} Return; }

