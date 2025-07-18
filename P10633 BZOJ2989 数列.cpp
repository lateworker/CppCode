#include <bits/stdc++.h>
namespace std {
	template<class T_, size_t N_, T_ DEFAULT = T_()>
	class Array {
		T_ val[N_]; size_t ver[N_], clk;
	public:
		Array() { clk = 1; }
		T_& operator[] (size_t i) { if (ver[i] != clk) ver[i] = clk, val[i] = DEFAULT; return val[i]; }
		void clear() { ++clk; }
	};
}
using namespace std;
const int N = 60000, Q = 110000, M = 160000;
int n, m, q, a[N + 10], ans[N + Q + 10];
tuple<int, int, int> evt[N + Q + 10];

struct Tnum {
	Array<int, M + 10> st;
	int ofs;
	void modify(int u, int val) { for (u += ofs; u <= M; u += u & -u) st[u] += val; }
	int query(int u) { int res = 0; for (u += ofs; u; u -= u & -u) res += st[u]; return res; }
	void clear() { st.clear(); }
} t1, t2;

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid), cdq(mid + 1, r);
	
	vector<int> idx(r - l + 1);
	iota(idx.begin(), idx.end(), l);
	
	stable_sort(idx.begin(), idx.end(), [](int i, int j) {
		int pi = get<0>(evt[i]), pj = get<0>(evt[j]);
		return pi == pj ? get<2>(evt[i]) < get<2>(evt[j]) : pi < pj;
	} );
	t1.clear(), t2.clear();
	t1.ofs = n + 3, t2.ofs = n + m + 3;
	for (auto u = idx.begin(); u != idx.end(); u++) {
		int i = *u; auto [pos, val, k] = evt[i];
		if (k && pos > mid) {
			ans[i] += t1.query(k - pos + val);
			ans[i] += t2.query(k - pos - val);
		}
		if (!k && pos <= mid) {
			t1.modify(- pos + val, 1);
			t2.modify(- pos - val, 1);
		}
	}
	
	t1.clear(), t2.clear();
	t1.ofs = 3, t2.ofs = m + 3;
	for (auto u = idx.rbegin(); u != idx.rend(); u++) {
		int i = *u; auto [pos, val, k] = evt[i];
		if (k && pos > mid) {
			ans[i] += t1.query(k + pos + val);
			ans[i] += t2.query(k + pos - val);
		}
		if (!k && pos <= mid) {
			t1.modify(pos + val, 1);
			t2.modify(pos - val, 1);
		}
	}
}
int main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		evt[i] = {i, a[i], 0};
		m = max(m, a[i]);
	}
	for (int i = 1; i <= q; i++) {
		string op; int x, k;
		cin >> op >> x >> k;
		m = max(m, k);
		if (op[0] == 'M') {
			evt[n + i] = {x, a[x] = k, 0};
		} else
		if (op[0] == 'Q') {
			evt[n + i] = {x, a[x], k};
		}
	}
	cdq(1, n + q);
	for (int i = 1; i <= q; i++)
		if (get<2>(evt[n + i])) cout << ans[n + i] << "\n";
	return 0;
}
