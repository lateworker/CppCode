#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if constexpr (*#s) freopen(#s ".in", "r", stdin); \
if constexpr (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) (x = std::max(x, y))
#define chkmin(x, y) (x = std::min(x, y))
#define gc() (eof||(p==SIZE&&(buf[fread(buf,1,SIZE,stdin)]=EOF,(p=0)))||~buf[p]?buf[p++]:(eof=true,EOF))
#define ug(x) (eof=false,buf[--p]=(x))
#define pc(x) (buf[p++]=(x),p==SIZE?fl():p)
#define fl() (fwrite(buf,1,p,stdout),p=0)
namespace FastIn { constexpr size_t SIZE = 1 << 16; size_t p = SIZE; char buf[SIZE | 1], c; bool f, eof; inline void rd(char& x) { while(isspace(x=gc())); } inline void rd(char* s) { while(isspace(*s=gc()));if(eof){return;}for(;!isspace(*s)&&!eof;*++s=gc());ug(*s),*s='\0'; } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128>, void> rd(T& x) { x=f=0;while(isspace(c=gc()));if(eof){return;}if(c=='-'){f=true,c=gc();}for(;isdigit(c);c=gc()){x=(x<<1)+(x<<3)+(c^'0');}ug(c);if(f){x=-x;} } }
namespace FastOut { constexpr size_t SIZE = 1 << 18; char buf[SIZE], c[40]; size_t f, p; struct __{~__(){fl();}}__; inline void wt(char x) { pc(x); } inline void wt(const char* s) { while(*s)pc(*s++); } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128>, void> wt(T x) { if(!x){pc('0');return;}f=0;if(x<0)x=-x,pc('-');while(x){c[f++]=x%10^'0',x/=10;}while(f--){pc(c[f]);} } }
template<typename... Args> inline void rd(Args&... args) { using namespace FastIn; (rd(args), ...); }
template<typename... Args> inline void wtsp(const Args&... args) { using namespace FastOut; ((wt(args), wt(' ')), ...); if constexpr (!sizeof...(args)) wt(' '); }
template<typename... Args> inline void wtln(const Args&... args) { using namespace FastOut; ((wt(args), wt('\n')), ...); if constexpr (!sizeof...(args)) wt('\n'); }
using namespace std;
using intl = long long;
const intl N = 100000, Mod = 1000000007;
int n, f[N + 10][2];
vector<int> g[N + 10];
void dfs(int u, int p) {
	for (int v : g[u]) if (v != p) {
		dfs(v, u);
		f[u][1] = (intl) f[u][0] * f[v][1] % Mod + (intl) f[u][1] * (f[v][0] + f[v][1]) % Mod, f[u][1] %= Mod;
		f[u][0] = (intl) f[u][0] * (f[v][0] + f[v][1]) % Mod, f[u][0] %= Mod;
	}
}
int main() {
	rd(n);
	for (int i = 2; i <= n; i++) {
		int fa; rd(fa); ++fa;
		g[i].push_back(fa);
		g[fa].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		int x; rd(x);
		f[i][x] = 1;
	}
	dfs(1, 0), wtln(f[1][1]);
	return 0;
}
