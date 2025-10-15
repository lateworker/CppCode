#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define MultiCase(Callback) { Callback; int CaseId = 1; cin >> CaseId; CaseLoop:
#define Return if (--CaseId) { goto CaseLoop; } else { return 0; }
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
template<typename T_, size_t N_, T_ DEFAULT_ = T_()> class Array { T_ val[N_]; size_t ver[N_], clk; public: Array() { clk = 1; } T_& operator[] (size_t i) { if (ver[i] != clk) {ver[i] = clk, val[i] = DEFAULT_;} return val[i]; } void clear() { ++clk; } };
template<typename T_, size_t N_> class Graph { inline static size_t psz; inline static std::pair<T_, size_t> pool[N_]; struct iterator { size_t now; T_& operator* () const { return pool[now].first; } bool operator== (iterator it) const { return now == it.now; } iterator& operator++ () { now = pool[now].second; return *this; } }; size_t head; public: Graph() { head = 0; } iterator begin() const { return {head}; } iterator end() const { return {0}; } void push_back(const T_& val) { ++psz, this->pool[psz] = {val, head}, head = psz; } void clear() { psz = head = 0; } };
using namespace std;
using intl = long long;
const int N = 100;
int n, m, a[N + 10][N + 10];
map<int, int> c;
int calc(int x, int y) {
	c.clear();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			++c[a[i][j] - (i - 1) * x - (j - 1) * y];
	int ans = 0;
	for (const auto& [p, cnt] : c) chkmax(ans, cnt);
	return ans;
}
int main() MultiCase(ffopen()) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) cin >> a[i][j];
	cout << n * m - max({calc(+1, +1), calc(+1, -1), calc(-1, +1), calc(-1, -1)}) << '\n';
} Return }
