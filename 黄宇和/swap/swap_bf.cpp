#define ffopen(s) \
	cin.tie(0)->sync_with_stdio(0); \
	freopen((string(s) + ".in").c_str(), "r", stdin); \
	freopen((string(s) + ".out").c_str(), "w", stdout);
#include <bits/stdc++.h>
using namespace std;
const int N = 100000, M = 200000;
int n, m, s[M + 10], t[M + 10], ans[N + 10];
bool vis[N + 10];
void calc(int i) {
	int u = i, cnt = 0;
	vector<int> vec;
	for (int j = 1; j <= n; j++) vis[j] = false;
	while (true) {
		for (int j = 1; j <= m; j++) {
			u = (u == s[j] ? t[j] : u == t[j] ? s[j] : u);
			if (!vis[u]) ++cnt, vis[u] = true;
		}
		vec.push_back(u);
		if (u == i) break;
	}
	for (int j : vec) ans[j] = cnt;
}
int main() { ffopen("swap2");
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> s[i] >> t[i];
	for (int i = 1; i <= n; i++) if (!ans[i]) calc(i);
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
	return 0;
}
