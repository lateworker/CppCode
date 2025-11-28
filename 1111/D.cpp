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
const int LGA = 30, N = 200000;
int n, s, ans[N + 10];
void slove() {
	cin >> n >> s;
	if ((s & 1) || s < n || n == 1) { cout << "-1\n"; return; }
	vector<pii> stk;
	int cnt = 0;
	for (int i = 0; i < LGA; i++) {
		if (s >> 1 >> i & 1) {
			stk.emplace_back(i, 2);
			cnt += 2;
		} else {
			stk.emplace_back(i, 0);
		}
	}
	while (cnt < n) {
		auto [i, c] = stk.back(); stk.pop_back();
		if (!c) continue;
		stk.back().second += 4, c -= 2, cnt += 2;
		if (c) stk.emplace_back(i, c);
	}
	int p = 1;
	while (!stk.empty()) {
		auto& [i, c] = stk.back();
		if (!c) { stk.pop_back(); continue; }
		if (c > n) {
			if (!i) { cout << "-1\n"; return; }
			prev(prev(stk.end()))->second += 4, c -= 2;
		}
		ans[p] |= (1 << i), --c;
		p = p % n + 1;
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) ans[i] = 0;
	}
	return 0;
}
