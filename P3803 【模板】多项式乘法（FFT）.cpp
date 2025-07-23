#include <bits/stdc++.h>
#define vint(f, l, r) vector<int>(f.begin() + l, f.begin() + r)
using namespace std;
using intl = long long;
const intl N_ = 1e5 + 10, Mod = 998244353;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
void dft(vector<int> &p, int inv) {
	int n = p.size(); vector<int> q(n);
	for (int k = n >> 1; k; k >>= 1) {
		int wn = fpow(3, (Mod - 1) / (n / k));
		if (inv == -1) wn = fpow(wn, Mod - 2);
		for (int i = 0, w = 1; i < n; i += k, w = (intl) w * wn % Mod)
			for (int j = 0; j < k; j++)
				q[i + j] = (p[2 * i % n + j] + (intl) w * p[2 * i % n + j + k]) % Mod;
		p.swap(q);
	}
	if (inv == -1) {
		int inv_n = fpow(n, Mod - 2);
		for (int i = 0; i < n; i++) p[i] = (long long)p[i] * inv_n % Mod;
	}
}
vector<int> convolution(vector<int> a, vector<int> b) {
	int m = a.size() + b.size() - 1, n = 1 << (32 - __builtin_clz(m - 1));
	if (a.size() < 64 && b.size() < 64) {
		vector<int> c(m);
		for (int i = 0; i < (int)a.size(); i++)
			for (int j = 0; j < (int)b.size(); j++)
				c[i + j] = (c[i + j] + (long long)a[i] * b[j]) % Mod;
		return c;
	}
	a.resize(n), b.resize(n);
	dft(a, 1), dft(b, 1);
	for (int i = 0; i < n; ++i) a[i] = (long long)a[i] * b[i] % Mod;
	dft(a, -1);
	return vector<int>(a.begin(), a.begin() + m);
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<int> a, b;
	for (int i = 0; i <= n; ++i) {
		int x; cin >> x;
		a.push_back(x);
	}
	for (int i = 0; i <= m; ++i) {
		int x; cin >> x;
		b.push_back(x);
	}
	auto c = convolution(a, b);
	for (int x : c) cout << x << " ";
	return 0;
}
