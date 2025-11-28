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
const int N = 100000, A = 30;
int n, tn, a[N + 10], p[N + 10], las[A + 5], pe;
intl cnt[N * A + 10];
tuple<int, int, int> evt[N * A + 10];
void slove() {
	cin >> n; tn = sqrt(n);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		p[i] = p[i - 1] ^ a[i];
	}
	memset(las, 0, sizeof las), pe = 0;
	static int idx[A + 5];
	for (int i = 1; i <= n; i++) {
		int val = p[i];
		for (int j = 1; j <= A; j++) {
			if (~ a[i] >> (j - 1) & 1) las[j] = i;
		}
		iota(idx + 1, idx + A + 1, 1), las[A + 1] = i, idx[A + 1] = A + 1;
		sort(idx + 1, idx + A + 1, [&](int jx, int jy) { return las[jx] == las[jy] ? jx < jy : las[jx] < las[jy]; } );
		for (int jj = 1; jj <= A + 1; jj++) {
			int l = las[idx[jj - 1]], r = las[idx[jj]] - 1, j = idx[jj];
			if (l <= r) evt[++pe] = {val, l, r};
			if (j <= A) val ^= 1 << (j - 1);
		}
	}
	sort(evt + 1, evt + pe + 1, [&](const auto& x, const auto& y) {
		const auto& [v1, l1, r1] = x;
		const auto& [v2, l2, r2] = y;
		return l1 / tn == l2 / tn ? r1 < r2 : l1 < l2;
	} );
	intl l = 0, r = -1, ans = 0;
	map<int, int> cnt;
	for (int i = 1; i <= pe; i++) {
		auto [val, lf, rt] = evt[i];
		while (lf < l) ++cnt[p[--l]];
		while (r < rt) ++cnt[p[++r]];
		while (l < lf) --cnt[p[l++]];
		while (rt < r) --cnt[p[r--]];
		ans += cnt[val];
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
