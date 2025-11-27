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
int n, m, a[N + 10], b[N + 10], g[N + 10], cnt[N + 10][2], mx[N + 10], my[N + 10];
inline int idx(int i, int j) { return (i - 1) * m + j; }
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]][0] = i;
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
		cnt[b[i]][1] = i;
	}
	int ima = cnt[n * m][0], jma = cnt[n * m][1];
	if (!ima || !jma) { cout << "No\n"; return; }
	g[idx(ima, jma)] = n * m, mx[ima] = my[jma] = n * m;
	for (int i = n * m - 1; i >= 1; i--) {
		if (!cnt[i][0] && !cnt[i][1]) continue;
		if (cnt[i][0] && cnt[i][1]) {
			g[idx(cnt[i][0], cnt[i][1])] = i;
			chkmax(mx[cnt[i][0]], i);
			chkmax(my[cnt[i][1]], i);
		}
		else if (cnt[i][0]) {
			g[idx(cnt[i][0], jma)] = i;
			chkmax(mx[cnt[i][0]], i);
		}
		else if (cnt[i][1]) {
			g[idx(ima, cnt[i][1])] = i;
			chkmax(my[cnt[i][1]], i);
		}
	}
	vector<pii> pnt;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!g[idx(i, j)]) pnt.emplace_back(i, j);
		}
	}
	sort(pnt.begin(), pnt.end(), [&](const pii& x, const pii& y) {
		return min(mx[x.first], my[x.second]) > min(mx[y.first], my[y.second]);
	} );
	int k = n * m;
	for (auto [i, j] : pnt) {
		while (cnt[k][0] || cnt[k][1]) --k;
		if ((mx[i] && k > mx[i]) || (my[j] && k > my[j])) { cout << "No\n"; return; }
		chkmax(mx[i], k);
		chkmax(my[j], k);
		g[idx(i, j)] = k--;
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << g[idx(i, j)] << " \n"[j == m];
		}
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n * m; i++) {
			g[i] = 0;
			cnt[i][0] = cnt[i][1] = 0;
		}
		for (int i = 1; i <= n; i++) mx[i] = 0;
		for (int i = 1; i <= m; i++) my[i] = 0;
	}
	return 0;
}
