#include <bits/stdc++.h>
using namespace std;
const int N = 500000;
struct Segt {
	struct ODT {
		mutable int lx, rx;
		auto operator <=> (const ODT& o) const { return make_pair(lx, rx) <=> make_pair(o.lx, o.rx); }
	};
	set<ODT> odt; int ans;
} st[N * 4 + 10];
#define le (u << 1)
#define ri (u << 1 | 1)
#define mid(l, r) auto mid = (((l) + (r)) / 2)
Segt operator + (Segt a, Segt b) {
	Segt c; if (a.odt.size() < b.odt.size()) swap(a, b);
	
}
void pushup(int u) {
	
}
void build(int u, int l, int r) {
	if (l == r) {
		int x; cin >> x;
		st[u].odt.insert({x - l + 1, x});
		st[u].ans = l;
		return;
	} mid(l, r);
	build(le, l, mid);
	build(ri, mid + 1, r);
	pushup(u);
}
int n, m;
int main() { cin.tie(0)->sync_with_stdio(0);
	return 0;
}

/*
a[i] --> [ max(a[i] - i + 1, 0), a[i] ];
6 5 7 6
(([6, 6], [4, 5], [5, 7], [3, 6])+, [0, 5])* = ([3, 7], [0, 5])* = [3, 5]
8 7 9 6
(([8, 8], [6, 7], [7, 9], [3, 6])+, [0, 6])* = ([3, 9], [0, 6])* = [3, 6]
8 7 9 11
(([8, 8], [6, 7], [7, 9], [8, 11])+, [0, 7])* = ([6, 11], [0, 7])* = [6, 7]
*/
