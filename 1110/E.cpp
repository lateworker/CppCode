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
const int N = 300000, PN = 26013;
int prm[PN + 10], pn, isnp[N + 10];
intl fpow(intl a, intl b) { intl c = 1; for (; b; a *= a, b >>= 1) if (b & 1) c *= a; return c; }
vector<pii> gtprm(int x) {
	if (x == 1) return vector<pii>{{1, 1}};
	vector<pii> vec;
	while (x > 1) {
		if (vec.empty() || vec.back().first != isnp[x]) vec.emplace_back(isnp[x], 1);
		vec.back().second *= prm[isnp[x]];
		x /= prm[isnp[x]];
	} return vec;
}
void init_prm() {
	isnp[0] = isnp[1] = 0;
	for (int i = 2; i <= N; i++) {
		if (!isnp[i]) prm[++pn] = i;
		for (int j = 1; j <= pn && (intl) i * prm[j] <= N; j++) {
			isnp[i * prm[j]] = j;
			if (i % prm[j] == 0) break;
		}
	}
	for (int i = 1; i <= pn; i++) isnp[prm[i]] = i;
}
int q, n; intl ans[N + 10];
vector<pii> qry[N + 10];
vector<pii> g[N + 10];
struct Bit {
	intl st[N + 10];
	void modify(int u, intl val) { for (; u <= n; u += u & -u) st[u] += val; }
	intl query(int u) { intl res = 0; for (; u; u -= u & -u) res += st[u]; return res; }
} st;
void update(int i, bool isadd) {
	int ma = 0;
	for (auto [p, v] : g[i]) chkmax(ma, v);
	st.modify(i, isadd ? ma : -ma);
}
int main() {
	init_prm();
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r;
		qry[l].emplace_back(r, i);
		chkmax(n, r);
	}
	for (int i = n; i >= 1; i--) {
		for (auto [j, c] : gtprm(i)) g[i].emplace_back(c, i);
		update(i, true);
		for (intl x = i << 1; x <= n; x += i) {
			update(x, false);
			for (auto &[p, v] : g[x])
				{ if (i % p == 0) v = i; }
			update(x, true);
		}
		for (auto [j, idx] : qry[i]) ans[idx] = st.query(j);
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
