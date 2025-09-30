#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define int long long
#define chkmax(x, y) ((x)=max((x),(y)))
#define chkmin(x, y) ((x)=min((x),(y)))
template<typename T_, size_t N_, T_ DEFAULT_ = T_()> class Array { T_ val[N_]; size_t ver[N_], clk; public: Array() { clk=1; } T_& operator[] (size_t i) { if(ver[i]!=clk){ver[i]=clk,val[i]=DEFAULT_;} return val[i]; } void clear() { ++clk; } };
template<typename T_, size_t N_> class Graph { inline static size_t psz; inline static std::pair<T_, size_t> pool[N_]; struct iterator { size_t now; T_& operator* () const { return pool[now].first; } bool operator== (iterator it) const { return now == it.now; } iterator& operator++ () { now=pool[now].second; return *this; } }; size_t head; public: Graph() { head = 0; } iterator begin() const { return {head}; } iterator end() const { return {0}; } void push_back(const T_& val) { ++psz,this->pool[psz]={val, head},head=psz; } void clear() { psz=head=0; } };
using namespace std;
using intl = long long;
const int N = 200000;
int n, q, a[N + 10], mac[N + 10], mic[N + 10];
Array<int, N + 10> st;
void modify(int u, int val) { for (; u <= n; u += u & -u) st[u] += val; }
int query(int u) { int res = 0; for (; u; u -= u & -u) res += st[u]; return res; }
void slove() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	vector<int> idx(n); iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] > a[j]; } );
	mac[n + 1] = 0, st.clear();
	for (int i : idx) {
		mac[a[i]] = mac[a[i] + 1] + query(i);
		modify(i, 1);
	}
	sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; } );
	mic[0] = 0, st.clear();
	for (int i : idx) {
		mic[a[i]] = mic[a[i] - 1] + query(n - i + 1);
		modify(n - i + 1, 1);
	}
//	for (int i = 1; i <= n; i++) cout << mac[i] << " \n"[i == n];
//	for (int i = 1; i <= n; i++) cout << mic[i] << " \n"[i == n];
	for (int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r;
		cout << (l == r ? 0 : mac[1] - mac[r] - mic[l]) << "\n";
	}
}
signed main() { ffopen();
	int T; cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
