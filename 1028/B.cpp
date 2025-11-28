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
const int N = 300000, inf = 0x3f3f3f3f;
int n, a[N + 10], las[N + 10], ans[N + 10];
int Main(ffopen(); MultiCase; ) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		las[a[i]] = 0;
		ans[a[i]] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (las[a[i]]) {
			chkmax(ans[a[i]], (i - las[a[i]]) >> 1);
		} else {
			chkmax(ans[a[i]], i - 1);
		}
		las[a[i]] = i;
	}
	int idx = n + 1; ans[n + 1] = inf;
	for (int i = 1; i <= n; i++) {
		chkmax(ans[a[i]], n - las[a[i]]);
		if (ans[a[i]] < ans[idx]) idx = a[i];
		if (ans[a[i]] == ans[idx]) chkmin(idx, a[i]);
	}
	cout << idx << ' ' << ans[idx] << '\n';
} Return; }

