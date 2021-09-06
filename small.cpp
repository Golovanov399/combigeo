#include "pe/geometry/primitives/all.h"
#include "pe/geometry/polygon.h"

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

using Pt = Point<ld>;

const ld pi = acosl(-1);
const Pt u = {1., 0.};

ld deg(int degs) {
	return degs * pi / 180;
}

int main() {
	vector<Pt> layer[3];
	layer[0].push_back({0, 0});
	ld psi = deg(130);
	ld v1u2 = deg(90);
	ld u1v2 = deg(90);
	layer[1].push_back(u.rotated(pi / 2 - psi / 2));
	layer[1].push_back(u.rotated(pi / 2 + psi / 2));
	layer[2].push_back(layer[1][0] + u.rotated(pi / 2 + psi / 2 - v1u2));
	layer[2].push_back(layer[1][1] + u.rotated(pi / 2 - psi / 2 + u1v2));

	cout << "% ld psi = deg(" << psi / pi * 180 << ");\n";
	cout << "% ld v1u2 = deg(" << v1u2 / pi * 180 << ");\n";
	cout << "% ld u1v2 = deg(" << u1v2 / pi * 180 << ");\n";

	cout << "numeric r;\n";
	cout << R"qwe(r = 1.5cm;
% R = 4r;
% pair u;
% u = (r, 0);

path small, big;
small = fullcircle scaled r;
big = fullcircle scaled (2 * r);

pair d[][];
)qwe";

	cout << setprecision(6) << fixed;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < (int)layer[i].size(); ++j) {
			cout << "d[" << i << "][" << j << "] = (" << layer[i][j].x << ", " << layer[i][j].y << ") scaled r;\n";
		}
	}

	// for (int i = 0; i < 3; ++i) {
	// 	cout << "for i := 0 step 1 until " << (int)layer[i].size() - 1 << ":\n" << 
	// 			"  fill big shifted d[" << i << "][i] withcolor .9 * white;" <<
	// 			"endfor;\n\n";
	// }
	for (int i = 0; i < 3; ++i) {
		cout << "for i := 0 step 1 until " << (int)layer[i].size() - 1 << ":\n" << 
				"  draw small shifted d[" << i << "][i];" <<
				"  pickup pencircle scaled 0.25;\n" <<
				"  draw big shifted d[" << i << "][i] dashed evenly scaled 0.5;\n" <<
				"  pickup pencircle scaled 0.5;\n" <<
				"endfor;\n\n";
	}
	// cout << "\nfill small withcolor .7 * white;\n";

	cout << "pickup pencircle;\n";
	for (int i = 1; i < 3; ++i) {
		for (int j = 0; j < (int)layer[i].size(); ++j) {
			int idx = 0;
			while (sign(dist(layer[i][j], layer[i - 1][idx]) - 1) != 0) {
				++idx;
			}
			cout << "drawarrow d[" << i - 1 << "][" << idx << "]--d[" << i << "][" << j << "];\n";
		}
	}

	cout << "for i := 0 step 1 until 1:\n" <<
  			"draw d[2][i]--(d[2][i] scaled (1 + 2.1 * r / 2 / abs(d[2][i])));\n" <<
			"endfor;\n";

	vector<Circle<ld>> circles[3];
	vector<Circle<ld>> all_circles;
	for (int i = 0; i < 3; ++i) {
		for (const auto& p : layer[i]) {
			circles[i].push_back({p, 1.});
			all_circles.push_back(circles[i].back());
		}
	}

	Polygon<ld> region({layer[2][0] + layer[2][0] / layer[2][0].len() * 10, layer[2][0], layer[1][0], layer[0][0], layer[1][1], layer[2][1], layer[2][1] + layer[2][1] / layer[2][1].len() * 10});
	vector<vector<char>> is_involved(3);
	for (int i = 0; i < 3; ++i) {
		is_involved[i].resize(layer[i].size());
		for (int j = 0; j < (int)layer[i].size(); ++j) {
			int cnt = 0;
			vector<Point<ld>> cands;
			for (const auto& c : all_circles) {
				if (c.p != circles[i][j].p) {
					auto pts = c.intersect(circles[i][j]);
					for (auto p : pts) {
						if (region.is_inside(p)) {
							cands.push_back(p);
						}
					}
				}
			}
			make_unique(cands);
			for (auto p : cands) {
				bool good = true;
				for (auto c : all_circles) {
					if (sign(dist(c.p, p) - 1) < 0) {
						good = false;
					}
				}
				if (good) {
					++cnt;
				}
			}
			is_involved[i][j] = (cnt > 1);
		}
	}
	fill(all(is_involved[2]), true);
	vector<pair<int, int>> seq = {{2, 0}, {1, 0}, {0, 0}, {1, 1}, {2, 1}};
	{
		decltype(seq) tmp;
		for (auto p : seq) {
			if (is_involved[p.first][p.second]) {
				tmp.push_back(p);
			}
		}
		seq.swap(tmp);
	}
	for (int i = 0; i < (int)seq.size() - 1; ++i) {
		auto [x1, y1] = seq[i];
		auto [x2, y2] = seq[i + 1];
		for (int j : {i, i + 1}) {
			cout << "drawarrow d[" << seq[j].first << "][" << seq[j].second << "]--((big shifted d[" << x1 << "][" << y1 << "]) intersectionpoint (big shifted d[" << x2 << "][" << y2 << "])) dashed evenly;\n";
		}
	}
	cout << "\npickup pencircle scaled 1.5;\n";
	for (int i = 0; i < (int)seq.size(); ++i) {
		auto [x, y] = seq[i];
		Point<ld> l = i ? circles[seq[i - 1].first][seq[i - 1].second].intersect(circles[x][y])[0] : layer[x][y] * (1 + 1 / layer[x][y].len());
		Point<ld> r = i < (int)seq.size() - 1 ? circles[seq[i + 1].first][seq[i + 1].second].intersect(circles[x][y])[1] : layer[x][y] * (1 + 1 / layer[x][y].len());
		ld alpha = atan2(l.y - layer[x][y].y, l.x - layer[x][y].x);
		ld beta = atan2(r.y - layer[x][y].y, r.x - layer[x][y].x);
		while (alpha < 0) {
			alpha += 2 * pi;
		}
		while (beta < alpha) {
			beta += 2 * pi;
		}
		vector<pair<ld, ld>> angs;
		if (beta > 2 * pi) {
			angs.push_back({alpha, 2 * pi});
			angs.push_back({0, beta - 2 * pi});
		} else {
			angs.push_back({alpha, beta});
		}
		for (auto [al, be] : angs) {
			cout << "draw subpath(" << al * 4 / pi << ", " << be * 4 / pi << ") of (big shifted d[" << x << "][" << y << "]) withcolor .3 * white;\n";
		}
	}

// 	cout << "pickup pencircle;\n";
// 	for (int i = 0; i < 3; ++i) {
// 		for (int j = 0; j < (int)layer[i].size(); ++j) {
// 			const auto& circle = circles[i][j];
// 			vector<ld> angles;
// 			for (const auto& c : all_circles) {
// 				auto tmp = circle.intersect(c);
// 				for (const auto& p : tmp) {
// 					angles.push_back(atan2(p.y - layer[i][j].y, p.x - layer[i][j].x));
// 				}
// 			}
// 			sort(all(angles));
// 			for (int k = 0; k < (int)angles.size(); ++k) {
// 				ld alpha = angles[k];
// 				ld beta = angles[(k + 1) % (int)angles.size()];
// 				if (beta < alpha) {
// 					beta += 2 * pi;
// 				}
// 				ld mid = (alpha + beta) / 2;
// 				Pt cand = layer[i][j] + u.rotated(mid);

// 				bool covered = false;
// 				for (const auto& c : all_circles) {
// 					if (sign(dist(c.p, cand) - c.r) < 0) {
// 						covered = true;
// 						break;
// 					}
// 				}

// 				if (!covered) {
// 					vector<pair<ld, ld>> bes;
// 					if (alpha < 0) {
// 						alpha += 2 * pi;
// 						beta += 2 * pi;
// 					}
// 					if (beta < 2 * pi) {
// 						bes.push_back({alpha, beta});
// 					} else {
// 						bes.push_back({alpha, 2 * pi});
// 						bes.push_back({0, beta - 2 * pi});
// 					}
// 					for (auto [b, e] : bes) {
// 						if (sign(e - b) > 0) {
// #ifdef REGIONS
// 							cout << "draw subpath(" << b * 4 / pi << ", " << e * 4 / pi << ") of (big shifted d[" << i << "][" << j << "]) withcolor .5 * white;\n";
// #else
// 							cout << "draw subpath(" << b * 4 / pi << ", " << e * 4 / pi << ") of (big shifted d[" << i << "][" << j << "]) withcolor .3 * white;\n";
// #endif
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}

	return 0;
}