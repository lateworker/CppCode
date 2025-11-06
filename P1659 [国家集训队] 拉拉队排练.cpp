#include <bits/stdc++.h>
using namespace std;
using intl = long long;
const intl N = 1000000, Mod = 19930726;
intl fpow(intl a, intl b) { intl c = 1; for (; b; (a *= a) %= Mod, b >>= 1) if (b & 1) (c *= a) %= Mod; return c; }
struct Pam {
	vector<int> ch;
	int fa; intl len, cnt;
} st[N + 10];
int last, psz;
int n; intl m;
char s[N + 10];
int node(int len, int fa) { return st[++psz] = {vector<int>(26, 0), fa, len, 0}, psz; }
void init() { s[0] = '#', st[0] = {vector<int>(26, 0), 1, 0, 0}, st[psz = 1] = {vector<int>(26, 0), 1, -1, 0}; }
int shorten(int u, int i) { while (s[i] != s[i - st[u].len - 1]) u = st[u].fa; return u; }
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m; init();
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		int c = s[i] - 'a', p = shorten(last, i);
		if (!st[p].ch[c]) st[p].ch[c] = node(st[p].len + 2, st[shorten(st[p].fa, i)].ch[c]);
		last = st[p].ch[c], ++st[last].cnt;
	}
	for (int i = psz; ~i; i--) st[st[i].fa].cnt += st[i].cnt;
	vector<pair<intl, intl>> vec;
	intl sum = 0;
	for (int i = 2; i <= psz; i++) {
		if (~ st[i].len & 1) continue;
		vec.push_back({st[i].len, st[i].cnt});
		sum += st[i].cnt;
	}
	if (sum < m) return cout << "-1\n", 0;
	sort(vec.begin(), vec.end(), [&](const auto& u, const auto& v) { return u.first > v.first; } );
	intl ans = 1;
	for (auto [len, cnt] : vec) {
		(ans *= fpow(len, min(intl(cnt), m))) %= Mod;
		m -= cnt; if (m <= 0) break;
	}
	cout << ans << "\n";
	return 0;
}
