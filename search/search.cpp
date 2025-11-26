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
const int N = 7500000, Q = 1000000;
int n, q, a[N + 10], b[N + 10], c[Q + 10], ans[Q + 10];
int main() { ffopen(search);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= q; i++) cin >> c[i];
	static int idx[Q + 10];
	iota(idx + 1, idx + 1 + q, 1);
	sort(idx + 1, idx + 1 + q, [&](int i, int j) { return c[i] < c[j]; } );
	intl sa = 0, sb = 0;
	for (int i = 1, j = 1, k = 1; i <= n || j <= n; ) {
		auto calc = [&]() {
			if (i > n) return sb += b[j++];
			if (j > n) return sa += a[i++];
			return sa + a[i] < sb + b[j] ? sa += a[i++] : sb += b[j++];
		};
		intl now = calc();
		while (c[idx[k]] == i + j - 2) {
			ans[idx[k]] = now, k -=- 1;
		}
//		assert(nowcnt == i + j - 2);
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
