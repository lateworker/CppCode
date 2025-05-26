#include <bits/stdc++.h>
using namespace std;
const int N = 200000;
int n, m;
pair<string, string> e[N + 10];
vector<string> vec;
vector<int> g[N + 10];
int bel[N + 10];
void dfs(int u, const int& r) {
	bel[u] = r;
	for (int v : g[u]) {
		if (bel[v] == r) {
			cout << "No\n"; exit(0);
		} else if (!bel[v]) dfs(v, r);
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s, t; cin >> s >> t;
		e[i] = make_pair(s, t);
		vec.push_back(s), vec.push_back(t);
	}
	sort(vec.begin(), vec.end()); vec.erase(unique(vec.begin(), vec.end()), vec.end());
	m = vec.size();
	for (int i = 1; i <= n; i++) {
		int u, v;
		u = lower_bound(vec.begin(), vec.end(), e[i].first) - vec.begin() + 1;
		v = lower_bound(vec.begin(), vec.end(), e[i].second) - vec.begin() + 1;
		g[u].push_back(v);
	}
	for (int i = 1; i <= m; i++) if (!bel[i]) dfs(i, i);
	cout << "Yes\n";
	return 0;
}
