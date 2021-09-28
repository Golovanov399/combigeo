#include "pe/geometry/svg.h"

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

using Pt = Point<double>;
const Pt u[3] = {{4, 0}, {2, 1}, {0, 4}};

struct P3d {
	double x, y, z;

	Pt to_2d() const {
		return u[0] * x + u[1] * y + u[2] * z;
	}

	P3d operator -(const P3d& ot) const {
		return {x - ot.x, y - ot.y, z - ot.z};
	}

	P3d operator +(const P3d& ot) const {
		return {x + ot.x, y + ot.y, z + ot.z};
	}

	P3d operator *(double k) const {
		return {x * k, y * k, z * k};
	}

	bool operator ==(const P3d& ot) const {
		return sign(x - ot.x) == 0 && sign(y - ot.y) == 0 && sign(z - ot.z) == 0;
	}

	bool is_zero() const {
		return sign(x) == 0 && sign(y) == 0 && sign(z) == 0;
	}

	double dot(const P3d& p) const {
		return x * p.x + y * p.y + z * p.z;
	}

	P3d cross(const P3d& p) const {
		return {y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x};
	}

	double len() const {
		return sqrt(x * x + y * y + z * z);
	}
};

ostream& operator <<(ostream& ostr, const P3d& p) {
	return ostr << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}

bool contains(vector<P3d> a, P3d p) {
	bool sanity = true;
	for (auto& q : a) {
		q = q - p;
	}
	if ((int)a.size() == 1) {
		sanity = a[0].is_zero();
	} else if ((int)a.size() == 2) {
		sanity = a[0].cross(a[1]).is_zero();
	} else if ((int)a.size() == 3) {
		sanity = sign(a[0].dot(a[1].cross(a[2]))) == 0;
	} else {
		assert(false);
	}
	if (!sanity) {
		return false;
	}
	if ((int)a.size() == 1) {
		return true;
	} else if ((int)a.size() == 2) {
		return sign(a[0].dot(a[1])) < 0;
	} else if ((int)a.size() == 3) {
		return sign(a[0].cross(a[1]).len() + a[1].cross(a[2]).len() + a[2].cross(a[0]).len() - (a[1] - a[0]).cross(a[2] - a[0]).len()) == 0;
	}
	assert(false);
}

// vector<P3d> intersect(vector<P3d> a, vector<P3d> b) {
// 	if (a.size() > b.size()) {
// 		a.swap(b);
// 	}
// 	vector<P3d> res;
// 	if ((int)a.size() == 1) {
// 		if (contains(b, a[0])) {
// 			res.push_back(a[0]);
// 		}
// 	} else if ((int)a.size() == 2) {
// 		if ((int)b.size() == 2) {
// 			auto c = (a[1] - a[0]).cross(b[1] - b[0]);
// 			if (c.is_zero()) {
// 				//
// 			} else {
// 				if (sign(a[0].dot(c) - b[0].dot(c))) {
// 					// pass;
// 				} else {
// 					//
// 				}
// 			}
// 		}
// 	}
// 	return res;
// }

void draw_octa(SVG& svg) {
	vector<pair<int, int>> iss = {{1, 1}, {1, -1}, {0, 1}, {0, -1}, {2, 1}, {2, -1}};
	for (int i = 0; i < (int)iss.size(); ++i) {
		for (int j = i + 1; j < (int)iss.size(); ++j) {
			if (iss[i].first == iss[j].first) {
				continue;
			}
			svg.draw(Segment<double>{u[iss[i].first] * iss[i].second, u[iss[j].first] * iss[j].second}, i ? "black" : "#cccccc", 0.1);
		}
	}
	for (int i = 0; i < 3; ++i) {
		svg.draw(u[i]);
		svg.draw(-u[i]);
	}
}

struct CW {
	vector<vector<P3d>> cells[3];

	void add_cell(const vector<P3d>& pts) {
		cells[(int)pts.size() - 1].push_back(pts);
	}

	bool contains(const P3d& p) const {
		for (const auto& kth : cells) {
			for (const auto& cell : kth) {
				if (::contains(cell, p)) {
					return true;
				}
			}
		}
		return false;
	}

	CW shifted(const P3d& off) const {
		auto res = *this;
		for (auto& kth : res.cells) {
			for (auto& cell : kth) {
				for (auto& p : cell) {
					p = p + off;
				}
			}
		}
		return res;
	}
};

CW intersect(const CW& fst, const CW& snd) {
	const int n = 1 << 3;
	vector<P3d> pts;
	for (const auto& cell : fst.cells[0]) {
		if (snd.contains(cell[0])) {
			pts.push_back(cell[0]);
		}
	}
	for (const auto& cell : fst.cells[1]) {
		for (int i = 1; i < n; ++i) {
			if (auto p = cell[0] * ((double)i / n) + cell[1] * ((double)(n - i) / n); snd.contains(p)) {
				pts.push_back(p);
			}
		}
	}
	for (const auto& cell : fst.cells[2]) {
		for (int i = 1; i < n; ++i) {
			for (int j = 1; i + j < n; ++j) {
				if (auto p = cell[0] * ((double)i / n) + cell[1] * ((double)j / n) + cell[2] * ((double)(n - i - j) / n); snd.contains(p)) {
					pts.push_back(p);
				}
			}
		}
	}

	auto good_dir = [](const P3d& a, const P3d& b) {
		auto c = a - b;
		double cs[3] = {abs(c.x), abs(c.y), abs(c.z)};
		sort(cs, cs + 3);
		return sign(cs[0]) == 0 && sign(cs[1] - cs[2]) == 0;
	};

	CW res;
	vector<P3d> bad;
	for (auto p : pts) {
		res.add_cell({p});
		for (auto q : pts) {
			if (p == q) {
				break;
			}
			if (!good_dir(p, q)) {
				continue;
			}
			if (!snd.contains((p + q) * 0.5)) {
				continue;
			}
			res.add_cell({p, q});
			for (auto r : pts) {
				if (r == p || r == q) {
					continue;
				}
				if (::contains({p, q}, r)) {
					bad.push_back(r);
				}
			}
			for (auto r : pts) {
				if (q == r) {
					break;
				}
				if (!good_dir(p, r) || !good_dir(q, r)) {
					continue;
				}
				if (!snd.contains((p + q) * 0.25 + r * 0.5)) {
					continue;
				}
				if ((q - p).cross(r - p).is_zero()) {
					continue;
				}
				res.add_cell({p, q, r});
				for (auto s : pts) {
					if (s == p || s == q || s == r) {
						continue;
					}
					if (::contains({r, p}, s) || ::contains({r, q}, s) || ::contains({r, p, q}, s)) {
						bad.push_back(s);
					}
				}
			}
		}
	}
	for (auto& kth : res.cells) {
		for (int i = 0; i < (int)kth.size(); ++i) {
			bool ok = true;
			for (auto p : kth[i]) {
				if (find(all(bad), p) != bad.end()) {
					ok = false;
					break;
				}
			}
			if (!ok) {
				// if (kth[i].size() == 1u) {
				// 	cerr << kth[i][0] << " is bad\n";
				// }
				kth.erase(kth.begin() + i);
				--i;
			}
		}
	}
	return res;
}

CW octahedron(double r) {
	CW res;
	for (int i : {-1, 0, 1}) {
		for (int j : {-1, 0, 1}) {
			for (int k : {-1, 0, 1}) {
				vector<P3d> pts;
				if (i) {
					pts.push_back({i * r, 0, 0});
				}
				if (j) {
					pts.push_back({0, j * r, 0});
				}
				if (k) {
					pts.push_back({0, 0, k * r});
				}
				if (!pts.empty()) {
					res.add_cell(pts);
				}
			}
		}
	}
	return res;
}

void draw_cw(SVG& svg, const CW& cw) {
	for (int i = 2; i >= 0; --i) {
		for (const auto& cell : cw.cells[i]) {
			vector<Pt> to_draw;
			for (auto p : cell) {
				to_draw.push_back(p.to_2d());
			}
			if (cell.size() == 3u) {
				auto n = (cell[1] - cell[0]).cross(cell[2] - cell[0]);
				ld alpha = abs(n.y) / n.len() * 0.5;
				svg.polyline(to_draw, "blue", "none", 0.1, alpha);
			} else if (cell.size() == 2u) {
				svg.polyline(to_draw, "none", "blue", 0.1, 0.5);
			} else if (cell.size() == 1u) {
				svg.draw(to_draw[0], 0.1, "blue", "none", 0.5, 0.5);
			} else {
				assert(false);
			}
		}
	}
}

int main() {
	SVG svg;
	draw_octa(svg);

	CW cw = octahedron(1);
	cw = intersect(cw, octahedron(2).shifted({-1, 0, 0}));

	cw = intersect(cw, octahedron(1).shifted({0.5, 0, 0.5}));
	cw = intersect(cw, octahedron(2).shifted({0, 0, 1}));
	for (auto& kth : cw.cells) {
		for (auto& cell : kth) {
			for (auto& p : cell) {
				p = (p - P3d{1, 0, 0}) * 2 + P3d{1, 0, 0};
			}
		}
	}

	cw = intersect(cw, octahedron(1).shifted({0.5, -0.5, 0}));
	cw = intersect(cw, octahedron(2).shifted({0, -1, 0}));
	for (auto& kth : cw.cells) {
		for (auto& cell : kth) {
			for (auto& p : cell) {
				p = (p - P3d{1, 0, 0}) * 2 + P3d{1, 0, 0};
			}
		}
	}

	// cw = intersect(cw, octahedron(1).shifted({1./2, 1./4, -1./4}));
	// cw = intersect(cw, octahedron(2).shifted({1, 0, 0}));
	cw = intersect(cw, octahedron(1).shifted({0.5, 0.5, 0}));
	cw = intersect(cw, octahedron(2).shifted({0, 1, 0}));
	for (auto& kth : cw.cells) {
		for (auto& cell : kth) {
			for (auto& p : cell) {
				p = (p - P3d{1, 0, 0}) * 2 + P3d{1, 0, 0};
			}
		}
	}

	cw = intersect(cw, octahedron(1).shifted({0.5, 0, -0.5}));
	cw = intersect(cw, octahedron(2).shifted({0, 0, -1}));
	draw_cw(svg, cw);

	svg.save("out.svg");

	return 0;
}