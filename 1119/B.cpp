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
const int N = 200000, A = 50;
int n, m, a[N + 10], sum[A + 10];
priority_queue<int, vector<int>, greater<int> > que[A + 10];
bitset<A + 10> atv;
void add(int j, int x) {
	sum[j] += x;
	que[j].push(x);
	while ((int)que[j].size() > m) {
		x = que[j].top(); que[j].pop();
		sum[j] -= x;
	}
}
void slove() {
	cin >> n >> m; m -= 2;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= A; j++) {
			if (!atv[j]) continue;
			if ((int)que[j].size() == m) chkmax(ans, (sum[j] << 1) + a[i] + j);
			add(j, a[i]);
		}
		atv[a[i]] = true;
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int j = 1; j <= A; j++) que[j] = {}, sum[j] = 0, atv[j] = false;
	}
	return 0;
}
