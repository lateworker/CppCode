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
int n, m;
char s[N + 10], t[N + 10];
vector<int> check() {
	vector<int> vec;
	for (int i = 1, j = 1; i <= n; i++) {
		if (t[i] == t[i - 1]) { ++j; } else j = 1;
		if (j >= m) {
			vec.push_back(i);
			j = 1;
		}
	} return vec;
}
bool calc() {
	for (int i = 1; i <= n; i++) t[i] = s[i];
	vector<int> vec = check();
	if (vec.empty()) return true;
	if (vec.size() > 2) return false;
	if (vec.size() == 2) {
		reverse(t + vec[0], t + vec[1]);
		return check().empty();
	}
	int p = vec[0], q = n, len = 0;
	for (int i = p; i <= n; i++) {
		if (t[i] == t[p]) { ++len; } else break;
	}
	for (int i = n, j = 0; i >= p; i--) {
		if (t[i] == t[p]) ++j;
		else {
			if (j + len < m) { q = i; break; }
			j = 0;
		}
	}
	reverse(t + p, t + q + 1);
	return check().empty();
}
int Main(ffopen(); MultiCase; ) {
	cin >> n >> m; s[n + 1] = '\0';
	for (int i = 1; i <= n; i++) cin >> s[i];
	if (calc()) { cout << "Yes\n"; Return; }
	reverse(s + 1, s + 1 + n);
	if (calc()) { cout << "Yes\n"; Return; }
	cout << "No\n";
} Return; }
