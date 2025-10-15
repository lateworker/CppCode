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
const intl N = 5000, M = N, Mod = 998244353;
intl n, m, f[M + 10], g[M + 10], a[N + 10];
int Main(ffopen(); MultiCase; ) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	memset(f, 0, (m + 5) * sizeof(intl)), g[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) g[j] = (g[j - 1] + f[j]) % Mod;
		if (a[i] == -1) {
			for (int j = 1; j <= m; j++) {
				f[j] = (f[j] * m % Mod + g[j - 1]) % Mod;
			}
			(g[0] *= m) %= Mod;
		} else {
			f[a[i]] += g[a[i] - 1], f[a[i]] %= Mod;
		}
	}
	intl ans = 0;
	for (int j = 1; j <= m; j++) {
		ans += f[j], ans %= Mod;
	}
	cout << ans % Mod << '\n';
} Return; }
