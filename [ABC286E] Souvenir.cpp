#include <bits/stdc++.h>
using intl = long long;
using namespace std;
const intl N = 300, inf = 0x3f3f3f3f3f3f3f3f;
intl n, a[N + 10];
vector<int> g[N + 10];
pair<intl, intl> ans[N + 10][N + 10];
#define dis(u) (now[u].first)
#define rew(u) (now[u].second)
void bfs(int s) {
	auto now = ans[s];
	queue<int> que;
	now[s] = {0, a[s]}, que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int v : g[u]) {
			if (dis(v) == inf) {
				dis(v) = dis(u) + 1, rew(v) = rew(u) + a[v];
				que.push(v);
			} else if (dis(v) == dis(u) + 1) {
				rew(v) = max(rew(v), rew(u) + a[v]);
			}
		}
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			char c; cin >> c;
			if (c == 'Y') g[i].push_back(j);
			ans[i][j] = {inf, -inf};
		}
	for (int i = 1; i <= n; i++) bfs(i);
	int q; cin >> q;
	while (q--) {
		int u, v; cin >> u >> v;
		if (ans[u][v].first == inf) cout << "Impossible\n";
		else cout << ans[u][v].first << " " << ans[u][v].second << "\n";
	}
	return 0;
}
