#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define int long long
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
using pii = pair<int, int>;
const int N = 300000, A = 1000000000;
int n, k, a[N + 10];
bool check(int h) {
	int cnt = 0;
	vector<int> vec;
	for (int i = 1; i <= n; i++) {
		int x = a[i];
		if (x < h) {
			if (x % k) {
				if (x * k >= h) vec.push_back(1);
			} else while (x % k == 0) x /= k, ++cnt;
		} else {
			if (x % k) {
				vec.push_back(0);
			} else {
				while (x % k == 0 && x / k >= h) x /= k, ++cnt;
				int cur = 0;
				while (x % k == 0) x /= k, ++cnt, ++cur;
				vec.push_back(cur);
			}
		}
	}
	if ((int)vec.size() < h) return false;
	sort(vec.begin(), vec.end());
	for (int i = 0; i < h; i++) {
		cnt -= vec[i];
	}
	return cnt >= 0;
}
void slove() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int l = 0, r = A;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l << '\n';
}
signed main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
