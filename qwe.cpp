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
	vector<Circle<ld>> layer;
	svg.draw(Circle<ld>{{0, 0}, 1}, "blue", "black", .1);
	for (int i = 0; i < 6; ++i) {
		layer.push_back({{2 * cos(pi / 3 * i), 2 * sin(pi / 3 * i)}, 1});
	}
	for (auto c : layer) {
		svg.draw(c, "gray", "black", .1);
	}

	int k = 1;
	int total = 6;
	bool need = true;
	while ((int)layer.size() <= 6 * k) {
		if (need) {
			vector<Circle<ld>> nw;
			for (auto [p, c] : layer) {
				nw.push_back({p + (p / p.len()).rotated(-pi / 6) * 2 * c, c});
				nw.push_back({p + (p / p.len()).rotated(pi / 6) * 2 * c, c});
			}
			nw.swap(layer);
			need = false;
		} else if (sign(layer[0].p.len() + 2 - get_radius(2 * layer.size())) >= 0) {
			vector<Circle<ld>> nw;
			nw.push_back(Circle<ld>{Circle<ld>{layer[0].p, 2}.intersect(Circle<ld>{{0, 0}, get_radius(2 * layer.size())})[0], 1});
			for (int i = 1; i < (int)layer.size(); ++i) {
				auto q = nw.back().p.rotated(2 * pi / layer.size());
				nw.push_back(Circle<ld>{q, 1});
			}
			nw.swap(layer);
			need = true;
		} else {
			for (auto& c : layer) {
				c.p = c.p * (1 + 2 / (c.p.len()));
			}
		}
		k += 1;
		for (auto c : layer) {
			svg.draw(c, "gray", "black", .1);
		}
		total += layer.size();
		if (k >= 100) {
			cerr << ":(\n";
			break;
		}
	}
	cerr << k << ": " << layer.size() << "\n";

	while (total <= 3 * k * (k + 1)) {
		cerr << 3 * k * (k + 1) - total << " ";
		vector<Circle<ld>> boundary;
		for (auto [p, r] : layer) {
			boundary.push_back({p, 2 * r});
		}
		layer.clear();
		Point<ld> pt = {0, 0};
		for (auto [p, r] : boundary) {
			pt = max(pt, {p.x + r, p.y});
		}
		int i = 0;
		while (sign(dist(boundary[i].p, pt) - boundary[i].r)) {
			++i;
		}
		pt = (pt - boundary[i].p).rotated(pi / 6 * gen(rr)) + boundary[i].p;
		layer.push_back({pt, 1});
		while (true) {
			if ((int)boundary.size() > 1) {
				while (true) {
					auto vec = boundary[i].intersect(boundary[(i + 1) % boundary.size()]);
					auto p = *max_element(all(vec), [](const Point<ld>& p1, const Point<ld>& p2) {
						return p1.sqr() < p2.sqr();
					});
					if (sign(2 - dist(pt, p)) >= 0) {
						i = (i + 1) % boundary.size();
					} else {
						break;
					}
				}
			}
			auto vec = boundary[i].intersect({pt, 2});
			auto p = vec[0];
			if (sign(cross(pt - boundary[i].p, p - boundary[i].p)) < 0) {
				p = vec[1];
			}
			if (layer[0].strictly_intersects({p, 1})) {
				break;
			} else {
				pt = p;
				layer.push_back({pt, 1});
			}
		}
		for (auto c : layer) {
			svg.draw(c, "gray", "black", .1);
		}
		total += layer.size();
		k += 1;
	}
	cerr << k << " layers\n";
	cerr << "total " << total << " balls\n";
	cerr << "hexagonal embedding would give only " << 3 * k * (k + 1) << " balls\n";

	svg.save("out.svg");
 
	return 0;
}