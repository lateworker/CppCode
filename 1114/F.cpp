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
const int N = 200000;
struct Hax {
	intl a[2];
	inline static intl Mod[2] = {19260817, 1000000007}, Base = 3, pBase[N + 10][2];
	Hax() { a[0] = a[1] = 0; }
	Hax(char c) { a[0] = a[1] = (c == ')') + 1; }
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
};
int n;
Hax hax[N + 10];
map<Hax, int> cnt;
void slove() {
	cin >> n;
	vector<int> stk;
	cnt.clear();
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		hax[i] = hax[i - 1] * 1 + c;
		if (c == '(') stk.push_back(i);
		else if (!stk.empty()) {
			int l = stk.back(), r = i;
			stk.pop_back();
			++cnt[hax[r] - hax[l - 1] * (r - l + 1)];
		}
	}
	intl ans = 0;
	for (auto [hh, cc] : cnt) {
		ans += ((intl) cc * (cc - 1)) >> 1;
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
