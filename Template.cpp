#include <bits/stdc++.h>

namespace std {

// Array
	template<class T_, size_t N_, T_ DEFAULT_ = T_()>
	class Array {
		T_ val[N_]; size_t ver[N_], clk;
	public:
		Array() { clk = 1; }
		T_& operator[] (size_t i) { if (ver[i] != clk) ver[i] = clk, val[i] = DEFAULT_; return val[i]; }
		void clear() { ++clk; }
	};

// Graph
	template<class T_, size_t N_>
	class Graph {
		inline static size_t psz;
		inline static std::pair<T_, size_t> pool[N_];
		struct iterator {
			size_t now;
			T_& operator* () const { return pool[now].first; }
			bool operator== (iterator it) const { return now == it.now; }
			iterator& operator++ () { now = pool[now].second; return *this; }
		}; size_t head;
	public:
		Graph() { head = 0; }
		iterator begin() const { return {head}; }
		iterator end() const { return {0}; }
		void push_back(const T_& val) { ++psz, this->pool[psz] = {val, head}, head = psz; }
		void clear() { psz = head = 0; }
	};

// Matrix
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

int main() {
	return 0;
}
