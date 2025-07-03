#include <bits/stdc++.h>
using namespace std;
namespace std {
#ifndef Int_Digit
#define Int_Digit 4
#endif
#define Int_DigitLen Int_Digit
#define Int_DigitMod (int)pow(10, Int_DigitLen)
	inline size_t digit_count(int x) {
		size_t cnt = 0;
		while (x) ++cnt, x /= 10;
		return cnt;
	}
	inline int digit_mod(const int &x) {
		return (x % Int_DigitMod + Int_DigitMod) % Int_DigitMod;
	}
	inline int digit_overflow(const int &x) {
		if (x >= Int_DigitMod) return x / Int_DigitMod;
		if (x < 0) return x / Int_DigitMod - (x % Int_DigitMod ? 1 : 0);
		return 0;
	}
	class Int {
	private:
		bool _sign;
		vector<int> _digit;
	protected:
		inline void _init() {
			_sign = false, _digit.clear();
			_adjust();
		}
		inline void _init(const bool &sign, const vector<int> &digit) {
			_sign = sign, _digit = digit;
			_adjust();
		}
		inline void _init(const Int &b) {
			_sign = b._sign, _digit = b._digit;
			_adjust();
		}
		inline void _init(const string &b) {
			_sign = false, _digit.clear();
			_convert(b);
			_adjust();
		}
		template<typename T>
		inline void _init(const T &b) {
			_sign = false, _digit.clear();
			_convert(to_string(b));
			_adjust();
		}
		inline void _adjust() {
			if (!_digit.empty())
				for (size_t i = _digit.size() - 1; i > 0; --i) {
					int overflow = digit_overflow(_digit[i]);
					_digit[i - 1] += overflow;
					_digit[i] -= overflow * Int_DigitMod;
				}
			while (!_digit.empty() && _digit.front() == 0)
				_digit.erase(_digit.begin());
			if (_digit.empty())
				_digit.push_back(0), _sign = false;
		}
		inline bool _convert(string s) {
			if (s.front() == '-') {
				_sign = true;
				s.erase(s.begin());
			}
			for (const char &c : s) if (!isdigit(c)) return true;
			stack<int> stk;
			while (!s.empty()) {
				string t = (s.size() >= Int_DigitLen) ? s.substr(s.size() - Int_DigitLen) : s;
				s.erase(s.size() - t.size());
				stk.push(stoll(t));
			}
			while (!stk.empty())
				_digit.push_back(stk.top()), stk.pop();
			return false;
		}
		inline bool _check0() const {
			return (_digit.front() == 0);
		}
	public:
		inline string convert() const;
		Int() { _init(); }
		Int(const bool &sign, const vector<int> &digit) { _init(sign, digit); }
		Int(const Int &b) { _init(b); }
		Int(const string &b) { _init(b); }
		template<typename T>
		Int(const T &b) { _init(b); }
		
		friend void debug();
		
		friend istream& operator >> (istream &in, Int &dat);
		friend ostream& operator << (ostream &out, const Int &dat);
		friend Int Int_AddByDigit(const Int &a, const Int &b);
		friend Int Int_SubtractByDigit(const Int &a, const Int &b);
		friend Int Int_MultiplyByDigit(const Int &a, const Int &b);
		friend int Int_CompareByDigit(const Int &a, const Int &b);
		// 比较运算符
		friend bool operator == (const Int &a, const Int &b);
		friend bool operator != (const Int &a, const Int &b);
		friend bool operator < (const Int &a, const Int &b);
		friend bool operator > (const Int &a, const Int &b);
		friend bool operator <= (const Int &a, const Int &b);
		friend bool operator >= (const Int &a, const Int &b);
		// 算术运算符
		friend Int operator + (const Int &a);
		friend Int operator - (const Int &a);
		friend Int operator + (const Int &a, const Int &b);
		friend Int operator - (const Int &a, const Int &b);
		friend Int operator * (const Int &a, const Int &b);
		// 自增自减运算符
		friend Int& operator ++ (Int &a);
		friend Int& operator -- (Int &a);
		friend Int operator ++ (Int &a, int);
		friend Int operator -- (Int &a, int);
		// 赋值运算符，类内定义
		template<typename T>
		Int& operator = (const T &b);
		Int& operator += (const Int &b);
		Int& operator -= (const Int &b);
	};
	istream& operator >> (istream &cin, Int &dat) {
		string _buf; cin >> _buf;
		dat._convert(_buf);
		dat._adjust();
		return cin;
	}
	ostream& operator << (ostream &cout, const Int &dat) {
		cout << dat.convert();
		return cout;
	}
	inline string Int::convert() const {
		string res;
		if (_check0()) res = "0";
		else {
			if (_sign) res = "-";
			for (auto u = _digit.begin(); u != _digit.end(); u++) {
				const auto& dgt = *u;
				if (u != _digit.begin())
					res += string(Int_DigitLen - digit_count(dgt), '0');
				if (digit_count(dgt))
					res += to_string(dgt);
			}
		} return res;
	}
	// 要保证 Length(a) > Length(b)
	Int Int_AddByDigit(const Int &a, const Int &b) {
		size_t A = a._digit.size(), B = b._digit.size(), C = A + 1;
		Int c; c._digit.resize(C);
		size_t i = A - 1, j = B - 1, k = -1;
		while (0 <= i && i < A) {
			k = C - A + i; // = C - B + j = i + 1
			c._digit[k] = a._digit[i] + (0 <= j && j < B ? b._digit[j] : 0);
			--i, --j;
		}
		c._adjust();
		return c;
	}
	// 要保证 Length(a) > Length(b)
	Int Int_SubtractByDigit(const Int &a, const Int &b) {
		size_t A = a._digit.size(), B = b._digit.size(), C = A + 1;
		Int c; c._digit.resize(C);
		size_t i = A - 1, j = B - 1, k = -1;
		while (0 <= i && i < A) {
			k = C - A + i;
			c._digit[k] = a._digit[i] - (0 <= j && j < B ? b._digit[j] : 0);
			--i, --j;
		}
		c._adjust();
		return c;
	}
	Int Int_MultiplyByDigit(const Int &a, const Int &b) {
		Int c; int carry = 0;
		c._digit.resize(a._digit.size() + b._digit.size());
		for (size_t i = 0; i < a._digit.size(); ++i)
			for (size_t j = 0; j < b._digit.size(); ++j)
				c._digit[i + j + 1] = a._digit[i] * b._digit[j];
		for (size_t i = c._digit.size() - 1; i >= 0; --i) {
			c._digit[i] += carry;
			carry = c._digit[i] / Int_DigitMod;
			c._digit[i] %= Int_DigitMod;
		}
		return c;
	}
	int Int_CompareByDigit(const Int &a, const Int &b) {
		if (a._digit.size() < b._digit.size()) return -1;
		if (a._digit.size() > b._digit.size()) return 1;
		size_t A = a._digit.size(), B = b._digit.size();
		size_t i = A - 1, j = B - 1;
		while (0 <= i && i < A) {
			if (a._digit[i] < b._digit[j]) return -1;
			if (a._digit[i] > b._digit[j]) return 1;
			--i, --j;
		}
		return 0;
	}
	// 比较运算符
	bool operator == (const Int &a, const Int &b) {
		return a._sign == b._sign && Int_CompareByDigit(a, b) == 0;
	}
	bool operator != (const Int &a, const Int &b) {
		return !operator==(a, b);
	}
	bool operator < (const Int &a, const Int &b) {
		if (a._sign != b._sign) return a._sign;
		if (!a._sign) return Int_CompareByDigit(a, b) < 0;
		else return Int_CompareByDigit(a, b) > 0;
	}
	bool operator > (const Int &a, const Int &b) {
		if (a._sign != b._sign) return !a._sign;
		if (!a._sign) return Int_CompareByDigit(a, b) > 0;
		else return Int_CompareByDigit(a, b) < 0;
	}
	bool operator <= (const Int &a, const Int &b) {
		return !operator>(a, b);
	}
	bool operator >= (const Int &a, const Int &b) {
		return !operator<(a, b);
	}
	// 算数运算符
	Int operator + (const Int &a) {
		return Int(false, a._digit);
	}
	Int operator - (const Int &a) {
		return Int(true, a._digit);
	}
	Int operator + (const Int &a, const Int &b) {
		int compres = Int_CompareByDigit(a, b); // compres = compare result
		if (a._sign == b._sign) {
			return (compres >= 0) ? Int(a._sign, Int_AddByDigit(a, b)._digit) : Int(a._sign, Int_AddByDigit(b, a)._digit);
		} else {
			return (compres >= 0) ? Int(a._sign, Int_SubtractByDigit(a, b)._digit) : Int(b._sign, Int_SubtractByDigit(b, a)._digit);
		}
		return Int();
	}
	Int operator - (const Int &a, const Int &b) {
		return operator+(a, operator-(b));
	}
	// 自增自减运算符
	Int& operator ++ (Int &a) {
		a = operator+(a, Int(1));
		return a;
	}
	Int& operator -- (Int &a) {
		a = operator-(a, Int(1));
		return a;
	}
	Int operator ++ (Int &a, int) {
		a = operator+(a, Int(1));
		return a;
	}
	Int operator -- (Int &a, int) {
		a = operator-(a, Int(1));
		return a;
	}
	// 赋值运算符
	template<typename T>
	Int& Int::operator = (const T &b) {
		_init(b);
		return *this;
	}
	Int& Int::operator += (const Int &b) {
		_init(operator+(*this, b));
		return *this;
	}
	Int& Int::operator -= (const Int &b) {
		_init(operator-(*this, b));
		return *this;
	}
}

random_device seed;
mt19937 randx(114514);

void gen(string& s) {
	int m = randx() % 100000 + 1;
	s.push_back(randx() % 9 + '1');
	for (int i = 1; i < m; i++) s.push_back(randx() % 10 + '0');
}

int main() {
	int n = 50;
	puts("YS");
	for (int i = 1; i <= n; i++) {
		string s; gen(s);
//		cout << s << "\n";
		Int a(s);
//		cout << s << "\n" << a << "\n" << s.size() << " " << a.convert().size() << "\n\n";
		if (s != a.convert()) system("pause > nul");
	}
	return 0;
}
