#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
const int SIZE = 1 << 20; char buf[SIZE], *p1, *p2;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++)
template<typename T> inline void rd(T& x) {
	x = 0; int f = 1; char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -1;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
template<typename T, typename... Args> inline void rd(T& x, Args&... y) { rd(x), rd(y...); }
using intl = long long;
const intl M = 200000, inf = 0x3f3f3f3f3f3f3f3f;
int n, m, k;
struct Pair { int l, r, v; bool operator< (const Pair& b) const { return r < b.r; } } qry[M + 10];
intl st[M * 2 + 10], tg[M * 2 + 10], d;
void pushup(int u) { if (u) st[u] = max(st[u << 1], st[u << 1 | 1]); }
void modify(int u, intl val) { st[u] += val, tg[u] += val; }
void pushdown(int u) { if (tg[u]) modify(u << 1, tg[u]), modify(u << 1 | 1, tg[u]), tg[u] = 0; }
void updateAdd(int l, int r, intl val) {
	l += n, r += n + 1;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
		if (l & 1) u = l, modify(l++, val);
		if (r & 1) v = r, modify(--r, val);
		do pushup(u >>= 1); while (l == r && u);
		do pushup(v >>= 1); while (l == r && v);
	}
}
void modifyMax(int u, intl val) {
	u += n;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(u >> i), chkmax(st[u >> i], val);
	chkmax(st[u], val);
}
intl queryMax(int l, int r) {
	l += n, r += n + 1;
	for (int i = __lg(n + 1) + 1; i; i--) pushdown(l >> i), pushdown(r >> i);
	intl res = -inf;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) chkmax(res, st[l++]);
		if (r & 1) chkmax(res, st[--r]);
	} return res;
}
int vec[M * 2 + 10], vecpsz;
inline int lower(const int& x) { return lower_bound(vec, vec + n, x) - vec; }
inline void slove() {
	rd(n, m, k, d);
	for (int i = 1; i <= m; i++) {
		int x, y, z; rd(x, y, z);
		if (y > k) continue;
		qry[i] = {x - y, x, z};
		vec[vecpsz++] = qry[i].l, vec[vecpsz++] = qry[i].r;
	}
	sort(qry + 1, qry + m + 1);

	sort(vec, vec + vecpsz);
	n = unique(vec, vec + vecpsz) - vec;

	fill_n(st, n << 1, -inf);
	fill_n(tg, n << 1, 0);
	modifyMax(0, 0);

	intl f = 0; int ptr = 1, pos = 0;
	for (int ii = 1; ii < n; ii++) {
		const int& i = vec[ii];
		modifyMax(ii, f + d * i);
		for (; ptr <= m && qry[ptr].r == i; ++ptr) updateAdd(0, lower(qry[ptr].l), qry[ptr].v);
		while (vec[pos] < i - k) ++pos;
		chkmax(f, queryMax(pos, ii - 1) - d * i);
	}
	printf("%lld\n", f);
}
int main() {
	int C, T; rd(C, T);
	while (T--) {
		vecpsz = 1;
		slove();
	}
	return 0;
}
