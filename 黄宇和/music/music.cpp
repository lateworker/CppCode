#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 500000, inf = 0x3f3f3f3f;
int n, k, a[N + 10], b[N + 10], ans;
int main() { ffopen(music);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n);
	for (int i = n; i >= 1; i--) b[i] = upper_bound(a + i + 1, a + n + 1, a[i] + k) - a - i;
	for (int i = n; i >= 1; i--) a[i] = max(a[i + 1], b[i]);
	for (int i = 1; i <= n; i++) ans = max(ans, b[i] + a[i + b[i]]);
	cout << ans << "\n";
	return 0;
}
