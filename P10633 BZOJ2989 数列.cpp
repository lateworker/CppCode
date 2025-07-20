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
const int N = 60000, Q = 60000, M = 400000, inf = 0x3f3f3f3f;
int n, q, a[N + 10], ans[Q + 10];
vector<tuple<int, int, int, int> > evt;

struct Tnum {
	Array<int, M + 10> st;
	int ofs;
	void modify(int u, int val) { for (u += ofs; u <= M; u += u & -u) st[u] += val; }
	int query(int u) { int res = 0; for (u += ofs; u; u -= u & -u) res += st[u]; return res; }
	void clear() { st.clear(); }
} st;

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid), cdq(mid + 1, r);
	
	vector<int> idx(r - l + 1);
	iota(idx.begin(), idx.end(), l);
	
	stable_sort(idx.begin(), idx.end(), [](int i, int j) {
		int xi = get<0>(evt[i]), xj = get<0>(evt[j]);
		return xi < xj;
	} );
	
	st.clear();
	for (int i : idx) {
		auto [x, y, yy, qid] = evt[i];
		if (i <= mid && !qid) {
			st.modify(y, 1);
		}
		if (i > mid && qid) {
			int op = qid > 0 ? 1 : -1; qid = abs(qid);
			ans[qid] += op * (st.query(yy) - st.query(y - 1));
		}
	}
}
int main() {
	cin >> n >> q;
	int miny = inf;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		int x = i + a[i], y = i - a[i];
		miny = min(miny, y);
		evt.emplace_back(x, y, y, 0);
	}
	int pszq = 0;
	for (int i = 1; i <= q; i++) {
		string op; int pos, val;
		cin >> op >> pos >> val;
		if (op[0] == 'M') {
			a[pos] = val;
			int x = pos + val, y = pos - val;
			miny = min(miny, y);
			evt.emplace_back(x, y, y, 0);
		} else
		if (op[0] == 'Q') {
			int x = pos + a[pos], y = pos - a[pos];
			miny = min(miny, y - val);
			evt.emplace_back(x + val, y - val, y + val, ++pszq);
			evt.emplace_back(x - val - 1, y - val, y + val, -pszq);
		}
	}
	st.ofs = -miny + 3;
	cdq(0, evt.size() - 1);
	for (int i = 1; i <= pszq; i++) cout << ans[i] << "\n";
	return 0;
}
