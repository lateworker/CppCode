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
const int N = 200000;
int n, a[N + 10], b[N + 10];
bitset<N + 10> f;
void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	if (a[1] != b[1] || a[n] != b[n]) { cout << "No\n"; return; }
	for (int i = 1; i < n; i++) {
		if (a[i] && !b[i]) {
			if (a[i - 1] || a[i + 1]) { cout << "No\n"; return; }
			else a[i] = 0;
		}
		if (!b[i]) f[i] = false;
		else f[i] = f[i - 1] || a[i];
	}
	bool g = false;
	for (int i = n; i > 1; i--) {
		if (!b[i]) g = false;
		else g = g || a[i];
		if (!a[i] && b[i]) {
			if (!f[i] && !g) { cout << "No\n"; return; }
		}
	}
	cout << "Yes\n";
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) { slove(); }
	return 0;
}
