#include <bits/stdc++.h>
using namespace std;
int n, m, l, r;
int tot = 0;
int fa = 0;
struct pnt {
	int val, lzi, rzi, siz, pri, tag;
} p[100005 << 2];
void pushup(int u) { p[u].siz = p[p[u].lzi].siz + p[p[u].rzi].siz + 1; }
int assignment(int x) {
	tot++;
	int u = tot;
//	cout << u << " " << x << "\n";
	p[u].val = x;
	p[u].lzi = p[u].rzi = 0;
	p[u].siz = 1;
	p[u].pri = rand();
	p[u].tag = 0;
	pushup(u); // 切记不要对叶结点pushup
	return u;
}
void pushdown(int u) {
	p[u].tag ^= 1;
//	p[u].tag = 0;
//	cout << p[u].val << "pd\n";
	swap(p[u].lzi, p[u].rzi);
	p[p[u].lzi].tag ^= 1;
	p[p[u].rzi].tag ^= 1;
}
void split(int u, int k, int &l, int &r) {
	if (u == 0) return void(l = r = 0);
	
	// 要访问 u 的子树，肯定要pushdown
	if (p[u].tag) pushdown(u);
	
	if (k <= p[p[u].lzi].siz) { // 你在这里偷偷访问了 u 的左子树，但你还没 pushdown，就炸了
//		if (p[u].tag) pushdown(u);
		r = u;
		split(p[u].lzi, k, l, p[u].lzi);
	} else {
//		if (p[u].tag) pushdown(u);
		l = u;
		split(p[u].rzi, k - p[p[u].lzi].siz - 1, p[u].rzi, r); //split的是前k个数
	}
	pushup(u);
}
int merge(int u, int v) {
	if (u == 0 || v == 0) return u | v; // 我习惯这么写
	if (p[u].pri < p[v].pri)
	{
		if (p[u].tag) pushdown(u);
		p[u].rzi = merge(p[u].rzi, v);
		pushup(u);
		return u;
	} else {
		if (p[v].tag) pushdown(v);
		p[v].lzi = merge(u, p[v].lzi);
		pushup(v);
		return v;
	}
}
void insert(int &fa, int u) {
	int l, r;
	split(fa, u, l, r);
	fa = merge(merge(l, assignment(u)), r);
}
void exchange(int&fa, int x, int y) {
	int l, mid, r;
	split(fa, x - 1, l, mid);
	split(mid, y - x + 1, mid, r); //将l到r的元素split出来
//	cout << y << " " << x << "ex\n";
	p[mid].tag ^= 1;
	fa = merge(l, merge(mid, r));
}
void dfs(int u) {
	if (u == 0) return;
	if (p[u].tag) pushdown(u);
	dfs(p[u].lzi);
	printf("%d ", p[u].val);
	dfs(p[u].rzi);
}
int main() {
	//srand(time(0));
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; i++) insert(fa, i);
	while (m--) {
		scanf("%d%d", &l, &r);
		exchange(fa, l, r);
	}
	dfs(fa);
}
