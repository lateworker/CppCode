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
const intl M = 5000, N = 1000000000, Mod = 1000000007;

int n, m;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }

struct Poly {
	vector<int> val;
	int size() const { return val.size(); }
	void push_back(int x) { val.push_back(x); }
	bool empty() const { return val.empty(); }
	int& operator[] (int i) { return val[i]; }
	int operator[] (int i) const { return val[i]; }
};
Poly derivate(const Poly& a) {
	Poly b;
	for (int i = 1; i < a.size(); i++) {
		b.push_back((intl) i * a[i] % Mod);
	} return b;
}
Poly operator- (const Poly& a) {
	Poly c;
	for (int i = 0; i < a.size(); i++) {
		c.push_back((Mod - a[i]) % Mod);
	} return c;
}
Poly operator+ (const Poly& a, const Poly& b) {
	Poly c; int len = max(a.size(), b.size());
	for (int i = 0; i < len; i++) {
		intl sum = 0;
		if (i < a.size()) sum += a[i];
		if (i < b.size()) sum += b[i];
		c.push_back(sum % Mod);
	} return c;
}
Poly operator- (const Poly& a, const Poly& b) { return a + (-b); }
Poly operator* (const Poly& a, const int& b) {
	Poly c;
	for (int i = 0; i < a.size(); i++) {
		c.push_back((intl) a[i] * b % Mod);
	} return c;
}

int main() {
	cin >> n >> m;
	Poly a, b;
	for (int i = 0; i <= m; i++) {
		int x; cin >> x;
		a.push_back(x);
	}
	for (int i = 0; i <= m; i++) {
		int x; cin >> x;
		b.push_back(x);
	}
	if (n & 1) {
		Poly ta = a, tb = b;
		a = tb + derivate(tb);
		b = ta - derivate(ta);
		--n;
	}
	
	int k = n >> 1;
	Poly ra, rb;
	for (int i = 0, cc = 1; i <= k; i++) {
		if (a.empty() && b.empty()) break;
		ra = ra + a * (i & 1 ? (Mod - cc) % Mod : cc);
		rb = rb + b * (i & 1 ? (Mod - cc) % Mod : cc);
		cc = (intl) cc * (k - i) % Mod * fpow(i + 1, Mod - 2) % Mod;
		a = derivate(derivate(a));
		b = derivate(derivate(b));
	}
	
	for (int i = 0; i <= m; i++) cout << ra[i] << " \n"[i == m];
	for (int i = 0; i <= m; i++) cout << rb[i] << " \n"[i == m];
	return 0;
}
