#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
int n, a[N + 10], b[N + 10];
vector<pair<int, int>> f;
int main() { ffopen(sequence);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
	}
	int ans = 0;
	vector<int> stk;
	for (int i = 1; i <= n; i++) {
		while (!stk.empty() && a[stk.back()] < a[i]) stk.pop_back();
		stk.push_back(i);
		vector<pair<int, int>> g; g.swap(f);
//		for (int j = g.size() - 1; j; j--) g[j - 1] = max(g[j - 1], g[j]);
		int j = 0;
		
		for (int p : stk) {
			int x = a[p];
			if (x > b[i]) continue;
			int res = 0;
			while (j < (int) g.size() && g[j].first > x) ++j;
//			for (auto [y, val] : g) {
//				if (y <= x) res = max(res, val);
//			}
			if (j != (int) g.size()) res = g[j].second;
			f.emplace_back(x, res + 1);
		}
		
		for (auto [x, val] : f) ans = max(ans, val);
	}
	cout << ans << "\n";
	return 0;
}
