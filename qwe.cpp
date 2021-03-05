#include "pe/geometry/all.h"
#include "pe/base/ostream.h"

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

const ld pi = acosl(-1);

mt19937 rr;
uniform_real_distribution gen;

ld get_radius(int cnt) {
	return 1 / tan(pi / cnt) - sqrt(3);
}

int main() {
	SVG svg;
	svg.draw(Circle<ld>{{0, 0}, 1}, "blue", "black", .1);

	vector<Circle<ld>> layer;
	auto draw_layer = [&]() {
		for (auto c : layer) {
			svg.draw(c, "gray", "black", .1);
		}
	};
	auto create_circle = [&](int cur) {
		layer = {};
		ld r = 1 / sin(pi / cur);
		for (int i = 0; i < cur; ++i) {
			layer.push_back({{cos(2 * pi / cur * i) * r, sin(2 * pi / cur * i) * r}, 1});
		}
	};

	const ld a = 1.3;
	int cur = 300;

	create_circle(cur);
	draw_layer();
	int len = floor((layer[0].p.len() * (a - 1)) - 1);
	create_circle(floor(pi * (layer[0].p.len() + 2 * (len + 1))));
	draw_layer();
	vector<Circle<ld>> nw;

	vector<pair<int, int>> segs = {{0, 0}};
	for (int i = 0; i < cur; ++i) {
		int l = i * (ld)layer.size() / cur;
		int r = (i + 1) * (ld)layer.size() / cur;
		assert(r == l + 1 || r == l + 2);
		if (r == l + 2) {
			auto rd = get_radius(layer.size());
			ld phi = pi * 2 * (l + 0.5) / layer.size();
			nw.push_back(Circle<ld>{{cos(phi) * rd, sin(phi) * rd}, 1});
		} else {
			if (segs.back().second == l) {
				segs.back().second = r;
			} else {
				segs.push_back({l, r});
			}
		}
	}
	for (auto [l, r] : segs) {
		ld phi = pi * (l + r - 1) / layer.size();
		for (int i = l; i < r; ++i) {
			nw.push_back(Circle<ld>{layer[i].p - Point<ld>{cos(phi), sin(phi)} * 2, 1});
		}
		// ld phi1 = 2 * pi / layer.size() * (l - 1.5);
		// ld phi2 = 2 * pi / layer.size() * (r + 0.5);
		// for (int i = l; i < r; ++i) {
		// 	ld phi = phi1 + (phi2 - phi1) / (r - l + 1) * (i - l + 1);
		// 	ld alpha = phi - 2 * pi / layer.size() * i;
		// 	ld rd = 1 / sin(pi / layer.size());
		// 	ld x = -sqrt(4 - rd * rd * sin(alpha) * sin(alpha)) + rd * cos(alpha);
		// 	assert(sign(x * x + rd * rd - 2 * x * rd * cos(alpha) - 4) == 0);
		// 	// cerr << rd << " " << alpha << " " << x << " | ";
		// 	nw.push_back(Circle<ld>{{x * cos(phi), x * sin(phi)}, 1.});
		// }
	}

	// int len = ceil((get_radius(layer.size()) - 1 / sin(pi / cur)) / 2) - 1;
	sort(all(nw), [](const Circle<ld>& p, const Circle<ld>& q) {
		return atan2(-p.p.y, -p.p.x) < atan2(-q.p.y, -q.p.x);
	});
	draw_layer();

	// nw.swap(layer);
	// draw_layer();
	// nw.swap(layer);

	create_circle(cur);
	assert((int)nw.size() == cur);
	// for (int i = 0; i < cur; ++i) {
	// 	svg.draw(Segment<ld>{layer[i].p, nw[i].p}, "black", .1);
	// }

	/*for (int i = 0; i < cur; ++i) {
		ld d = dist(layer[i].p, nw[i].p);
		assert(sign(d - 2 * (len + 1)) < 0);
		ld le = d / 2, ri = 1e9;
		for (int it = 0; it < 50; ++it) {
			ld mid = (le + ri) / 2;
			ld phi = asin(1 / mid);
			if (mid * sin((len + 1) * phi) < d / 2) {
				le = mid;
			} else {
				ri = mid;
			}
		}
		Point<ld> center = (layer[i].p + nw[i].p) / 2;
		ld rd = (le + ri) / 2;
		ld opp = sqrtl(rd * rd - (center - nw[i].p).sqr());
		center += (layer[i].p - nw[i].p).rotated(pi / 2) / (layer[i].p - nw[i].p).len() * opp;
		ld phi = asin(1 / rd) * 2;
		for (int j = 0; j <= len; ++j) {
			svg.draw(Circle<ld>{center + (nw[i].p - center).rotated(phi * j), 1.}, "gray", "black", .1);
		}
	}*/

	/*for (int j = 0; j < len + 1; ++j) {
		for (auto c : nw) {
			svg.draw(c, "gray", "black", .1);
		}
		if (j == len) {
			break;
		}
		vector<Circle<ld>> nnw;
		for (int i = 0; i < cur; ++i) {
			auto cp = Circle<ld>{layer[i].p, (len - j) * 2.};
			auto cq = Circle<ld>{nw[i].p, 2.};
			assert(cp.intersects(cq));
			auto pt = cp.intersect(cq)[0];
			if (Circle<ld>{pt, 1.}.strictly_intersects(nw[(i + cur - 1) % cur])) {
				pt = cq.intersect(Circle<ld>{nw[(i + cur - 1) % cur].p, 2.})[0];
			}
			nnw.push_back({pt, 1.});
		}
		nw.swap(nnw);
	}*/

	for (auto c : nw) {
		svg.draw(c, "gray", "black", .1);
	}
	for (int i = 0; i < cur; ++i) {
		// svg.draw(Segment<ld>{layer[i].p, nw[i].p}, "black", .1);
		auto p = layer[i].p;
		auto q = nw[i].p;
		auto cp = Circle<ld>{p, (len - 1) * 2.};
		auto cq = Circle<ld>{q, 2.};
		assert(cp.intersects(cq));
		auto r = cp.intersect(cq)[0];
		for (int j = 0; j < (len - 1); ++j) {
			svg.draw(Circle<ld>{r + (p - r) / (len - 1) * j, 1}, "gray", "black", .1);
		}
	}

	svg.save("out.svg");
 
	return 0;
}