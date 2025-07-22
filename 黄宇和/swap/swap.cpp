#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
freopen((string(s) + ".in").c_str(), "r", stdin); \
freopen((string(s) + ".out").c_str(), "w", stdout);
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000, BLC = 5;
int n, tn, m, s[M + 3], t[M + 3], a[N + 3], ans[N + 3];
namespace BF {
	void calc(int i) {
		vector<bool> vis(n + 10);
		int u = i, cnt = 0;
		vector<int> vec;
		for (int j = 1; j <= n; j++) vis[j] = false;
		while (true) {
			for (int j = 1; j <= m; j++) {
				u = (u == s[j] ? t[j] : u == t[j] ? s[j] : u);
				if (!vis[u]) ++cnt, vis[u] = true;
			}
			vec.push_back(u);
			if (u == i) break;
		}
		for (int j : vec) ans[j] = cnt;
	}
	int main() {
		for (int i = 1; i <= n; i++) if (!ans[i]) calc(i);
		for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
		return 0;
	}
}
namespace AC {
	bitset<N / BLC + 3> ps[N + 3];
	int fa[N + 3];
	int findfa(int u) { return fa[u] == u ? u : fa[u] = findfa(fa[u]); }
	void mergefa(int u, int v) {
		u = findfa(u), v = findfa(v);
		if (u == v) return;
		fa[u] = v, ps[v] |= ps[u];
	}
	inline bool check(int pos, int bid) {
		return bid * tn < pos && pos <= (bid + 1) * tn;
	}
	void calc(int bid) {
		for (int i = 1; i <= n; i++) {
			ps[i].reset();
			fa[i] = a[i] = i;
			if (check(i, bid)) ps[i].set(i - bid * tn);
		}
		for (int i = 1; i <= m; i++) {
			if (check(t[i], bid)) ps[a[s[i]]].set(t[i] - bid * tn);
			if (check(s[i], bid)) ps[a[t[i]]].set(s[i] - bid * tn);
			swap(a[s[i]], a[t[i]]);
		}
		for (int i = 1; i <= n; i++) mergefa(a[i], i);
		for (int i = 1; i <= n; i++) ans[i] += ps[findfa(i)].count();
	}
	int main() {
		for (int i = 0; i <= BLC; i++) calc(i);
		for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
		return 0;
	}
}

int main() { ffopen("swap");
	cin >> n >> m; tn = n / BLC;
	for (int i = 1; i <= m; i++) cin >> s[i] >> t[i];
	if (n <= 2000 && m <= 4000) return BF::main();
	return AC::main();
}
