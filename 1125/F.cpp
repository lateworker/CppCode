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
const int N = 200000, LGA = 23, inf = 0x3f3f3f3f;
int n, a[N + 10];
struct Seg { int l, r; };
int gtlen(const Seg& u) { return max(u.r - u.l + 1, 0); }
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	set<int> b; b.insert(a[1]);
	int ans = 0;
	vector<Seg> seg = {{0, 2000000000}};
	for (int i = 2; i <= n; i++) {
		auto update = [&](int l, int r) {
			vector<Seg> now;
			for (auto [sl, sr] : seg) {
				if (sr < l || r < sl) { now.emplace_back(sl, sr); continue; }
				Seg now1 = {sl, l - 1}, now2 = {r + 1, sr};
				ans += sr - sl + 1 - gtlen(now1) - gtlen(now2);
				if (now1.l <= now1.r) now.push_back(now1);
				if (now2.l <= now2.r) now.push_back(now2);
			}
			seg.swap(now);
		};
		auto u = b.upper_bound(a[i]);
		if (u != b.end()) update(*u - a[i] + 1, *u + a[i] - 1);
		if (u != b.begin()) --u, update(a[i] - *u + 1, a[i] + *u - 1);
		b.insert(a[i]);
		cout << ans << " \n"[i == n];
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
