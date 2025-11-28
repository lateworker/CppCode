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
const intl N = 100000, inf = 0x3f3f3f3f3f3f3f3f;
intl n, m, t1, t2, f[N + 10];
struct Deque {
	int que[N * 2 + 10], l, r;
	Deque() { clear(); }
	bool empty() { return r < l; }
	void push_back(int x) { que[++r] = x; }
	void pop_back() { --r; }
	void pop_front() { ++l; }
	int back() { return que[r]; }
	int front() { return que[l]; }
	void clear() { l = 0, r = -1; }
} que;
void slove() {
	cin >> n >> m >> t1 >> t2;
	if (t1 <= t2) {
		for (int i = 1; i <= n; i++) {
			cout << (m + t1) * i <<  " \n"[i == n]; 
		} return;
	}
	memset(f, 0x3f, sizeof f), f[0] = 0;
	que.clear(), que.push_back(0); int p = 0;
#define gt(p) (f[p] - (t1 - t2) * (p))
	for (int i = 1; i <= n; i++) {
		while (p < i && f[p] < m * i) ++p; 
		while (!que.empty() && que.front() < p) que.pop_front();
		intl res = inf;
		if (p > 0) chkmin(res, m * i - (t1 - t2) * (p - 1));
		if (!que.empty()) chkmin(res, gt(que.front()));
		f[i] = res + (t1 + t2) * i;
		while (!que.empty() && gt(i) <= gt(que.back())) que.pop_back();
		que.push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		cout << f[i] - t2 * i << " \n"[i == n];
	}
}
int main() { ffopen(a2);
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
