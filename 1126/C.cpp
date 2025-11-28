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
const int N = 200000;
int n, f[N + 10], g[N + 10];
struct Seg { int l, r; } a[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;
	sort(a + 1, a + 1 + n, [&](const Seg& x, const Seg& y) { return x.r < y.r; } );
	memset(g, 0x3f, (n + 3) * sizeof(*g));
	for (int i = 1; i <= n; i++) {
		f[i] = 1;
		chkmax(f[i], int(upper_bound(g + 1, g + 1 + n, a[i].l) - g));
		chkmin(g[f[i]], a[i].l);
	}
	cout << *max_element(f + 1, f + 1 + n) << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
