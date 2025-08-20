#include <bits/stdc++.h>
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
using namespace std;
const int SIZE = 1 << 20; char buf[SIZE], *p1, *p2;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++)
template<typename T> inline T& rd(T &x) {
	x = 0; int f = 1; char c = gc();
	for (; !isdigit(c); c = gc())if (c == '-')f = -1;
	for (; isdigit(c); c = gc())x = x * 10 + (c ^ 48);
	return x *= f;
}
using intl = long long;
const int N = 100000, A = 500000, RTA = int(sqrt(A)) + 1;
int n, m, a[N + 10], cnt[A + 10], psz[A + 10], c[N + 10], maxa;
int idx[N * RTA + 10], fa[N * RTA + 10], tn[A + 10], t[N + 10][RTA + 10];
inline void node(const int& r, const int& i) { idx[psz[r]] = i, fa[psz[r]] = psz[r], ++psz[r]; }
inline int find(const int& r, const int& u) { return u == tn[r + 1] || u == fa[u] ? u : fa[u] = find(r, fa[u]); }
inline void del(const int& u) { fa[u] = u + 1; }
intl b[N + 10];
inline void tnumUpdate(int u, const intl& val) { for (; u <= n; u += u & -u) b[u] += val; }
inline intl tnumQuery(int u) { intl res = 0; for (; u; u -= u & -u) res += b[u]; return res; }
int main() {
	rd(n), rd(m);
	for (int i = 1; i <= n; ++i) {
		rd(a[i]);
		tnumUpdate(i, a[i]);
		++cnt[a[i]];
		chkmax(maxa, a[i]);
	}
	for (int i = 1; i <= maxa; ++i) cnt[i] += cnt[i - 1], psz[i] = cnt[i - 1];
	for (int i = 1; i <= n; ++i) c[++psz[a[i]]] = i;
	psz[2] = tn[2] = 1;
	for (int x = 2; x <= maxa; ++x) {
		for (int y = x; y <= maxa; y += x) tn[x + 1] += cnt[y] - cnt[y - 1];
		psz[x + 1] = (tn[x + 1] += tn[x]);
	}
	static int vec[N + 10];
	for (int x = 2; x <= maxa; ++x) {
		int vec0 = 0;
		for (int y = x; y <= maxa; y += x)
			for (int i = cnt[y - 1] + 1; i <= cnt[y]; ++i) vec[++vec0] = c[i];
		stable_sort(vec + 1, vec + vec0 + 1);
		for (int i = 1; i <= vec0; ++i) node(x, vec[i]);
	}
	intl last = 0;
	for (int i = 1; i <= m; ++i) {
		intl op, l, r;
		rd(op), rd(l), rd(r);
		l ^= last, r ^= last;
		if (op == 1) {
			intl x; rd(x); x ^= last;
			if (x == 1 || tn[x] == tn[x + 1]) continue;
			int p = lower_bound(idx + tn[x], idx + tn[x + 1], l) - idx;
			for (p = find(x, p); p < tn[x + 1] && idx[p] <= r; p = find(x, p + 1)) {
				int j = idx[p];
				if (a[j] % x) del(p);
				else tnumUpdate(j, - a[j] + a[j] / x), a[j] /= x;
			}
		} else printf("%lld\n", last = tnumQuery(r) - tnumQuery(l - 1));
	}
	return 0;
}
