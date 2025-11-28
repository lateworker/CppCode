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
const int N = 30000, LGN = __lg(N);
int n, a[N + 10], maxd;
vector<int> ans[LGN + 4];
void cdq(int l, int r, int d) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	vector<int> pos[2];
	for (int i = l; i <= mid; i++) {
		if (a[i] > mid) pos[0].push_back(i);
	}
	for (int i = mid + 1; i <= r; i++) {
		if (a[i] <= mid) pos[1].push_back(i);
	}
	assert(pos[0].size() == pos[1].size());
	int m = pos[0].size();
	for (int i = 0; i < m; i++) {
		ans[d].push_back(pos[0][i]);
		ans[d].push_back(pos[1][i]);
		swap(a[pos[0][i]], a[pos[1][i]]);
		chkmax(maxd, d);
	}
	cdq(l, mid, d + 1), cdq(mid + 1, r, d + 1);
}
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	maxd = 0, cdq(1, n, 1);
	int cnt = 0;
	for (int i = 1; i <= maxd; i++) if (ans[i].size()) ++cnt;
	cout << cnt << '\n';
	for (int i = 1; i <= maxd; i++) {
		if (ans[i].empty()) continue;
		cout << ans[i].size() << ' ';
		for (int x : ans[i]) cout << x << ' ';
		cout << '\n';
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= maxd; i++) ans[i].clear();
	}
	return 0;
}
