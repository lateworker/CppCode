#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const int N = 300000;
struct Pam {
	vector<int> ch;
	int fa, len, cnt;
} st[N + 10];
int last, psz;
string s;
int node(int len, int fa) { return st[++psz] = {vector<int>(26, 0), fa, len, 0}, psz; }
void init() {
	st[0] = {vector<int>(26, 0/*point to node `0`*/), 1/*point to node `-1`*/, 0, 0};
	st[1] = {vector<int>(26, 0/*point to node `0`*/), 1/*point to node `-1`*/, -1, 0};
	s[0] = '#', psz = 1;
}
int shorten(int u, int i) { while (s[i] != s[i - st[u].len - 1]) u = st[u].fa; return u; }
void append(int i) {
	int c = s[i] - 'a', p = shorten(last, i);
	if (!st[p].ch[c]) st[p].ch[c] = node(st[p].len + 2, st[shorten(st[p].fa, i)].ch[c]);
	last = st[p].ch[c], ++st[last].cnt;
}
int main() {
	init();
	cin >> s; int n = s.size(); s = '#' + s;
	for (int i = 1; i <= n; i++) append(i);
	for (int i = psz; i >= 0; i--) st[st[i].fa].cnt += st[i].cnt;
	intl ans = 0;
	for (int i = 1; i <= psz; i++)
		ans = max(ans, (intl) st[i].len * st[i].cnt);
	cout << ans << "\n";
	return 0;
}
