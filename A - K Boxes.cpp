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
intl n, k, a[N + 10], b[N + 10], ans[N + 10];
void slove() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	vector<int> idx(n); iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; } );
	priority_queue<int, vector<int>, greater<int> > que;
	intl sum = 0;
	for (int i : idx) {
		ans[i] = sum;
		if ((int) que.size() < k) {
			sum += b[i], que.push(b[i]);
		} else if (que.top() < b[i]) {
			sum += b[i] - que.top(); que.pop(), que.push(b[i]);
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}
int main() { ffopen();
	int T; cin >> T;
	while (T--) { slove(); }
	return 0;
}
