#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
#define gc() (eof||(p==SIZE&&(buf[fread(buf,1,SIZE,stdin)]=EOF,(p=0)))||~buf[p]?buf[p++]:(eof=true,EOF))
#define ug(x) (eof=false,buf[--p]=(x))
#define pc(x) (buf[p++]=(x),p==SIZE?fl():p)
#define fl() (fwrite(buf,1,p,stdout),p=0)
namespace FastIn { constexpr size_t SIZE = 1 << 16; size_t p = SIZE; char buf[SIZE | 1], c; bool f, eof; inline void rd(char& x) { while(isspace(x=gc())); } inline void rd(char* s) { while(isspace(*s=gc()));if(eof){return;}for(;!isspace(*s)&&!eof;*++s=gc());ug(*s),*s='\0'; } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128>, void> rd(T& x) { x=f=0;while(isspace(c=gc()));if(eof){return;}if(c=='-'){f=true,c=gc();}for(;isdigit(c);c=gc()){x=(x<<1)+(x<<3)+(c^'0');}ug(c);if(f){x=-x;} } }
namespace FastOut { constexpr size_t SIZE = 1 << 18; char buf[SIZE], c[40]; size_t f, p; struct __{~__(){fl();}}__; inline void wt(char x) { pc(x); } inline void wt(const char* s) { while(*s)pc(*s++); } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128>, void> wt(T x) { if(!x){pc('0');return;}f=0;if(x<0)x=-x,pc('-');while(x){c[f++]=x%10^'0',x/=10;}while(f--){pc(c[f]);} } }
template<typename... Args> inline void rd(Args&... args) { using namespace FastIn; (rd(args), ...); }
template<typename... Args> inline void wtsp(const Args&... args) { using namespace FastOut; ((wt(args), wt(' ')), ...); if constexpr (!sizeof...(args)) wt(' '); }
template<typename... Args> inline void wtln(const Args&... args) { using namespace FastOut; ((wt(args), wt('\n')), ...); if constexpr (!sizeof...(args)) wt('\n'); }
template<class T_, size_t N_>
class Graph {
	inline static size_t psz;
	inline static std::pair<T_, size_t> pool[N_];
	struct iterator {
		size_t now;
		T_& operator* () const { return pool[now].first; }
		bool operator== (iterator it) const { return now == it.now; }
		iterator& operator++ () { now = pool[now].second; return *this; }
	}; size_t head;
public:
	Graph() { head = 0; }
	iterator begin() const { return {head}; }
	iterator end() const { return {0}; }
	void push_back(const T_& val) { ++psz, this->pool[psz] = {val, head}, head = psz; }
	void clear() { psz = head = 0; }
};
using namespace std;
using intl = long long;
const int N = 100000, M = 300000, LGN = __lg(N) + 1, inf = 0x3f3f3f3f;
int n, m, lgn, vec[M + 10], vecpsz;
struct E { int u, v, w; } e[M + 10];
Graph<pair<int, int>, N * 2 + 10> g[N + 10];
struct DSU {
	int fa[N + 10];
	void init(int n) { for (int i = 1; i <= n; i++) fa[i] = i; }
	int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
} dsu;
intl kruskal() {
	static int idx[M + 10];
	iota(idx + 1, idx + m + 1, 1);
	sort(idx + 1, idx + m + 1, [&](int i, int j) { return e[i].w < e[j].w; } );
	dsu.init(n); intl res = 0;
	for (int ii = 1; ii <= m; ii++) {
		const int& i = idx[ii];
		int uf = dsu.find(e[i].u), vf = dsu.find(e[i].v);
		if (uf == vf) { vec[++vecpsz] = i; continue; }
		g[e[i].u].push_back({e[i].v, e[i].w});
		g[e[i].v].push_back({e[i].u, e[i].w});
		dsu.fa[uf] = vf, res += e[i].w;
	} return res;
}
struct Data {
	int ma1, ma2;
	Data() { ma1 = ma2 = -inf; }
	Data(int ma1, int ma2) { this->ma1 = ma1, this->ma2 = ma2; }
};
Data operator+ (const Data& a, const Data& b) {
	Data c; int ar[4] = {a.ma1, a.ma2, b.ma1, b.ma2};
	stable_sort(ar, ar + 4, greater<int>());
	c.ma1 = ar[0];
	for (int i : {1, 2, 3})
		if (ar[i] != c.ma1) { c.ma2 = ar[i]; break; }
	return c;
}
int fa[N + 10][LGN + 2], dep[N + 10];
Data val[N + 10][LGN + 2];
void dfs(int u, int p, int upw) {
	dep[u] = dep[p] + 1, fa[u][0] = p, val[u][0] = {upw, -inf};
	for (int k = 1; k <= lgn; k++) {
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
		val[u][k] = val[u][k - 1] + val[fa[u][k - 1]][k - 1];
	}
	for (const auto& [v, w] : g[u]) if (v != p) dfs(v, u, w);
}
Data query(int u, int v) {
	Data res;
	if (dep[u] < dep[v]) swap(u, v);
	int d = dep[u] - dep[v];
	for (int i = lgn; ~i; i--) if (d >> i & 1)
		res = res + val[u][i], u = fa[u][i];
	if (u == v) return res;
	for (int i = lgn; ~i; i--) if (fa[u][i] != fa[v][i]) {
		res = res + val[u][i] + val[v][i];
		u = fa[u][i], v = fa[v][i];
	} return res + val[u][0] + val[v][0];
}
int main() {
	rd(n, m), lgn = __lg(n) + 1;
	for (int i = 1; i <= m; i++)
		rd(e[i].u, e[i].v, e[i].w);
	intl sum = kruskal(), ans = numeric_limits<intl>::max();
	dfs(1, 0, 0);
	for (int ii = 1; ii <= vecpsz; ii++) {
		const int& i = vec[ii];
		Data res = query(e[i].u, e[i].v);
		chkmin(ans, sum + e[i].w - (e[i].w == res.ma1 ? res.ma2 : res.ma1));
	}
	wtln(ans);
	return 0;
}
