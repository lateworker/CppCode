#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using namespace std;
const int N = 300000, LN = __lg(N) + 1;
int n, tn, las[N + 10], f[N + 10], st[LN + 2][N + 10];
int query(int l, int r) {
	if (r < l) return 0;
	int d = __lg(r - l + 1);
	return max(st[d][l], st[d][r - (1 << d) + 1]);
}
bool ans[N + 10];
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> st[0][i], st[0][i] += i;
		las[i] = i;
	} tn = __lg(n);
	for (int j = 1; j <= tn; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	}
	for (int i = 2; i <= n; i++) {
//		f[i] = f[i - 1];
		f[i] = f[i - 1] >= i ? max(f[i - 1], st[0][i]) : f[i - 1];
		int p = lower_bound(f, f + i, i - (st[0][i] - i) - 1) - f;
		if (p != i) {
			int now = max(i - 1, query(p + 1, i - 1));
			if (now > f[i]) f[i] = now, las[i] = p;
		}
	}
//	for (int i = 1; i <= n; i++) cerr << f[i] << " \n"[i == n];
//	for (int i = 1; i <= n; i++) cerr << las[i] << " \n"[i == n];
	cout << (f[n] >= n ? "YES" : "NO") << "\n";
	if (f[n] >= n) {
		for (int u = n; u; u--) {
			if (las[u] == u) ans[u] = true;
			else {
				ans[u] = false;
				for (int i = las[u] + 1; i < u; i++) ans[i] = true;
				u = las[u] + 1;
			}
		}
		for (int i = 1; i <= n; i++) cout << (ans[i] ? 'R' : 'L');
		cout << "\n";
	}
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
		for (int i = 1; i <= n; i++) {
			f[i] = 0, ans[i] = false;
		}
	}
	return 0;
}
