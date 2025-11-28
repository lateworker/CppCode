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
intl calc(intl n, intl k, intl x) {
	return (x % k) * ((n - x) % k);
}
int Main(ffopen(); MultiCase; ) {
	intl n, k;
	cin >> n >> k;
	intl p = 0;
	for (intl i = n; i >= 0; i -= k) {
		if (calc(n, k, i >> 1) >= calc(n, k, p)) p = i >> 1;
		else break;
	}
	cout << p << '\n';
} Return; }

