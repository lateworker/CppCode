#include<stdio.h>
const long long mod=19940417,inv2=9970209,inv6=3323403;
long long i,j,k,m,n,l,r,ans,tmp1,tmp2,tmp3;
inline long long min(long long a,long long b){
	return a<b? a:b; 
}
inline void swp(long long &a,long long &b){
	a+=b,b=a-b,a-=b;
}
inline long long sum1(long long x){
	return x*(x+1)%mod*inv2%mod;
}
inline long long sum2(long long x){
	return x*(x+1)%mod*(2*x+1)%mod*inv6%mod;
}
int main(){
	scanf("%lld%lld",&n,&m);
	if(n>m)
		swp(n,m);
	l=1,tmp1=n*n%mod;
	while(l<=n){
		r=n/(n/l);
		tmp1=(tmp1-(sum1(r)-sum1(l-1)+mod)%mod*(n/l)%mod+mod)%mod;
		l=r+1;
	}
	l=1,tmp2=m*m%mod;
	while(l<=m){
		r=m/(m/l);
		tmp2=(tmp2-(sum1(r)-sum1(l-1)+mod)%mod*(m/l)%mod+mod)%mod;
		l=r+1;
	}
	l=1,tmp3=0;
	while(l<=n){
		long long a,b,c;
		a = b = c = 0;
		r=min(n/(n/l),m/(m/l));
		a=(r-l+1)*n%mod*m%mod;
		b=(sum1(r)-sum1(l-1)+mod)%mod*((n/l)*m%mod+(m/l)*n%mod)%mod;
		c=(sum2(r)-sum2(l-1)+mod)%mod*(n/l)%mod*(m/l)%mod;
		tmp3=(tmp3+a-b+c+mod)%mod;
		l=r+1;
	}
	ans=(tmp1*tmp2%mod-tmp3+mod)%mod;
	printf("%lld\n",ans);
	return 0;
} 

