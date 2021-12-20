#include "geometry/delaunay.h"
#include "geometry/svg.h"

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

int main() {
	// const int n = 1000;
	// vector<Point<ld>> pts(n);
	// for (int i = 0; i < n; ++i) {
	// 	pts[i] = {rand() % 1000000 * 1e-4, rand() % 1000000 * 1e-4};
	// }

	const int n = 10;
	vector<Point<ld>> pts = {{-5., 0.}, {-1., 4.}, {-1., -4.}, {1., 4.}, {1., -4.}, {5., 0.},
							 {0., -3.9}, {0., -4.1}, {0., 3.9}, {0., 4.1}};

	Delaunay dln(pts);

	SVG svg;
	vector<vector<int>> g(n);
	for (const auto& [u, v] : dln.get_edges()) {
		svg.draw(Segment<ld>{pts[u], pts[v]}, "black", 0.1);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (const auto& p : pts) {
		svg.draw(p, 0.2, "blue", "black", 0.05);
	}

	map<pair<int, int>, vector<int>> M;
	for (const auto& tr : dln.get_triangles()) {
		for (int i = 0; i < 3; ++i) {
			int x = tr[i], y = tr[(i + 1) % 3];
			if (x > y) {
				swap(x, y);
			}
			M[{x, y}].push_back(tr[(i + 2) % 3]);
		}
	}

	vector<vector<int>> h(n);
	for (const auto& [_, v] : M) {
		if ((int)v.size() == 2) {
			h[v[0]].push_back(v[1]);
			h[v[1]].push_back(v[0]);
		}
	}

	vector<Circle<ld>> sphs(n);
	vector<int> where(n);
	for (int i = 0; i < n; ++i) {
		ld mn = 1e9;
		int opt = -1;
		for (int j : g[i]) {
			if (mn > dist(pts[i], pts[j])) {
				mn = dist(pts[i], pts[j]);
				opt = j;
			}
		}
		sphs[i] = {pts[i], mn};
		where[i] = opt;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (sphs[i].intersects(sphs[j])) {
				if (where[i] == j || where[j] == i) {
					continue;
				}
				if (where[i] == where[j]) {
					continue;
				}
				// if (find(all(g[i]), j) == g[i].end() && find(all(h[i]), j) == h[i].end()) {
				if (find(all(g[i]), j) == g[i].end() && find(all(g[i]), where[j]) == g[i].end() && find(all(g[j]), where[i]) == g[j].end() && find(all(h[i]), j) == h[i].end()) {
					cerr << i << " " << j << "\n";
					svg.draw(sphs[i], "red", "", 1, 0.2);
					svg.draw(sphs[j], "red", "", 1, 0.2);
					svg.draw(Segment<ld>{pts[i], pts[where[i]]}, "black", 0.3);
					svg.draw(Segment<ld>{pts[j], pts[where[j]]}, "black", 0.3);
					svg.save("out.svg");
					return 0;
				}
			}
		}
	}

	svg.save("out.svg");

	return 0;
}
