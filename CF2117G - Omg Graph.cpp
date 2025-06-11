#include <bits/stdc++.h>
template<class T_, size_t N_, T_ DEFAULT = T_()>
class Array {
	T_ val[N_]; size_t ver[N_], clk;
public:
	Array() { clk = 1; }
	T_& operator[] (size_t i) { if (ver[i] != clk) ver[i] = clk, val[i] = DEFAULT; return val[i]; }
	void clear() { ++clk; }
};
using namespace std;
const int N = 200000, inf = 0x3f3f3f3f;
int n, m;
struct Edge { int u, v, w; } e[N + 10];
Array<int, N + 10> fa, mi;
int findf(int u) { return fa[u] == u ? u : fa[u] = findf(fa[u]); }
void slove() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> e[i].u >> e[i].v >> e[i].w;
	sort(e + 1, e + 1 + m, [&](const Edge& u, const Edge& v) { return u.w < v.w; } );
	int ans = inf;
	for (int i = 1; i <= m; i++) {
		
	}
}
int main() {
	
	return 0;
}
