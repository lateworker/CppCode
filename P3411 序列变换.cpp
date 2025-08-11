#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
const int N = 1000000;
int n, a[N + 10];
vector<int> vec[N + 10];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], vec[a[i]].push_back(i);
	int m = *max_element(a + 1, a + 1 + n), now = 0;
	deque<int> que;
	for (int i = 1; i <= m; i++) {
		for (auto u = vec[i].rbegin(); u != vec[i].rend(); u++) {
			int p = *u;
			while (!que.empty() && p < que.back()) {
				while (a[que.front()] != a[que.back()]) que.pop_front();
				que.pop_back();
			}
			chkmax(now, (int) que.size() + (int) (u - vec[i].rbegin() + 1));
		}
		for (auto p : vec[i]) que.push_back(p);
	}
	cout << n - now << "\n";
	return 0;
}
