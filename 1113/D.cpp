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
const int N = 100000, inf = 0x3f3f3f3f;
int n, cnt[N + 10], ans[N + 10];
vector<int> g[N + 10];
int gtcost(int x, int y) {
	if (x < y) swap(x, y);
	return y ? abs(__builtin_clz(x) - __builtin_clz(y)) : (32 - __builtin_clz(x));
}
void merge(vector<int>& x, const vector<int>& y) {
	int i = 0, j = 0;
	vector<int> z;
	while (i < (int)x.size() || j < (int)y.size()) {
		if (i == (int)x.size()) { z.push_back(y[j++]); continue; }
		if (j == (int)y.size()) { z.push_back(x[i++]); continue; }
		z.push_back(x[i] < y[j] ? x[i++] : y[j++]);
	}
	x.swap(z);
}
void slove() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> cnt[i];
	for (int i = 0; i <= n; i++) {
		if (!cnt[i]) {
			ans[i] = inf;
			g[i].push_back(i);
		}
	}
	for (int i = n; i >= 0; i--) {
		vector<int> vec;
		int x = cnt[i];
		for (int j : g[i]) {
			if (x <= 1) vec.push_back(j);
			else ans[j] = gtcost(i, j), --x;
		}
		g[i].swap(vec);
		merge(g[i >> 1], g[i]);
	}
	int ps = 0;
	for (int i = 0; i <= n; i++) {
		if (ans[i] == inf) {
			cout << ps << ' ';
			for (int j = i + 1; j <= n; j++) cout << "-1 ";
			break;
		}
		cout << ps + (ans[i] ? 0 : cnt[i]) << ' ';
		ps += ans[i];
	} cout << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 0; i <= n; i++) {
			cnt[i] = ans[i] = 0;
			g[i].clear();
		}
	}
	return 0;
}
