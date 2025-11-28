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
const intl N = 100000, Mod = 998244353;

intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }

void dft(vector<intl>& p, bool is_inv) {
	intl n = p.size(); vector<intl> q(n);
	for (intl k = n >> 1; k; k >>= 1) {
		intl wn = fpow(3, (Mod - 1) / (n / k));
		if (is_inv) wn = fpow(wn, Mod - 2);
		for (intl i = 0, w = 1; i < n; i += k, w = (intl) w * wn % Mod) {
			for (intl j = 0; j < k; j++)
				q[i + j] = ((intl) w * p[(i << 1) % n + j + k] + p[(i << 1) % n + j]) % Mod;
		} p.swap(q);
	}
	if (is_inv) {
		intl inv_n = fpow(n, Mod - 2);
		for (intl i = 0; i < n; i++) p[i] = (intl) p[i] * inv_n % Mod;
	}
}
vector<intl> convolution_naive(const vector<intl>& a, const vector<intl>& b) {
	vector<intl> c(a.size() + b.size() - 1);
	for (int i = 0; i < (int)a.size(); i++) {
		for (int j = 0; j < (int)b.size(); j++) {
			c[i + j] += a[i] * b[j] % Mod;
			if (c[i + j] >= Mod) c[i + j] -= Mod;
		}
	} return c;
}
vector<intl> convolution_ntt(vector<intl> a, vector<intl> b) {
	intl m = a.size() + b.size() - 1, n = 1 << (32 - __builtin_clzll(m - 1));
	a.resize(n), b.resize(n);
	dft(a, false), dft(b, false);
	for (intl i = 0; i < n; i++) a[i] = (intl) a[i] * b[i] % Mod;
	dft(a, true);
	return vector<intl>(a.begin(), a.begin() + m);
}
vector<intl> convolution(const vector<intl>& a, const vector<intl>& b) { return a.size() + b.size() <= 16 ? convolution_naive(a, b) : convolution_ntt(a, b); }

intl n, m, q, pw2[N + 10], a[N + 10];
map<int, int> cnt;
vector<intl> cdq(int l, int r) {
	if (l == r) return vector<intl>{1, a[l]};
	int mid = (l + r) >> 1;
	return convolution(cdq(l, mid), cdq(mid + 1, r));
}
int main() { ffopen();
	pw2[0] = 1;
	for (int i = 1; i <= N; i++) pw2[i] = (pw2[i - 1] << 1) % Mod;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int c; cin >> c;
		++cnt[c];
	}
	for (auto [v, c] : cnt) a[++m] = (pw2[c] - 1 + Mod) % Mod;
	vector<intl> f = cdq(1, m);
	f.resize(n + 5);
	for (int j = 1; j <= n; j++) f[j] += f[j - 1], f[j] %= Mod;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		cout << (f[r] - f[l - 1] + Mod) % Mod << '\n';
	}
	return 0;
}
