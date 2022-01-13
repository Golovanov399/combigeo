#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

const int D = 4;
const int need_mod = 2;

inline int is_ok(int x) {
	return x % (2 * need_mod) == need_mod;
}

using Point = array<int, D>;

ostream& operator <<(ostream& ostr, const Point& p) {
	ostr << "(";
	for (int i = 0; i < D; ++i) {
		if (i) {
			ostr << ", ";
		}
		ostr << p[i];
	}
	return ostr << ")";
}

template <typename T>
ostream& operator <<(ostream& ostr, const vector<T>& v) {
	ostr << "[";
	for (int i = 0; i < (int)v.size(); ++i) {
		if (i) {
			ostr << ", ";
		}
		ostr << v[i];
	}
	return ostr << "]";
}

int d(const Point& p, const Point& q) {
	int ans = 0;
	for (int i = 0; i < 3; ++i) {
		ans += abs(p[i] - q[i]);
	}
	return ans;
}

const int L = D;

const auto pts = []() {
	vector<Point> res;
	Point p;
	iota(all(p), 1);
	do {
		res.push_back(p);
		for (int i = 1; i < (1 << D); ++i) {
			p[__builtin_ctz(i)] *= -1;
			res.push_back(p);
		}
		p.back() *= -1;
	} while (next_permutation(all(p)));
	// for (int i = -L; i <= L; ++i) {
	// 	for (int j = -L; j <= L; ++j) {
	// 		for (int k = -L; k <= L; ++k) {
	// 			for (int l = -L; l <= L; ++l) {
	// 				if (is_ok(d({}, {i, j, k, l}))) {
	// 					res.push_back({i, j, k, l});
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// reverse(all(res));
	return res;
}();

const int sz = 24 << D;
using Bs = bitset<sz>;
vector<Bs> bs(sz);

int mx = 0;
// vector<Point> st = {{}};
vector<Point> st;
void rec(Bs b) {
	if ((int)st.size() > mx) {
		cerr << st << "\n";
		mx = st.size();
		// if (mx == 8) {
		// 	for (int i = 0; i < mx; ++i) {
		// 		for (int j = 0; j < mx; ++j) {
		// 			cerr << d(st[i], st[j]) / need_mod << " ";
		// 		}
		// 		cerr << "\n";
		// 	}
		// }
	}
	for (int i = b._Find_first(); i < sz; i = b._Find_next(i)) {
		st.push_back(pts[i]);
		rec(b & bs[i]);
		st.pop_back();
	}
}

int main() {
	for (int i = 0; i < (int)pts.size(); ++i) {
		bs[i] = {};
		for (int j = 0; j < (int)pts.size(); ++j) {
			if (is_ok(d(pts[i], pts[j]))) {
				bs[i].set(j);
			}
		}
	}
	Bs b = {};
	for (int i = 0; i < (int)pts.size(); ++i) {
		b.set(i);
	}
	rec(b);

	return 0;
}
