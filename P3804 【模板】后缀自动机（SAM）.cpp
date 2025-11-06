#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
struct SAM {
	int son[26], fa;
	SAM() { memset(son, 0, sizeof son); fa = -1; }
} st[N + 10];
int psz, last;
int len[N + 10], cnt[N + 10];
int node(int x) { len[++psz] = x; return psz; }
int append(int c) { c -= 'a';
	int p = last, u = node(len[p] + 1);
	cnt[u] = 1;
	for (; ~p && !st[p].son[c]; p = st[p].fa) st[p].son[c] = u;
	if (p == -1) st[u].fa = 0;
	else {
		int q = st[p].son[c];
		if (len[q] == len[p] + 1) st[u].fa = q;
		else {
			int v = node(len[p] + 1); st[v] = st[q];
			st[u].fa = st[q].fa = v;
			for (; ~p && st[p].son[c] == q; p = st[p].fa) st[p].son[c] = v;
		}
	} return last = u;
}
int deg[N + 10];
int solve() {
	queue<int> q;
	for (int u = 1; u <= psz; ++u) ++deg[st[u].fa];
	for (int u = 1; u <= psz; ++u)
		if (deg[u] == 0) q.push(u);
	while (!q.empty()) {
		int u = q.front(), v = st[u].fa; q.pop();
		cnt[v] += cnt[u];
		--deg[v]; if (!deg[v]) q.push(v);
	}
	int ans = 0;
	for (int i = 1; i <= psz; ++i)
		if (cnt[i] > 1) ans = max(ans, cnt[i] * len[i]);
	return ans;
}
signed main() {
	string s; cin >> s;
	for (char c : s) append(c);
	cout << solve() << "\n";
	return 0;
}
