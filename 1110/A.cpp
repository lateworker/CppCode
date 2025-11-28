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
const intl N = 100000;

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
	
};

auto& operator<< (auto& cerr, const Hax& a) {
	cerr << '{' << a[0] << ',' << a[1] << '}';
	return cerr;
}

char s[N + 10];

void slove() {
	int n; cin >> n;
	Hax hh;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		hh = hh * 1 + Hax(s[i]);
	}
	set<Hax> st;
	for (int i = 1; i <= n - 2; i++) {
		Hax x(s[i]), y(s[i + 1]), z(s[i + 2]);
		Hax now = hh;
		now = now - x * (n - i) - y * (n - i - 1) - z * (n - i - 2);
		now = now + y * (n - i) + z * (n - i - 1) + x * (n - i - 2);
		st.insert(now);
	}
	cout << st.size() << '\n';
}
int main() { ffopen();
	Hax::init();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
