#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
freopen((string(s) + ".in").c_str(), "r", stdin); \
freopen((string(s) + ".out").c_str(), "w", stdout);
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000, BLC = 5;
int n, tn, m, s[M + 3], t[M + 3], a[N + 3], ans[N + 3];
char ver[N + 3];
bitset<N / BLC + 3> ps[N + 3];
int fa[N + 3];
int findfa(int u) { return fa[u] == u ? u : fa[u] = findfa(fa[u]); }
inline void tryclear(int i, int bid) {
	if (ver[i] != bid) ps[i].reset(), ver[i] = bid;
}
void mergefa(int u, int v, int bid) {
	u = findfa(u), v = findfa(v);
	if (u == v) return;
	tryclear(u, bid), tryclear(v, bid);
	fa[u] = v, ps[v] |= ps[u];
}
inline bool check(int pos, int bid) {
	return bid * tn < pos && pos <= (bid + 1) * tn;
}
inline void modify(int i, int j, int bid) {
	tryclear(i, bid);
	ps[i].set(j - bid * tn);
}
inline int query(int i, int bid) {
	tryclear(i, bid);
	return ps[i].count();
}
void calc(int bid) {
	for (int i = 1; i <= n; i++) {
//		ps[i].reset();
		fa[i] = a[i] = i;
		if (check(i, bid)) modify(i, i, bid);
	}
	for (int i = 1; i <= m; i++) {
		if (check(t[i], bid)) modify(a[s[i]], t[i], bid);
		if (check(s[i], bid)) modify(a[t[i]], s[i], bid);
		swap(a[s[i]], a[t[i]]);
	}
	for (int i = 1; i <= n; i++) mergefa(a[i], i, bid);
	for (int i = 1; i <= n; i++) ans[i] += query(findfa(i), bid);
}
int main() {
	ffopen("swap");
	cin >> n >> m; tn = n / BLC;
	for (int i = 1; i <= m; i++) cin >> s[i] >> t[i];
	for (int i = 0; i <= BLC; i++) calc(i);
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
	return 0;
}
