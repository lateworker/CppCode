#include<bits/stdc++.h>
using std::cin,std::cout,std::min,std::max;
using ll=long long;
const int N=2e5+10,inf=1e9+10;

int main(){
	cin.tie(0)->sync_with_stdio(0);
	freopen("stone.in","w",stdout);
	int n = 2100;
	cout<<n<<"\n0 ";
	for(int i=1;i<=n/3;++i)cout<<"1 ";
	for(int i=1;i<=n/3;++i)cout<<"2 ";
	for(int i=1;i<=n/3;++i)cout<<"3 ";
	cout<<n+1<<"\n0 ";
	for(int i=1;i<=n/3;++i)cout<<"3 ";
	for(int i=1;i<=n/3;++i)cout<<"2 ";
	for(int i=1;i<=n/3;++i)cout<<"1 ";
	cout<<n+1;
	return 0;
}
