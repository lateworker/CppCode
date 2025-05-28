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
int n;
Graph < int, N * 2 + 10 > g[N + 10];
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	return 0;
}
