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
const intl N = 100000;
intl n, w, a[N + 10];
namespace TaskWeq0 {
	bool isTaskWeq0() { return w == 0; }
	int b[N + 10], pb;
	int main() {
		sort(a + 1, a + 1 + n);
		cout << a[n] << ' ';
		for (int i = 1, j = n; i <= j; i++, j--) {
			b[++pb] = a[j];
			if (i != j) b[++pb] = a[i];
		}
		intl ans2 = b[1];
		for (int i = 2; i <= n; i++) {
			ans2 += max(abs(b[i] - b[i - 1]), b[i]);
		}
		cout << ans2 << '\n';
		return 0;
	}
}
int main() { ffopen();
	cin >> n >> w;
	for (int i = 1; i <= n; i++) cin >> a[i];
	if (TaskWeq0::isTaskWeq0()) return TaskWeq0::main();
	return 0;
}
