#define ffopen(s) \
std::cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
#define chkmax(x, y) ((x) = std::max((x), (y)))
#define chkmin(x, y) ((x) = std::min((x), (y)))
#define gc() (eof||(p==SIZE&&(buf[fread(buf,1,SIZE,stdin)]=EOF,(p=0)))||~buf[p]?buf[p++]:(eof=true,EOF))
#define ug(x) (eof=false,buf[--p]=(x))
#define pc(x) (buf[p++]=(x),p==SIZE?fl():p)
#define fl() (fwrite(buf,1,p,stdout),p=0)
namespace FastIn { constexpr size_t SIZE = 1 << 16; size_t p = SIZE; char buf[SIZE | 1], c; bool f, eof; inline void rd(char& x) { while(isspace(x=gc())); } inline void rd(char* s) { while(isspace(*s=gc()));if(eof){return;}for(;!isspace(*s)&&!eof;*++s=gc());ug(*s),*s='\0'; } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128> || std::is_same_v<T, unsigned __int128> > rd(T& x) { x=f=0;while(isspace(c=gc()));if(eof){return;}if(c=='-'){f=true,c=gc();}for(;isdigit(c);c=gc()){x=(x<<1)+(x<<3)+(c^'0');}ug(c);if(f){x=-x;} } }
namespace FastOut { constexpr size_t SIZE = 1 << 18; char buf[SIZE], c[40]; size_t f, p; struct __{~__(){fl();}}__; inline void wt(char x) { pc(x); } inline void wt(const char* s) { while(*s)pc(*s++); } template<typename T> inline std::enable_if_t<std::is_integral<T>::value || std::is_same_v<T, __int128> || std::is_same_v<T, unsigned __int128> > wt(T x) { if(!x){pc('0');return;}f=0;if(x<0)x=-x,pc('-');while(x){c[f++]=x%10^'0',x/=10;}while(f--){pc(c[f]);} } }
template<typename... Args> inline void rd(Args&&... args) { using namespace FastIn; (rd(args), ...); }
template<typename... Args> inline void wtsp(Args&&... args) { using namespace FastOut; ((wt(args), wt(' ')), ...); if constexpr (!sizeof...(args)) wt(' '); }
template<typename... Args> inline void wtln(Args&&... args) { using namespace FastOut; ((wt(args), wt('\n')), ...); if constexpr (!sizeof...(args)) wt('\n'); }
template<typename Iter> std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value> rd(Iter begin, Iter end) { while (begin != end) rd(*begin++); }
template<typename Iter> std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value> wtsp(Iter begin, Iter end) { while (begin != end) wtsp(*begin++); }
template<typename Iter> std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value> wtln(Iter begin, Iter end) { while (begin != end) wtln(*begin++); }
template<typename T_, size_t N_, T_ DEFAULT_ = T_()> class Array { T_ val[N_]; size_t ver[N_], clk; public: Array() { clk=1; } T_& operator[] (size_t i) { if(ver[i]!=clk){ver[i]=clk,val[i]=DEFAULT_;} return val[i]; } void clear() { ++clk; } };
template<typename T_, size_t N_> class Graph { inline static size_t psz; inline static std::pair<T_, size_t> pool[N_]; struct iterator { size_t now; T_& operator* () const { return pool[now].first; } bool operator== (iterator it) const { return now == it.now; } iterator& operator++ () { now=pool[now].second; return *this; } }; size_t head; public: Graph() { head = 0; } iterator begin() const { return {head}; } iterator end() const { return {0}; } void push_back(const T_& val) { ++psz,this->pool[psz]={val, head},head=psz; } void clear() { psz=head=0; } };
using std::min, std::max;
using intl = long long;
const intl N = 300, Mod = 1000000007;
int n, a[N + 10];
intl f[N + 10][N + 10];
struct Tnum {
	Array<int, N + 10> st;
	void modify(int u, intl val) { ++u; for (; u <= n; u += u & -u) st[u] += val, st[u] %= Mod; }
	intl query(int u) { ++u; intl res = 0; for (; u; u -= u & -u) res += st[u], res %= Mod; return res; }
} t1[N + 10];
int main() {
	int T; rd(T);
	while (T--) {
		rd(n), rd(a + 1, a + 1 + n);
		f[0][0] = 1;
//		for (int k = 0; k <=).
		t1[0].modify(a[0], f[0][0]);
		for (int i = 1; i <= n; i++) {
			for (int k = 0; k < i; k++) {
				if (a[k] > a[i]) continue;
				intl res = t1[k].query(a[i]);
//				intl res = 0;
//				for (int j = 0; j < i; j++) {
//					if (a[i] >= a[j]) (res += f[j][k]) %= Mod;
//				}
				f[i][k] += res, f[i][k] %= Mod;
			}
			for (int j = 0; j < i; j++) {
				intl res = 0;
				for (int k = 0; k < i; k++) {
					if (a[k] <= a[i] && a[i] < a[j]) (res += f[j][k]) %= Mod;
				}
				f[j][i] += res, f[j][i] %= Mod;
			}
			for (int k = 0; k < i; k++) {
				if (a[k] > a[i]) continue;
				t1[k].modify(a[i], f[i][k]);
				
			}
			for (int j = 0; j < i; j++) {
				t1[i].modify(a[j], f[j][i]);
				
			}
		}
		intl ans = 0;
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n; k++)
				ans += f[j][k], ans %= Mod;
		wtln(ans);
		
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n; k++) f[j][k] = 0;
		for (int k = 0; k <= n; k++) {
			t1[k].st.clear();
		}
	}
	return 0;
}
