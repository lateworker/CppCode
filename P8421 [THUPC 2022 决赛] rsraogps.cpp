#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000, M = 5000000;
int n, m, a[N + 10], b[N + 10], c[N + 10], ans[N + 10];
int ap[N + 10], bp[N + 10], cp[N + 10], s[N + 10];
vector<pair<int, int>> qry[N + 10];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= m; i++) {
		int l, r; cin >> l >> r;
		qry[r].emplace_back(l, i);
	}
	for (int r = 1; r <= n; r++) {
		for (int i = 1; i < r; i++) {
			ap[i] &= a[r];
			bp[i] |= b[r];
			cp[i] = gcd(cp[i], c[r]);
		}
		ap[r] = a[r], bp[r] = b[r], cp[r] = c[r], s[r] = s[r - 1];
		for (int i = 1; i <= r; i++) {
			for (int x = 1; x <= i; x++) {
				s[i] += ap[x] * bp[x] * cp[x];
			}
		}
		for (auto [l, idx] : qry[r]) {
			ans[idx] = s[r] - s[l - 1];
		}
		for (int i = 1; i <= n; i++) cout << s[i] << " \n"[i == n];
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
	return 0;
}
