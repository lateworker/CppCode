#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
const int N = 100000;
struct BIT {
	BIT *le, *ri, *fa;
	int val, dep;
	BIT() { le = ri = this, val = dep = 0; }
} pool[N + 10]; int psz;
BIT* node() {
	BIT* u = pool + ++psz;
	u->le = u->ri = pool;
	return u;
}
void repl(BIT* u, BIT* v) {
	(u == u->fa->le ? u->fa->le : u->fa->ri) = v;
	v->fa = u->fa;
}
BIT* glca(BIT* u, BIT* v) {
	if (u->dep < v->dep) swap(u, v);
	while (u->dep > v->dep) u = u->fa;
	while (u != v) u = u->fa, v = v->fa;
	return u;
}
void make(BIT* u, BIT* v) {
	BIT* p = glca(u, v);
	vector<BIT*> st;
	while (u != p) {
		if (u == u->fa->ri) {
			st.push_back(u->fa->le);
			repl(u->fa, u);
		} else u = u->fa;
	}
	 
}
int main() {
	
	return 0;
}
