#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 250000, K = 500, Mod = 998244353;
intl fpow(intl a, intl b) { a %= Mod, b %= Mod; intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
int n, tn, m, a[N + 10], ans[N + 10], cnt[N + 10];
struct Qry { int l, r, x, i; } q[N + 10];
intl fac[N + 10], ifac[N + 10], b[K + 10], c[K + 10];
intl inv(intl a) { return ifac[a] * fac[a - 1] % Mod; }
int idx(int i) { return (i - 1) / tn + 1; }
void add(int i) {
	int x = a[i];
	++c[idx(x)];
	(b[idx(x)] *= ++cnt[x]) %= Mod;
}
void del(int i) {
	int x = a[i];
	--c[idx(x)];
	(b[idx(x)] *= inv(cnt[x]--)) %= Mod;
}
intl query(int x) {
	intl s = 0, t = 1;
	for (int i = 1; i < idx(x); i++)
		s += c[i], (t *= b[i]) %= Mod;
	for (int i = (idx(x) - 1) * tn + 1; i < x; i++)
		s += cnt[i], (t *= fac[cnt[i]]) %= Mod;
	return fac[s] * fpow(t, Mod - 2) % Mod;
}
int main() {
	cin >> n >> m; tn = sqrt(n) + 0.5;
	for (int i = 1; i <= n / tn + 1; i++) b[i] = 1;
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % Mod;
	ifac[n] = fpow(fac[n], Mod - 2); for (int i = n; i >= 1; i--) ifac[i - 1] = ifac[i] * i % Mod;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++)
		cin >> q[i].l >> q[i].r >> q[i].x, q[i].i = i;
	sort(q + 1, q + 1 + m, [&](const Qry& u, const Qry& v) { return u.r / tn == v.r / tn ? u.l < v.l : u.r < v.r; } );
	int l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		const auto& [lp, rp, xp, ip] = q[i];
		while (lp < l) add(--l);
		while (r < rp) add(++r);
		while (l < lp) del(l++);
		while (rp < r) del(r--);
		ans[ip] = query(xp);
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
	return 0;
}
