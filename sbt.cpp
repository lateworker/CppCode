#include <bits/stdc++.h>
using namespace std;
template<class T_>
class Frac {
public:
	T_ lp, lq, rp, rq;
	inline void maintain() { p = lp + rp, q = lq + rq; }
	T_ p, q;
	Frac() { lp = rq = 0, lq = rp = 1; maintain(); }
	Frac(const T_& lp, const T_& lq, const T_& rp, const T_& rq) {
		this->lp = lp, this->lq = lq, this->rp = rp, this->rq = rq;
		maintain();
	}
};
template<class T_>
ostream& operator<< (ostream& cout, Frac<T_>& a) {
	cout << a.p << '/' << a.q; return cout;
}
int main() {
	Frac<long long> u;
	string s; cin >> s;
	int cnt = 0;
	for (char c : s) {
		++cnt;
		if (c == '0') u = Frac(u.lp, u.lq, u.p, u.q);
		else u = Frac(u.p, u.q, u.rp, u.rq);
	}
	cout << cnt << " " << u << "\n";
	return 0;
}
