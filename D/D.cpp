#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int long long
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
using namespace std;
using intl = long long;
const intl N = 525010, A = N, LGA = __lg(A) + 3;
int n, a[N + 10], fa[N + 10];
vector<int> g[N + 10];
int ch[N * LGA * 5 + 10][2], cnt[N * LGA * 5 + 10], psz;
vector<int> recy;
int node() {
	int u = recy.empty() ? ++psz : recy.back();
	if (!recy.empty()) recy.pop_back();
	ch[u][0] = ch[u][1] = 0, cnt[u] = 0;
	return u;
}
#define L(u) (ch[u][0])
#define R(u) (ch[u][1])
#define calc(u, dep) (intl(cnt[R(u)] & 1) << dep)
bool chkempty(int& u) {
	if (!u) u = node();
	return !cnt[u];
}
void swapson(int u, int dep, intl& sum) {
	if (!cnt[L(u)] && chkempty(R(u))) {
		cnt[R(u)] = cnt[u];
		sum ^= calc(u, dep);
		return;
	}
	sum ^= calc(u, dep);
	swap(L(u), R(u));
	sum ^= calc(u, dep);
}
int dfsmerge(int x, int y) {
	if (!x || !y) return x | y;
	L(x) = dfsmerge(L(x), L(y));
	R(x) = dfsmerge(R(x), R(y));
	cnt[x] += cnt[y];
//	recy.push_back(y);
	return x;
}
struct Trie {
	int root; intl sum;
	void insert(int x) {
		if (root == 0) root = node();
		int u = root; sum ^= x;
		for (int i = 0; i <= LGA; i++, x >>= 1) {
			if (!x) break;
			bool c = x & 1;
			chkempty(ch[u][c]);
			++cnt[u = ch[u][c]];
		}
	}
	void invert() {
		if (root == 0) return;
		int u = root;
		for (int i = 0; i <= LGA; i++, u = L(u)) {
			swapson(u, i, sum);
			if (!cnt[L(u)]) break;
		}
	}
	Trie() { root = 0, sum = 0; }
};
void merge(Trie& x, Trie y) {
	x.root = dfsmerge(x.root, y.root);
	x.sum ^= y.sum;
}
intl ans = 0;
Trie dfs(int u) {
	Trie res;
	res.insert(a[u]);
	for (int v : g[u]) {
		Trie now = dfs(v);
		now.invert();
		merge(res, now);
	}
	ans += res.sum;
	return res;
}
signed main() { ffopen();
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		g[fa[i]].push_back(i);
	}
	dfs(1);
	cout << ans << "\n";
	return 0;
}
