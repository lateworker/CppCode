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
struct Hax {
	intl a[2];
	inline static intl Mod[2] = {19260817, 1000000007}, Base = 31, pBase[N + 10][2];
	Hax() { a[0] = a[1] = 0; }
	Hax(char c) { a[0] = a[1] = c - 'a' + 1; }
	static void init() {
		for (int i : {0, 1}) {
			pBase[0][i] = 1;
			for (int j = 1; j <= N; j++) pBase[j][i] = pBase[j - 1][i] * Base % Mod[i];
		}
	}
	intl operator[] (const int& i) const { return a[i]; }
	intl& operator[] (const int& i) { return a[i]; }
	Hax operator+ (const Hax& b) const {
		Hax c; for (int i : {0, 1}) c[i] = (a[i] + b[i]) % Mod[i]; return c;
	}
	Hax operator* (const int& b) const {
		Hax c; for (int i : {0, 1}) c[i] = a[i] * pBase[b][i] % Mod[i]; return c;
	}
	Hax operator- () const {
		Hax c;
		for (int i : {0, 1}) {
			c[i] = Mod[i] - a[i];
			if (c[i] >= Mod[i]) c[i] -= Mod[i];
		}
		return c;
	}
	Hax operator- (const Hax& b) const { return (*this) + (-b); }
	auto operator<=> (const Hax& b) const { return make_pair(a[0], a[1]) <=> make_pair(b[0], b[1]); }
	bool operator== (const Hax& b) const { return a[0] == b[0] && a[1] == b[1]; }
};
Hax h[N + 10];
Hax gth(int l, int r) { return l <= r ? h[r] - h[l - 1] * (r - l + 1) : 0; }
void slove() {
	string s; cin >> s;
	int n = s.size(); s = '#' + s;
	if (n & 1) { cout << "0\n"; return; }
	for (int i = 1; i <= n; i++) {
		h[i] = h[i - 1] * 1 + s[i];
	}
	int ans = 0;
	for (int i = 0; i <= (n >> 1); i++) {
		if (gth(1, i) != gth(i + 1, i << 1)) continue;
		int j = i << 1 | 1, k = (j + n) >> 1;
		if (gth(j, k) != gth(k + 1, n)) continue;
		++ans;
	}
	cout << ans << '\n';
}
int main() { ffopen();
	Hax::init();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
