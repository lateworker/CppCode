#include <bits/stdc++.h>
template<class T_, size_t N_>
class Graph {
	inline static size_t psz;
	inline static std::pair<T_, size_t> pool[N_];
	struct iterator {
		size_t now;
		T_& operator* () const { return pool[now].first; }
		bool operator== (iterator it) const { return now == it.now; }
		iterator& operator++ () { now = pool[now].second; return *this; }
	}; size_t head;
public:
	Graph() { head = 0; }
	iterator begin() const { return {head}; }
	iterator end() const { return {0}; }
	void push_back(const T_& val) { ++psz, this->pool[psz] = {val, head}, head = psz; }
};
using namespace std;
const int N = 100000;
int n, siz[N + 10], vfa[N + 10];
Graph < int, N * 2 + 10 > g[N + 10];
bitset<N + 10> del;
void gsiz(int u, int p) {
	if (siz[u] = 0, del[u]) return;
	siz[u] = 1; for (int v : g[u]) if (v != p) gsiz(v, u), siz[u] += siz[v];
}
int gcet(int u, int p, const int& r) {
	if (del[u]) return 0;
	for (int v : g[u]) if (v != p && siz[v] << 1 > r) return gcet(v, u, r);
	return u;
}
void solve(int u, int p) {
	if (del[u]) return;
	gsiz(u, 0); int cet = gcet(u, 0, siz[u]);
	vfa[cet] = p, del[cet] = true;
	for (int v : g[cet]) solve(v, cet);
}
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	} solve(1, -1);
	for (int i = 1; i <= n; i++) cout << vfa[i] << " \n"[i == n];
	return 0;
}
