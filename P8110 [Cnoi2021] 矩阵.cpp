#define ffopen(s) \
cin.tie(0)->sync_with_stdio(0); \
if (*#s) freopen(#s ".in", "r", stdin); \
if (*#s) freopen(#s ".out", "w", stdout); \
/**/
#include <bits/stdc++.h>
namespace std {
#ifndef ATCODER_MODINT_HPP
#define ATCODER_MODINT_HPP 1
	
#include <cassert>
#include <numeric>
#include <type_traits>
	
#ifdef _MSC_VER
#include <intrin.h>
#endif
	
#ifndef ATCODER_INTERNAL_TYPE_TRAITS_HPP
#define ATCODER_INTERNAL_TYPE_TRAITS_HPP 1
	
#include <cassert>
#include <numeric>
#include <type_traits>
	
	namespace atcoder {
		
		namespace internal {
			
#ifndef _MSC_VER
			template <class T>
			using is_signed_int128 =
			typename std::conditional<std::is_same<T, __int128_t>::value ||
			std::is_same<T, __int128>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using is_unsigned_int128 =
			typename std::conditional<std::is_same<T, __uint128_t>::value ||
			std::is_same<T, unsigned __int128>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using make_unsigned_int128 =
			typename std::conditional<std::is_same<T, __int128_t>::value,
			__uint128_t,
			unsigned __int128>;
			
			template <class T>
			using is_integral = typename std::conditional<std::is_integral<T>::value ||
			is_signed_int128<T>::value ||
			is_unsigned_int128<T>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using is_signed_int = typename std::conditional<(is_integral<T>::value &&
				std::is_signed<T>::value) ||
			is_signed_int128<T>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using is_unsigned_int =
			typename std::conditional<(is_integral<T>::value &&
				std::is_unsigned<T>::value) ||
			is_unsigned_int128<T>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using to_unsigned = typename std::conditional<
			is_signed_int128<T>::value,
			make_unsigned_int128<T>,
			typename std::conditional<std::is_signed<T>::value,
			std::make_unsigned<T>,
			std::common_type<T>>::type>::type;
			
#else
			
			template <class T> using is_integral = typename std::is_integral<T>;
			
			template <class T>
			using is_signed_int =
			typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using is_unsigned_int =
			typename std::conditional<is_integral<T>::value &&
			std::is_unsigned<T>::value,
			std::true_type,
			std::false_type>::type;
			
			template <class T>
			using to_unsigned = typename std::conditional<is_signed_int<T>::value,
			std::make_unsigned<T>,
			std::common_type<T>>::type;
			
#endif
			
			template <class T>
			using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
			
			template <class T>
			using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
			
			template <class T> using to_unsigned_t = typename to_unsigned<T>::type;
			
		}  // namespace internal
		
	}  // namespace atcoder
	
#endif  // ATCODER_INTERNAL_TYPE_TRAITS_HPP
	
#ifndef ATCODER_INTERNAL_MATH_HPP
#define ATCODER_INTERNAL_MATH_HPP 1
	
#include <utility>
	
#ifdef _MSC_VER
#include <intrin.h>
#endif
	
	namespace atcoder {
		
		namespace internal {
			
// @param m `1 <= m`
// @return x mod m
			constexpr long long safe_mod(long long x, long long m) {
				x %= m;
				if (x < 0) x += m;
				return x;
			}
			
// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
			struct barrett {
				unsigned int _m;
				unsigned long long im;
				
				// @param m `1 <= m`
				explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}
				
				// @return m
				unsigned int umod() const { return _m; }
				
				// @param a `0 <= a < m`
				// @param b `0 <= b < m`
				// @return `a * b % m`
				unsigned int mul(unsigned int a, unsigned int b) const {
					// [1] m = 1
					// a = b = im = 0, so okay
					
					// [2] m >= 2
					// im = ceil(2^64 / m)
					// -> im * m = 2^64 + r (0 <= r < m)
					// let z = a*b = c*m + d (0 <= c, d < m)
					// a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
					// c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
					// ((ab * im) >> 64) == c or c + 1
					unsigned long long z = a;
					z *= b;
#ifdef _MSC_VER
					unsigned long long x;
					_umul128(z, im, &x);
#else
					unsigned long long x =
					(unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
					unsigned long long y = x * _m;
					return (unsigned int)(z - y + (z < y ? _m : 0));
				}
			};
			
// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
			constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
				if (m == 1) return 0;
				unsigned int _m = (unsigned int)(m);
				unsigned long long r = 1;
				unsigned long long y = safe_mod(x, m);
				while (n) {
					if (n & 1) r = (r * y) % _m;
					y = (y * y) % _m;
					n >>= 1;
				}
				return r;
			}
			
// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
			constexpr bool is_prime_constexpr(int n) {
				if (n <= 1) return false;
				if (n == 2 || n == 7 || n == 61) return true;
				if (n % 2 == 0) return false;
				long long d = n - 1;
				while (d % 2 == 0) d /= 2;
				constexpr long long bases[3] = {2, 7, 61};
				for (long long a : bases) {
					long long t = d;
					long long y = pow_mod_constexpr(a, t, n);
					while (t != n - 1 && y != 1 && y != n - 1) {
						y = y * y % n;
						t <<= 1;
					}
					if (y != n - 1 && t % 2 == 0) {
						return false;
					}
				}
				return true;
			}
			template <int n> constexpr bool is_prime = is_prime_constexpr(n);
			
// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
			constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
				a = safe_mod(a, b);
				if (a == 0) return {b, 0};
				
				// Contracts:
				// [1] s - m0 * a = 0 (mod b)
				// [2] t - m1 * a = 0 (mod b)
				// [3] s * |m1| + t * |m0| <= b
				long long s = b, t = a;
				long long m0 = 0, m1 = 1;
				
				while (t) {
					long long u = s / t;
					s -= t * u;
					m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b
					
					// [3]:
					// (s - t * u) * |m1| + t * |m0 - m1 * u|
					// <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
					// = s * |m1| + t * |m0| <= b
					
					auto tmp = s;
					s = t;
					t = tmp;
					tmp = m0;
					m0 = m1;
					m1 = tmp;
				}
				// by [3]: |m0| <= b/g
				// by g != b: |m0| < b/g
				if (m0 < 0) m0 += b / s;
				return {s, m0};
			}
			
// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
			constexpr int primitive_root_constexpr(int m) {
				if (m == 2) return 1;
				if (m == 167772161) return 3;
				if (m == 469762049) return 3;
				if (m == 754974721) return 11;
				if (m == 998244353) return 3;
				int divs[20] = {};
				divs[0] = 2;
				int cnt = 1;
				int x = (m - 1) / 2;
				while (x % 2 == 0) x /= 2;
				for (int i = 3; (long long)(i)*i <= x; i += 2) {
					if (x % i == 0) {
						divs[cnt++] = i;
						while (x % i == 0) {
							x /= i;
						}
					}
				}
				if (x > 1) {
					divs[cnt++] = x;
				}
				for (int g = 2;; g++) {
					bool ok = true;
					for (int i = 0; i < cnt; i++) {
						if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
							ok = false;
							break;
						}
					}
					if (ok) return g;
				}
			}
			template <int m> constexpr int primitive_root = primitive_root_constexpr(m);
			
// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
			unsigned long long floor_sum_unsigned(unsigned long long n,
				unsigned long long m,
				unsigned long long a,
				unsigned long long b) {
					unsigned long long ans = 0;
					while (true) {
						if (a >= m) {
							ans += n * (n - 1) / 2 * (a / m);
							a %= m;
						}
						if (b >= m) {
							ans += n * (b / m);
							b %= m;
						}
						
						unsigned long long y_max = a * n + b;
						if (y_max < m) break;
						// y_max < m * (n + 1)
						// floor(y_max / m) <= n
						n = (unsigned long long)(y_max / m);
						b = (unsigned long long)(y_max % m);
						std::swap(m, a);
					}
					return ans;
				}
			
		}  // namespace internal
		
	}  // namespace atcoder
	
#endif  // ATCODER_INTERNAL_MATH_HPP
	
	namespace atcoder {
		
		namespace internal {
			
			struct modint_base {};
			struct static_modint_base : modint_base {};
			
			template <class T> using is_modint = std::is_base_of<modint_base, T>;
			template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;
			
		}  // namespace internal
		
		template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
		struct static_modint : internal::static_modint_base {
			using mint = static_modint;
			
		public:
			static constexpr int mod() { return m; }
			static mint raw(int v) {
				mint x;
				x._v = v;
				return x;
			}
			
			static_modint() : _v(0) {}
			template <class T, internal::is_signed_int_t<T>* = nullptr>
			static_modint(T v) {
				long long x = (long long)(v % (long long)(umod()));
				if (x < 0) x += umod();
				_v = (unsigned int)(x);
			}
			template <class T, internal::is_unsigned_int_t<T>* = nullptr>
			static_modint(T v) {
				_v = (unsigned int)(v % umod());
			}
			
			int val() const { return _v; }
			
			mint& operator++() {
				_v++;
				if (_v == umod()) _v = 0;
				return *this;
			}
			mint& operator--() {
				if (_v == 0) _v = umod();
				_v--;
				return *this;
			}
			mint operator++(int) {
				mint result = *this;
				++*this;
				return result;
			}
			mint operator--(int) {
				mint result = *this;
				--*this;
				return result;
			}
			
			mint& operator+=(const mint& rhs) {
				_v += rhs._v;
				if (_v >= umod()) _v -= umod();
				return *this;
			}
			mint& operator-=(const mint& rhs) {
				_v -= rhs._v;
				if (_v >= umod()) _v += umod();
				return *this;
			}
			mint& operator*=(const mint& rhs) {
				unsigned long long z = _v;
				z *= rhs._v;
				_v = (unsigned int)(z % umod());
				return *this;
			}
			mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
			
			mint operator+() const { return *this; }
			mint operator-() const { return mint() - *this; }
			
			mint pow(long long n) const {
				assert(0 <= n);
				mint x = *this, r = 1;
				while (n) {
					if (n & 1) r *= x;
					x *= x;
					n >>= 1;
				}
				return r;
			}
			mint inv() const {
				if (prime) {
					assert(_v);
					return pow(umod() - 2);
				} else {
					auto eg = internal::inv_gcd(_v, m);
					assert(eg.first == 1);
					return eg.second;
				}
			}
			
			friend mint operator+(const mint& lhs, const mint& rhs) {
				return mint(lhs) += rhs;
			}
			friend mint operator-(const mint& lhs, const mint& rhs) {
				return mint(lhs) -= rhs;
			}
			friend mint operator*(const mint& lhs, const mint& rhs) {
				return mint(lhs) *= rhs;
			}
			friend mint operator/(const mint& lhs, const mint& rhs) {
				return mint(lhs) /= rhs;
			}
			friend bool operator==(const mint& lhs, const mint& rhs) {
				return lhs._v == rhs._v;
			}
			friend bool operator!=(const mint& lhs, const mint& rhs) {
				return lhs._v != rhs._v;
			}
			
		private:
			unsigned int _v;
			static constexpr unsigned int umod() { return m; }
			static constexpr bool prime = internal::is_prime<m>;
		};
		
		template <int id> struct dynamic_modint : internal::modint_base {
			using mint = dynamic_modint;
			
		public:
			static int mod() { return (int)(bt.umod()); }
			static void set_mod(int m) {
				assert(1 <= m);
				bt = internal::barrett(m);
			}
			static mint raw(int v) {
				mint x;
				x._v = v;
				return x;
			}
			
			dynamic_modint() : _v(0) {}
			template <class T, internal::is_signed_int_t<T>* = nullptr>
			dynamic_modint(T v) {
				long long x = (long long)(v % (long long)(mod()));
				if (x < 0) x += mod();
				_v = (unsigned int)(x);
			}
			template <class T, internal::is_unsigned_int_t<T>* = nullptr>
			dynamic_modint(T v) {
				_v = (unsigned int)(v % mod());
			}
			
			int val() const { return _v; }
			
			mint& operator++() {
				_v++;
				if (_v == umod()) _v = 0;
				return *this;
			}
			mint& operator--() {
				if (_v == 0) _v = umod();
				_v--;
				return *this;
			}
			mint operator++(int) {
				mint result = *this;
				++*this;
				return result;
			}
			mint operator--(int) {
				mint result = *this;
				--*this;
				return result;
			}
			
			mint& operator+=(const mint& rhs) {
				_v += rhs._v;
				if (_v >= umod()) _v -= umod();
				return *this;
			}
			mint& operator-=(const mint& rhs) {
				_v += mod() - rhs._v;
				if (_v >= umod()) _v -= umod();
				return *this;
			}
			mint& operator*=(const mint& rhs) {
				_v = bt.mul(_v, rhs._v);
				return *this;
			}
			mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
			
			mint operator+() const { return *this; }
			mint operator-() const { return mint() - *this; }
			
			mint pow(long long n) const {
				assert(0 <= n);
				mint x = *this, r = 1;
				while (n) {
					if (n & 1) r *= x;
					x *= x;
					n >>= 1;
				}
				return r;
			}
			mint inv() const {
				auto eg = internal::inv_gcd(_v, mod());
				assert(eg.first == 1);
				return eg.second;
			}
			
			friend mint operator+(const mint& lhs, const mint& rhs) {
				return mint(lhs) += rhs;
			}
			friend mint operator-(const mint& lhs, const mint& rhs) {
				return mint(lhs) -= rhs;
			}
			friend mint operator*(const mint& lhs, const mint& rhs) {
				return mint(lhs) *= rhs;
			}
			friend mint operator/(const mint& lhs, const mint& rhs) {
				return mint(lhs) /= rhs;
			}
			friend bool operator==(const mint& lhs, const mint& rhs) {
				return lhs._v == rhs._v;
			}
			friend bool operator!=(const mint& lhs, const mint& rhs) {
				return lhs._v != rhs._v;
			}
			
		private:
			unsigned int _v;
			static internal::barrett bt;
			static unsigned int umod() { return bt.umod(); }
		};
		template <int id> internal::barrett dynamic_modint<id>::bt(998244353);
		
		using modint998244353 = static_modint<998244353>;
		using modint1000000007 = static_modint<1000000007>;
		using modint = dynamic_modint<-1>;
		
		namespace internal {
			
			template <class T>
			using is_static_modint = std::is_base_of<internal::static_modint_base, T>;
			
			template <class T>
			using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
			
			template <class> struct is_dynamic_modint : public std::false_type {};
			template <int id>
			struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};
			
			template <class T>
			using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;
			
		}  // namespace internal
		
	}  // namespace atcoder
	
#endif  // ATCODER_MODINT_HPP
	
	template<class T_>
	class Matrix {
		size_t n, m;
		vector<vector<T_>> val;
		
	public:
		Matrix()											{ n = m = 0; val.clear(); }
		Matrix(size_t n, size_t m, const T_& val = T_())	{ this->resize(n, m, val); }
		Matrix(const initializer_list<initializer_list<T_>>& initlist);
		
		size_t size() const;
		size_t row() const;
		size_t column() const;
		
		void resize(size_t n, size_t m, const T_& val = T_());
		Matrix<T_> transpose() const;
		static Matrix<T_> identity(size_t n, const T_& val = T_(1));
		
		vector<T_>& operator[] (size_t i) { return val[i]; }
		const vector<T_>& operator[] (size_t i) const { return val[i]; }
		
		Matrix<T_> operator+ () const;
		Matrix<T_> operator- () const;
		Matrix<T_> operator+ (const Matrix<T_>&) const;
		Matrix<T_> operator- (const Matrix<T_>&) const;
		Matrix<T_> operator* (const T_&) const;
		Matrix<T_> operator* (const Matrix<T_>&) const;
		
		Matrix<T_>& operator+= (const Matrix<T_>&);
		Matrix<T_>& operator-= (const Matrix<T_>&);
		Matrix<T_>& operator*= (const T_&);
		Matrix<T_>& operator*= (const Matrix<T_>&);
	};
	
	template<class T_>
	Matrix<T_>::Matrix(const initializer_list<initializer_list<T_>>& initlist) {
		size_t n = initlist.size(), m = 0;
		for (const initializer_list<T_>& now : initlist) m = max(m, now.size());
		this->resize(n, m);
		for (size_t i = 0; i < n; ++i) {
			const initializer_list<T_>& now = *(initlist.begin() + i);
			for (size_t j = 0; j < m; ++j) {
				if (j < now.size()) val[i][j] = *(now.begin() + j);
				else break;
			}
		}
	}
	
	template<class T_> size_t Matrix<T_>::size() const { return n * m; }
	template<class T_> size_t Matrix<T_>::row() const { return n; }
	template<class T_> size_t Matrix<T_>::column() const { return m; }
	
	template<class T_>
	void Matrix<T_>::resize(size_t n, size_t m, const T_& val) {
		this->n = n, this->m = m;
		this->val.resize(n, vector<T_>(m, val));
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::transpose() const {
		Matrix<T_> c(m, n);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j)
				c[j][i] = (*this)[i][j];
		} return c;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::identity(size_t n, const T_& val) {
		Matrix<T_> a(n, n);
		for (size_t i = 0; i < n; ++i) a[i][i] = val;
		return a;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::operator+ () const {
		const Matrix<T_>& a = *this;
		Matrix<T_> c(n, m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j)
				c[i][j] = +a[i][j];
		} return c;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::operator- () const {
		const Matrix<T_>& a = *this;
		Matrix<T_> c(n, m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j)
				c[i][j] = -a[i][j];
		} return c;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::operator+ (const Matrix<T_>& b) const {
		const Matrix<T_>& a = *this;
		if (a.n != b.n || a.m != b.m) throw runtime_error("Matrix dimension mismatch");
		Matrix<T_> c(n, m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j)
				c[i][j] = a[i][j] + b[i][j];
		} return c;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::operator- (const Matrix<T_>& b) const {
		const Matrix<T_>& a = *this;
		if (a.n != b.n || a.m != b.m) throw runtime_error("Matrix dimension mismatch");
		Matrix<T_> c(n, m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j)
				c[i][j] = a[i][j] - b[i][j];
		} return c;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::operator* (const T_& k) const {
		const Matrix<T_>& a = *this;
		Matrix<T_> c(n, m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j)
				c[i][j] = a[i][j] * k;
		} return c;
	}
	
	template<class T_>
	Matrix<T_> Matrix<T_>::operator* (const Matrix<T_>& b) const {
		const Matrix<T_>& a = *this;
		if (a.m != b.n) throw runtime_error("Matrix dimension mismatch for multiply");
		size_t x = a.n, y = a.m, z = b.m;
		Matrix<T_> c(x, z);
		for (size_t i = 0; i < x; ++i) {
			for (size_t k = 0; k < y; ++k) {
				const T_& now = a[i][k];
				for (size_t j = 0; j < z; ++j)
					c[i][j] = c[i][j] + now * b[k][j];
			}
		} return c;
	}
	
	template<class T_> Matrix<T_>& Matrix<T_>::operator+= (const Matrix<T_>& b) { return *this = *this + b; }
	template<class T_> Matrix<T_>& Matrix<T_>::operator-= (const Matrix<T_>& b) { return *this = *this - b; }
	template<class T_> Matrix<T_>& Matrix<T_>::operator*= (const T_& k)         { return *this = *this * k; }
	template<class T_> Matrix<T_>& Matrix<T_>::operator*= (const Matrix<T_>& b) { return *this = *this * b; }
}
using namespace std;
using namespace std::atcoder;
using mint = modint998244353;
const int N = 100000, Mod = 998244353;
int n, k;
Matrix<mint> fpow(Matrix<mint> a, int b) {
	if (!b) return Matrix<mint>::identity(1, {1});
	Matrix<mint> c = Matrix<mint>::identity(1, {1});
	for (; b; a *= a, b >>= 1) if (b & 1) c *= a;
	return c;
}
int main() {
	cin >> n >> k;
	Matrix<mint> a(n, 1), b(1, n);
	for (int i = 0; i < n; ++i) { int x; cin >> x; a[i][0] = {x % Mod}; }
	for (int i = 0; i < n; ++i) { int x; cin >> x; b[0][i] = {x % Mod}; }
	if (!k) return cout << n << "\n", 0;
	cout << ((Matrix<mint>(1, n, {1}) * a) * fpow(b * a, k - 1) * (b * Matrix<mint>(n, 1, {1})))[0][0].val() << "\n";
	return 0;
}
