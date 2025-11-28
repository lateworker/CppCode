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
const intl N = 2000;
int n, m, a[N + 10], ans[N + 10];
bitset<N + 10> vis;
void proc(int l, int r) {
	vis.reset();
	for (int i = l; i <= r; i++) {
		if (vis[a[i]]) continue;
		ans[i] = a[i], vis[a[i]] = true;
	}
	for (int i = l, j = 1; i <= r; i++) {
		if (ans[i]) continue;
		while (j <= m && vis[j]) ++j;
		ans[i] = j, ++j;
	}
}
int Main(ffopen(); MultiCase; ) {
	memset(ans, 0, (n + 3) * sizeof(int));
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i += m) proc(i, min(n, i + m - 1));
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
} Return; }

