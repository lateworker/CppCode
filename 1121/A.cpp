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
const int N = 300000;
int n, a[N + 10], p[3], las[3];
bitset<3> msk[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], --a[i];
	p[0] = p[1] = p[2] = n + 1;
	for (int i = 1; i <= n; i++) chkmin(p[a[i]], i);
	msk[n + 1].reset();
	for (int i = n; i >= 1; i--) {
		msk[i] = msk[i + 1], msk[i].set(a[i]);
	}
	las[0] = las[1] = las[2] = 0;
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		las[a[i]] = i;
		int idx[7] = {0, las[0], las[1], las[2], p[0], p[1], p[2]};
		sort(idx, idx + 7);
		for (int j = 1; j <= 6; j++) {
			if (idx[j] > i) break;
			int l = idx[j - 1] + 1, r = idx[j], cnt = 0;
			if (r < l) continue;
			cnt += p[0] < l || msk[i + 1][0] || las[2] >= r;
			cnt += p[1] < l || msk[i + 1][1] || las[0] >= r;
			cnt += p[2] < l || msk[i + 1][2] || las[1] >= r;
			if (cnt == 3) ans += (intl) r - l + 1;
		}
	}
	cout << ans << '\n';
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
