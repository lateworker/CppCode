#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define eb emplace_back
#define IOS ios::sync_with_stdio(false),cin.tie(0)
int n,res,a[200010];
vector<int> e[200010];
set<int> s[200010];
void dfs(int u,int fa,int d){
	bool tmp=0; s[u].insert(d);
	for(int v:e[u]) if(v!=fa){
		dfs(v,u,d^a[v]);
		if(s[u].size()<s[v].size()) swap(s[u],s[v]);
		for(int i:s[v]) if(s[u].find(a[u]^i)!=s[u].end()) tmp=1;
		for(int i:s[v]) s[u].insert(i);
	}
	if(tmp) res++,s[u].clear();
}
signed main(){IOS;
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n-1){
		int u,v; cin>>u>>v;
		e[u].eb(v),e[v].eb(u);
	}
	dfs(1,0,a[1]);
	cout<<res;
}

