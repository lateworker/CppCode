#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
using namespace std;
const int N = 100000, inf = 0x3f3f3f3f;
struct Val {
	int fmax, fmin, bmax, bmin, sum, len;
	Val() {
		fmax = bmax = -inf;
		fmin = bmin = inf;
		sum = len = 0;
	}
	Val(int val) { fmax = fmin = bmax = bmin = sum = val, len = 1; }
};
struct Tag { bool inv, rev, cov, sig; } tag0 = {0, 0, 0, 0};
bool operator== (const Tag& a, const Tag& b) { return a.inv == b.inv && a.rev == b.rev && a.cov == b.cov && a.sig == b.sig; }
Val merge(const Val& x, const Val& y) {
	Val z;
	z.sum = x.sum + y.sum;
	z.fmax = max(x.fmax, x.sum + y.fmax);
	z.fmin = min(x.fmin, x.sum + y.fmin);
	z.bmax = max(x.bmax + y.sum, y.bmax);
	z.bmin = min(x.bmin + y.sum, y.bmin);
	z.len = x.len + y.len;
	return z;
}
bool xorbool(const bool& x, const bool& y) { return (x && !y) || (!x && y); }
void apply(Tag& x, const Tag& y) { x = y.cov ? y : Tag{ xorbool(x.inv, y.inv), xorbool(x.rev, y.rev), x.cov, x.sig }; }
void apply(Val& x, const Tag& y) {
	if (y.cov) {
		if (y.sig) {
			x.sum = -x.len;
			x.fmax = x.bmax = -1;
			x.fmin = x.bmin = -x.len;
		} else {
			x.sum = x.len;
			x.fmax = x.bmax = x.len;
			x.fmin = x.bmin = 1;
		}
	}
	if (y.inv) {
		swap(x.fmax, x.fmin);
		swap(x.bmax, x.bmin);
		x.fmax = -x.fmax, x.fmin = -x.fmin;
		x.bmax = -x.bmax, x.bmin = -x.bmin;
		x.sum = -x.sum;
	}
	if (y.rev) {
		swap(x.fmax, x.bmax);
		swap(x.fmin, x.bmin);
	}
}
struct Treap {
	int le, ri, pi;
	Val val, sum; Tag tag;
} st[N + 10]; int psz;
int node(Val val) {
	st[++psz] = {0, 0, rand(), val, val, tag0};
	return psz;
}
void pushup(int u) { st[u].sum = merge(merge(st[st[u].le].sum, st[u].val), st[st[u].ri].sum); }
void modify(int u, const Tag& tag) {
	apply(st[u].tag, tag), apply(st[u].val, tag), apply(st[u].sum, tag);
	if (tag.rev) swap(st[u].le, st[u].ri);
}
void pushdown(int u) {
	if (st[u].tag != tag0) {
		modify(st[u].le, st[u].tag);
		modify(st[u].ri, st[u].tag);
		st[u].tag = tag0;
	}
}
void split(int u, int s, int& lf, int& rt) {
	if (u == 0) { lf = rt = 0; return; }
	pushdown(u);
	if (st[st[u].le].sum.len >= s) split(st[u].le, s, lf, st[u].le), rt = u;
	else split(st[u].ri, s - st[st[u].le].sum.len - 1, st[u].ri, rt), lf = u;
	pushup(u);
}
int merge(int u, int v) {
	if (!u || !v) return u | v;
	if (st[u].pi > st[v].pi) {
		pushdown(u);
		st[u].ri = merge(st[u].ri, v);
		pushup(u); return u;
	} else {
		pushdown(v);
		st[v].le = merge(u, st[v].le);
		pushup(v); return v;
	}
}
ostream& operator<< (ostream& cout, const Val& a) {
	cout << a.fmax << " " << a.fmin << " front\n";
	cout << a.bmax << " " << a.bmin << " back\n";
	cout << a.len << " len " << a.sum << " sum\n";
	return cout;
}
ostream& operator<< (ostream& cout, const Tag& a) {
	cout << a.cov << " " << a.inv << " " << a.rev << " " << a.sig << "\n";
	return cout;
}
void dfs(int u) {
	if (!u) return;
	cout << u << " " << st[u].le << " " << st[u].ri << " NodeID\n";
	cout << st[u].val << "(val)\n" << st[u].sum << "(sum)\n" << st[u].tag << "(tag)\n";
	pushdown(u);
	dfs(st[u].le);
	dfs(st[u].ri);
}
int n, m, root;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		root = merge(root, node(Val(c == '(' ? 1 : -1)));
	}
//	dfs(root);.
	for (int i = 1; i <= m; i++) {
		string op; int a, b;
		cin >> op >> a >> b;
		int lf, tar, rt;
		split(root, b, lf, rt);
		split(lf, a - 1, lf, tar);
		if (op[0] == 'R') {
			char c; cin >> c;
			modify(tar, {0, 0, true, c == ')'});
		}
		if (op[0] == 'S') {
			modify(tar, {true, 0, 0, 0});
		}
		if (op[0] == 'I') {
			modify(tar, {0, true, 0, 0});
		}
		if (op[0] == 'Q') {
//			dfs(lf), puts("LF");
//			dfs(tar), puts("TAR");
//			dfs(rt), puts("RT");
			int x = st[tar].sum.fmin, y = st[tar].sum.sum, ans = 0, d;
			if (x < 0) d = ((1 - x) >> 1), ans += d, y += d << 1;
			ans += y >> 1;
			cout << ans << "\n";
		}
		root = merge(merge(lf, tar), rt);
	}
	return 0;
}
