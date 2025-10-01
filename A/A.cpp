#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
template<typename T_, size_t N_, T_ DEFAULT_ = T_()> class Array { T_ val[N_]; size_t ver[N_], clk; public: Array() { clk=1; } T_& operator[] (size_t i) { if(ver[i]!=clk){ver[i]=clk,val[i]=DEFAULT_;} return val[i]; } void clear() { ++clk; } };
template<typename T_, size_t N_> class Graph { inline static size_t psz; inline static std::pair<T_, size_t> pool[N_]; struct iterator { size_t now; T_& operator* () const { return pool[now].first; } bool operator== (iterator it) const { return now == it.now; } iterator& operator++ () { now=pool[now].second; return *this; } }; size_t head; public: Graph() { head = 0; } iterator begin() const { return {head}; } iterator end() const { return {0}; } void push_back(const T_& val) { ++psz,this->pool[psz]={val, head},head=psz; } void clear() { psz=head=0; } };
using namespace std;
using intl = long long;
const intl N = 1000, M = 200, K = M, Mod = 1000000007;
intl n, m, k, f[N + 10][M + 10], pf[N + 10][M + 10], g[N + 10][M + 10];
char s[N + 10], t[M + 10];
inline intl getpf(int i, int j) {
	if (i < 0 || j < 0) return 0;
	return pf[i][j] % Mod;
}
int main() { ffopen();
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> s[i];
	for (int i = 1; i <= m; i++) cin >> t[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			if (s[i] == t[j]) g[i][j] = g[i - 1][j - 1] + 1;
	}
	for (int i = 0; i <= n; i++) f[i][0] = 1;
	for (int kk = 1; kk <= k; kk++) {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				pf[i][j] = getpf(i - 1, j - 1) + f[i][j];
				pf[i][j] %= Mod, f[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m && j <= i; j++) {
				f[i][j] = f[i - 1][j] % Mod;
				if (s[i] != t[j]) continue;
				int len = g[i][j];
				f[i][j] += (getpf(i - 1, j - 1) - getpf(i - len - 1, j - len - 1) + Mod) % Mod;
				f[i][j] %= Mod;
			}
		}
	}
	cout << f[n][m] % Mod << "\n";
	return 0;
}
