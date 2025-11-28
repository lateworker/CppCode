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
const int N = 200000;
int n, m, k, a[N + 10], b[N + 10];
int main() { ffopen();
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	for (int i = 1, j = 1; i <= n; i++) {
		while (j <= m && b[j] < a[i]) ++j;
		if (j > m) break;
		if (a[i] <= b[j]) --k, ++j;
	}
	cout << (k > 0 ? "No" : "Yes") << '\n';
	return 0;
}
