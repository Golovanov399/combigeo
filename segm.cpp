#include "pe/geometry/primitives/all.h"

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

// #define REGIONS

int main() {
	vector<Pt> layer[3];
	layer[0].push_back({0, 0});
	for (int i = 0; i < 2; ++i) {
		if (i != 2) {
			layer[1].push_back(u.rotated(deg(30 + 120 * i)));
		}
	}
	layer[2].push_back(u.rotated(deg(30)) + u.rotated(deg(85)));
	layer[2].push_back(u.rotated(deg(150)) + u.rotated(deg(95)));

	cout << R"qwe(r = 1cm;
R = 4r;
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

	for (int i = 0; i < 3; ++i) {
		cout << "for i := 0 step 1 until " << (int)layer[i].size() - 1 << ":\n" << 
				"  fill big shifted d[" << i << "][i] withcolor .9 * white;" <<
				"endfor;\n\n";
	}
	for (int i = 0; i < 3; ++i) {
		cout << "for i := 0 step 1 until " << (int)layer[i].size() - 1 << ":\n" << 
				"  draw small shifted d[" << i << "][i];" <<
				"  pickup pencircle scaled 0.25;\n" <<
				// "  draw big shifted d[" << i << "][i] dashed evenly scaled 0.5;\n" <<
				"  pickup pencircle scaled 0.5;\n" <<
				"endfor;\n\n";
	}
	cout << "\nfill small withcolor .7 * white;\n";

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

	Pt nw = layer[1][1] + (layer[2][1] - layer[1][1]).rotated(deg(60));
	cout << "\npickup pencircle scaled 0.5;\n";
	cout << "draw small shifted ((" << nw.x << ", " << nw.y << ") scaled r);\n";
	cout << "pickup pencircle scaled 0.25;\n";
	cout << "draw big shifted ((" << nw.x << ", " << nw.y << ") scaled r) dashed evenly scaled 0.5;\n";

	vector<Circle<ld>> circles[3];
	vector<Circle<ld>> all_circles;
	for (int i = 0; i < 3; ++i) {
		for (const auto& p : layer[i]) {
			circles[i].push_back({p, 1.});
			all_circles.push_back(circles[i].back());
		}
	}

	/*cout << "pickup pencircle;\n";
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < (int)layer[i].size(); ++j) {
			const auto& circle = circles[i][j];
			vector<ld> angles;
			for (const auto& c : all_circles) {
				auto tmp = circle.intersect(c);
				for (const auto& p : tmp) {
					angles.push_back(atan2(p.y - layer[i][j].y, p.x - layer[i][j].x));
				}
			}
			sort(all(angles));
			for (int k = 0; k < (int)angles.size(); ++k) {
				ld alpha = angles[k];
				ld beta = angles[(k + 1) % (int)angles.size()];
				if (beta < alpha) {
					beta += 2 * pi;
				}
				ld mid = (alpha + beta) / 2;
				Pt cand = layer[i][j] + u.rotated(mid);

				bool covered = false;
				for (const auto& c : all_circles) {
					if (sign(dist(c.p, cand) - c.r) < 0) {
						covered = true;
						break;
					}
				}

				if (!covered) {
					vector<pair<ld, ld>> bes;
					if (alpha < 0) {
						alpha += 2 * pi;
						beta += 2 * pi;
					}
					if (beta < 2 * pi) {
						bes.push_back({alpha, beta});
					} else {
						bes.push_back({alpha, 2 * pi});
						bes.push_back({0, beta - 2 * pi});
					}
					for (auto [b, e] : bes) {
						if (sign(e - b) > 0) {
#ifdef REGIONS
							cout << "draw subpath(" << b * 4 / pi << ", " << e * 4 / pi << ") of (big shifted d[" << i << "][" << j << "]) withcolor .5 * white;\n";
#else
							cout << "draw subpath(" << b * 4 / pi << ", " << e * 4 / pi << ") of (big shifted d[" << i << "][" << j << "]) withcolor .3 * white;\n";
#endif
						}
					}
				}
			}
		}
	}*/

	return 0;
}