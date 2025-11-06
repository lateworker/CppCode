#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
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
template<typename... Args> inline void rd(Args&&... args) { using namespace FastIn; (rd(args), ...); }
template<typename... Args> inline void wtsp(Args&&... args) { using namespace FastOut; ((wt(args), wt(' ')), ...); if constexpr (!sizeof...(args)) wt(' '); }
template<typename... Args> inline void wtln(Args&&... args) { using namespace FastOut; ((wt(args), wt('\n')), ...); if constexpr (!sizeof...(args)) wt('\n'); }
using namespace std;
using intl = long long;
constexpr intl N = 2000, TN = 2001, Mod = 1000000007;
intl n, f[N + 10][N * 2 + 10], g[N + 10][N * 2 + 10];
char s[N + 10], t[N + 10];
inline bool chksame(char x, bool c) { return x == '?' || x == (c ? '1' : '0'); }
void slove() {
	rd(n, s + 1, t + 1);
	for (int i = 0; i <= n + 1; i++)
		for (int j = -n; j <= n; j++)
			f[i][j + TN] = g[i][j + TN] = 0;
	f[0][TN] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = -i; j <= i; j++)
			for (int x : {0, 1}) for (int y : {0, 1})
				if (chksame(s[i], x ^ (i & 1)) && chksame(t[i], y ^ (i & 1)))
					f[i][j + TN] += f[i - 1][j + TN - (x - y)], f[i][j + TN] %= Mod;
	}
	g[n + 1][TN] = 1;
	for (int i = n; i >= 1; i--) {
		for (int j = i - n - 1; j <= n - i + 1; j++)
			for (int x : {0, 1}) for (int y : {0, 1})
				if (chksame(s[i], x ^ (i & 1)) && chksame(t[i], y ^ (i & 1)))
					g[i][j + TN] += g[i + 1][j + TN - (x - y)], g[i][j + TN] %= Mod;
	}
	intl ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = -i; j <= i; j++)
			ans += f[i][TN + j] * g[i + 1][TN - j] % Mod * abs(j) % Mod, ans %= Mod;
	wtln(ans);
}
int main() {
	int T; rd(T);
	while (T--) slove();
	return 0;
}
