#include <bits/stdc++.h>
using namespace std;
vector<int> sa, rk, ht;
int gSA(const string &s, int n) {
	int m = 256; vector<int> _sa(n * 2 + 1), _rk(n * 2 + 1);
	sa.resize(n * 2 + 1, 0), rk.resize(n * 2 + 1, 0), ht.resize(n + 1, 0);
	auto ctsort = [&]() { vector<int> cnt(m + 1);
		for (int i = 1; i <= n; i++) cnt[rk[i]]++;
		for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--) sa[cnt[rk[_sa[i]]]--] = _sa[i];
	}; for (int i = 1; i <= n; i++) { rk[i] = s[i], _sa[i] = i; } ctsort();
	for (int w = 1, p; p = 0, 1; w <<= 1, m = p) {
		for (int i = n - w + 1; i <= n; i++) _sa[++p] = i;
		for (int i = 1; i <= n; i++) if (sa[i] > w) _sa[++p] = sa[i] - w;
		ctsort(); _rk.swap(rk), p = 0;
		for (int i = 1; i <= n; i++)
			rk[sa[i]] = (_rk[sa[i]] == _rk[sa[i - 1]] && _rk[sa[i] + w] == _rk[sa[i - 1] + w]) ? p : ++p;
		if (p == n) break;
	} for (int i = 1, k = 0; i <= n; i++)
		if (rk[i]) { for (k -= (k > 0); s[i + k] == s[sa[rk[i] - 1] + k]; k++); ht[rk[i]] = k; }
	sa.resize(n + 1), rk.resize(n + 1); return n;
}
int main() {
	string s; cin >> s;
	int n = gSA("#" + s, s.size());
	for (int i = 1; i <= n; i++) cout << sa[i] << " \n"[i == n];
	return 0;
}
