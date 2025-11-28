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
using piil = pair<intl, intl>;
const intl N = 100000, inf = 0x3f3f3f3f3f3f3f3f;
int n, x, b[N + 10];
intl a[N + 10], vec[N + 10], pw10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000};
int lsh() {
	for (int i = 1; i <= n; i++) vec[i] = a[i];
	sort(vec + 1, vec + 1 + n);
	int m = unique(vec + 1, vec + 1 + n) - vec - 1;
	vec[m + 1] = inf;
	for (int i = 1; i <= n; i++) b[i] = lower_bound(vec + 1, vec + 1 + m, a[i]) - vec;
	return m;
}
struct Segt {
	intl st[N * 3 + 10]; int tn;
	void init(int n) {
		for (tn = 1; tn <= n + 1; tn <<= 1);
		memset(st, 0, (tn + n + 5) * sizeof(st[0]));
	}
	void pushup(int u) { if (u) st[u] = st[u << 1] + st[u << 1 | 1]; }
	void modify(int u, intl val) {
		u += tn; st[u] += val;
		do pushup(u >>= 1); while (u);
	}
	intl query(int l, int r) {
		if (r < l) return 0;
		intl res = 0;
		for (l += tn, r += tn + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += st[l++];
			if (r & 1) res += st[--r];
		} return res;
	}
} st;
void slove() {
	cin >> n >> x;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int m = lsh(); st.init(m);
	intl ans = 0;
	for (int i = 1; i <= n; i++) {
		intl l = lower_bound(vec + 1, vec + 1 + m, pw10[x - 1] - a[i]) - vec;
		intl r = x == 19 ? m : lower_bound(vec + 1, vec + 1 + m, pw10[x] - a[i]) - vec - 1;
		ans += st.query(l, r) * (n - i + 1);
		st.modify(b[i], i);
	}
	cout << ans << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
