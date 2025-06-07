#include <bits/stdc++.h>
template<class T_, size_t N_, T_ DEFAULT = T_()>
class Array {
	T_ val[N_]; size_t ver[N_], clk;
public:
	Array() { clk = 1; }
	T_& operator[] (size_t i) { if (ver[i] != clk) ver[i] = clk, val[i] = DEFAULT; return val[i]; }
	void clear() { ++clk; }
};
template<class T_, size_t N_>
class Graph {
	inline static size_t psz;
	inline static std::pair<T_, size_t> pool[N_];
	size_t head;
public:
	struct iterator {
		size_t now;
		T_& operator* () const { return pool[now].first; }
		bool operator== (const iterator& it) const { return now == it.now; }
		iterator& operator++ () { now = pool[now].second; return *this; }
		iterator operator++ (int) { now = pool[now].second; return *this; }
		iterator operator~ () const { return {now ^ 1}; }
		T_* operator-> () { return &(pool[now].first); }
	};
	Graph() { head = size_t(-1); }
	iterator begin() const { return {head}; }
	iterator end() const { return {size_t(-1)}; }
	void push_back(const T_& val) { this->pool[psz] = {val, head}, head = psz++; }
};
using intl = long long;
using namespace std;
const intl N = 2000, M = N * N * 6, infl = 0x3f3f3f3f3f3f3f3f;
intl n, m, a[N * N + 10];
struct E { int v; intl r, w; };
Graph<E, M + 10> g[N * N + 10];
void edge(int u, int v, intl r, intl w) { g[u].push_back({v, r, w}), g[v].push_back({u, 0, -w}); }
Array<intl, N * N + 10, infl> dis;
Array<bool, N * N + 10, false> vis, inq;
bool SPFA(const int& t, int s) {
	queue<int> que; inq.clear(), dis.clear();
	dis[s] = 0, inq[s] = true, que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		inq[u] = false;
		for (auto [v, r, w] : g[u])
			if (r && dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				if (!inq[v]) inq[v] = true, que.push(v);
			}
	} return dis[t] < 0;
}
Graph<E, M + 10>::iterator cur[N * N + 10];
intl dfs(const int& t, int u, intl lim, intl& cost) {
	if (u == t) return lim;
	vis[u] = true; intl flow = 0;
	for (auto &it = cur[u]; it != g[u].end(); it++) {
		if (!it->r || vis[it->v] || dis[u] + it->w != dis[it->v]) continue;
		int delt = dfs(t, it->v, min(it->r, lim - flow), cost);
		flow += delt, cost += it->w * delt, it->r -= delt, (~it)->r += delt;
		if (flow == lim) break;
	} vis[u] = false; return flow;
}
inline int idx(int i, int j) { return (i - 1) * m + j; }
int main() {
	cin >> n >> m;
	int S = n * m + 1, T = n * m + 2;
	intl sum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> a[idx(i, j)], sum += a[idx(i, j)];
			if ((i + j) & 1) edge(S, idx(i, j), 1, 0);
			else edge(idx(i, j), T, 1, 0);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (i < n) {
				int u = idx(i, j), v = idx(i + 1, j);
				if (~ (i + j) & 1) swap(u, v);
				edge(u, v, 1, a[u] + a[v]);
			}
			if (j < m) {
				int u = idx(i, j), v = idx(i, j + 1);
				if (~ (i + j) & 1) swap(u, v);
				edge(u, v, 1, a[u] + a[v]);
			}
		}
	intl flow = 0, cost = 0;
	while (SPFA(T, S)) {
		intl delt = 0;
		do {
			for (int i = 1; i <= T; i++) cur[i] = g[i].begin();
			delt = dfs(T, S, infl, cost), flow += delt;
		} while (delt);
	} cout << sum - cost << "\n";
	return 0;
}
