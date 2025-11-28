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
intl n, q, a[N + 10], ans[N + 10];
struct Kque {
	priority_queue<int> sml;
	priority_queue<int, vector<int>, greater<int> > big;
	intl sum_sml, sum_big;
	void insert(int x) {
		if (big.empty() || x >= big.top()) {
			big.push(x), sum_big += x;
		} else {
			sml.push(x), sum_sml += x;
		}
		if (sml.size() > big.size()) {
			big.push(x = sml.top()), sml.pop();
			sum_big += x, sum_sml -= x;
		}
		if (sml.size() + 1 < big.size()) {
			sml.push(x = big.top()), big.pop();
			sum_sml += x, sum_big -= x;
		}
	}
	void clear() {
		sml = {}, big = {};
		sum_sml = sum_big = 0;
	}
	Kque() { clear(); }
} st;
void slove() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i], ans[i] = 0;
	st.clear();
	for (int i = 1; i <= n; i++) {
		st.insert(a[i]);
		if (i & 1) ans[i] = st.sum_big - st.sum_sml;
	}
	for (int i = 1; i <= q; i++) {
		int j; cin >> j;
		cout << ans[j] << " \n"[i == q];
	}
}
int main() {
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
