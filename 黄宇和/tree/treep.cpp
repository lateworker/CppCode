#include <bits/stdc++.h>
using namespace std;
inline void ffopen(string s) {
	cin.tie(0)->sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int N = 100000;
int n, a[N + 10], b[N + 10], fa[N + 10], son[N + 10], siz[N + 10], dep[N + 10], dfn[N + 10], idfn[N + 10], top[N + 10], psz;
vector<int> g[N + 10];
bool isq[N + 10];
int mul[N + 10], sum[N + 10];

int ans;
void trav(int u) {
	int p = fa[u];
	if (p == 0) return;
	ans += a[p] * siz[p];// - a[p] * siz[u];
	trav(p);
}
void upd(int u) {
	if (u == 0) return;
	++siz[u], upd(fa[u]);
}
int main() {
	cin >> n >> a[1]; ++n;
	ans = a[1], siz[1] = 1;
	for (int i = 2; i <= n; i++) {
		int op; cin >> op;
		if (op == 1) {
			cin >> a[i] >> fa[i];
			g[fa[i]].push_back(i);
			trav(i), upd(i); ans += a[i];
		} else if (op == 2) cout << ans << "\n";
	}
	
	return 0;
}
