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
const int N = 400, inf = 0x3f3f3f3f;
int n, x, y, a[N + 10], b[N + 10];
bool dp(int m) {
	set<int> f; f.insert(x);
	for (int i = 1; i <= m; i++) {
		vector<int> vec;
		for (auto u = f.lower_bound(b[i]); u != f.end(); u++) vec.push_back(*u % b[i]);
		for (int u : vec) f.insert(u);
	}
	return f.count(y);
}
void slove() {
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int Lx, Rx = n + 1;
	for (int i = 1, mi = inf; i <= n; i++) {
		chkmin(mi, a[i]);
		if (mi <= y) { Rx = i; break; }
	}
	int l = 1, r = Rx;
	while (l < r) {
		int mid = (l + r) >> 1;
		for (int i = 1; i <= mid; i++) b[i] = a[i];
		sort(b + 1, b + mid + 1, greater<int>());
		if (dp(mid)) r = mid;
		else l = mid + 1;
	} Lx = l;
	cout << Rx - Lx << "\n";
	for (int i = Lx; i < Rx; i++) cout << i << " ";
	cout << '\n';
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
