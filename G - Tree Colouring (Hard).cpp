#define MultiCase (cin >> CaseId)
#define Main(Callback) main() { int CaseId = 1; { Callback } CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else return 0
#define ffopen(s) \
ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cerr.tie(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
//
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
template<typename T_, size_t N_, T_ DEFAULT_ = T_()> class Array { T_ val[N_]; size_t ver[N_], clk; public: Array() { clk=1; } T_& operator[] (size_t i) { if(ver[i]!=clk){ver[i]=clk,val[i]=DEFAULT_;} return val[i]; } void clear() { ++clk; } };
template<typename T_, size_t N_> class Graph { inline static size_t psz; inline static std::pair<T_, size_t> pool[N_]; struct iterator { size_t now; T_& operator* () const { return pool[now].first; } bool operator== (iterator it) const { return now == it.now; } iterator& operator++ () { now=pool[now].second; return *this; } }; size_t head; public: Graph() { head = 0; } iterator begin() const { return {head}; } iterator end() const { return {0}; } void push_back(const T_& val) { ++psz,this->pool[psz]={val, head},head=psz; } void clear() { psz=head=0; } };
using namespace std;
using intl = long long;
const int N = 200000;
int n, deg[N + 10], ans[N + 10], rt, psz;
Graph<int, N * 2 + 10> g[N + 10];
void dfs(int u, int p) {
	vector<int> vec;
	for (int v : g[u]) if (v != p) {
		dfs(v, u), vec.push_back(v);
	}
	if (u == rt) { ans[u] = ans[vec.back()] = ++psz; }
	else {
		for (int i = 0; i < (int) vec.size(); i += 2) {
			ans[vec[i]] = ans[vec[i + 1]] = ++psz;
		}
	}
}
int Main(ffopen(); MultiCase; ) {
	for (int i = 1; i <= n; i++) {
		deg[i] = ans[i] = 0;
		g[i].clear();
	} psz = 0;
	
	cin >> n;
	int cnt = 1;
	for (int i = 2; i <= n; i++) {
		int fa; cin >> fa;
		g[fa].push_back(i);
		g[i].push_back(fa);
		++deg[i], ++deg[fa];
		if (deg[fa] & 1) --cnt; else ++cnt;
		if (~ deg[i] & 1) ++cnt;
		cout << (cnt ? 0 : 1);
	} cout << '\n';
	for (int i = 1; i <= n; i++) {
		if (~ deg[i] & 1) { Return; }
		if (deg[i] == 1) rt = i;
	}
	dfs(rt, 0);
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
} Return; }
