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
int n, a[N + 10];
void slove() {
	cin >> n;
	int las = 0;
	vector<pii> vec;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		if (i == n || a[i] != a[i + 1]) {
			vec.emplace_back(a[i], i - las);
			las = i;
		}
	}
	bool trn = 0;
	while (!vec.empty()) {
		trn ^= 1;
		vector<pii> cur;
		pii las = {0, 0};
		for (auto& [val, cnt] : vec) {
			if (!--cnt) continue;
			if (las == make_pair(0, 0)) {
				las = make_pair(val, cnt);
			} else {
				if (las.first != val) {
					cur.push_back(las);
					las = make_pair(val, cnt);
				} else las.second += cnt;
			}
		}
		if (las != make_pair(0, 0)) cur.push_back(las);
		vec.swap(cur);
	}
	cout << (trn ? "aLIcE" : "bOB") << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
