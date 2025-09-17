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
template<typename... Args> inline void rd(Args&... args) { using namespace FastIn; (rd(args), ...); }
template<typename... Args> inline void wtsp(const Args&... args) { using namespace FastOut; ((wt(args), wt(' ')), ...); if constexpr (!sizeof...(args)) wt(' '); }
template<typename... Args> inline void wtln(const Args&... args) { using namespace FastOut; ((wt(args), wt('\n')), ...); if constexpr (!sizeof...(args)) wt('\n'); }
using namespace std;
const int N = 100000;
int n, m, fa[N + 10];
multiset<pair<int, int> > st[N + 10];
bool del[N + 10];
int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
int main() {
	rd(n, m);
	for (int i = 1; i <= n; i++) {
		int x; rd(x);
		st[i].emplace(x, i);
		fa[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		rd(op, x);
		if (op == 1) {
			rd(y);
			if (del[x] || del[y]) continue;
			x = find(x), y = find(y);
			if (x == y) continue;
			if (st[x].size() < st[y].size()) swap(x, y);
			for (const auto& val : st[y]) st[x].insert(val);
			fa[y] = x;
		} else {
			if (del[x]) { wtln(-1); continue; }
			x = find(x);
			auto [val, idx] = *st[x].begin();
			wtln(val), del[idx] = true;
			st[x].erase(st[x].begin());
		}
	}
	return 0;
}
