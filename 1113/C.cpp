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
const int N = 100000;
int n, q, a[N + 10], cnt[N + 10][2];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[i][0] = cnt[i - 1][0];
		cnt[i][1] = cnt[i - 1][1];
		if (a[i] == 1) ++cnt[i][0];
		if (a[i] == 2) ++cnt[i][1];
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		int x = cnt[r][0] - cnt[l - 1][0];
		int y = cnt[r][1] - cnt[l - 1][1];
		int z = r - l + 1 - x - y;
		if (x > y) swap(x, y);
		int d = min({k, z, y - x});
		x += d, z -= d, k -= d;
		if (k && z) {
			d = min(k >> 1, z >> 1);
			x += d, y += d, z -= d << 1, k -= d << 1;
			if (k && z) ++x;
		} else if (k) {
			d = min(k, (y - x) >> 1);
			x += d, y -= d, k -= d;
		}
		cout << (intl) x * y << '\n';
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
