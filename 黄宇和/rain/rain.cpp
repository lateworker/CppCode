#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const int N = 200000, Mod = 998244353;
inline int fpow(int a, int b) { int c = 1; for(; b; a = (intl) a * a % Mod, b >>= 1) if (b & 1) c = (intl) c * a % Mod; return c; }
int n, m, hma;
vector<pair<int, int>> g[N + 10];
tuple<int, int, int> e[N + 10];
struct DSU {
	int fa[N + 10];
	void init(int n) { for (int i = 1; i <= n; i++) fa[i] = i; }
	int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
	void merge(int u, int v) {
		u = find(u), v = find(v);
		fa[u] = v;
	}
} st;
namespace Task1 {
	bool task1() { return hma == 1; }
	int main() {
		st.init(n);
		for (int i = 1; i <= m; i++) {
			int u, v, w; tie(u, v, w) = e[i];
			if (!w) st.merge(u, v);
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			if (st.fa[i] == i) ++cnt;
		cout << fpow(2, cnt) << "\n";
		return 0;
	}
}
namespace Task2 {
	bool task2() {
		for (int i = 2; i <= m; i++) {
			if (get<2>(e[i]) != get<2>(e[1])) return false;
		} return true;
	}
	int main() {
		int d = get<2>(e[1]);
		intl ans = fpow(d + 1, n);
		st.init(n);
		for (int i = 1; i <= m; i++) {
			st.merge(get<0>(e[i]), get<1>(e[i]));
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			if (st.fa[i] == i) ++cnt;
		ans += fpow(hma - d, cnt), ans %= Mod;
		cout << ans << "\n";
		return 0;
	}
}
namespace Task3 {
	bool task3() { return n <= 1000 && m <= 1000 && hma <= 1000; }
	int main() {
		vector<int> idx(m); iota(idx.begin(), idx.end(), 1);
		sort(idx.begin(), idx.end(), [&](int i, int j) { return get<2>(e[i]) < get<2>(e[j]); });
		auto u = idx.begin();
		intl ans = 0;
		st.init(n);
		for (int h = 0; h <= hma; h++) {
			while (get<2>(e[*u]) < h) {
				st.merge(get<0>(e[*u]), get<1>(e[*u])), u++;
			}
			int cnt = 0;
			for (int i = 1; i <= n; i++)
				if (st.fa[i] == i) ++cnt;
			ans += ((intl) fpow(h + 1, cnt) - fpow(h, cnt) + Mod) % Mod, ans %= Mod;
		}
		cout << ans << "\n";
		return 0;
	}
}
int main() { ffopen(rain);
	cin >> n >> m >> hma;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
		e[i] = {u, v, w};
	}
	if (Task1::task1()) return Task1::main();
	if (Task2::task2()) return Task2::main();
	if (Task3::task3()) return Task3::main();
	return 0;
}
