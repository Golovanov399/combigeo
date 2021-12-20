#include "pe/geometry/primitives/point.h"

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	scanf("%d", &x);
	return x;
}

const double pi = acos(-1);
using Pt = Point<double>;

int main() {
	vector<double> angles;
	for (int s : {3, 4, 5}) {
		double phi = rand();
		phi -= floor(phi / 2 / pi) * 2 * pi;
		for (int i = 0; i < s; ++i) {
			angles.push_back(phi);
			phi += 2 * pi / s;
			if (phi >= 2 * pi) {
				phi -= 2 * pi;
			}
		}
	}
	sort(all(angles));
	const int n = angles.size();
	vector<Pt> pts(n, {0, 0});
	for (int i = 0; i < n - 1; ++i) {
		pts[i + 1] = pts[i] + Pt{1, 0}.rotated(angles[i]);
	}

	cout << setprecision(6) << fixed;

	cout << "numeric r;\n";
	cout << "r = 1.5cm;\n";
	cout << "path disk;\n";
	cout << "disk = fullcircle scaled r;\n";
	cout << "pickup pencircle scaled 0.7;\n";

	cout << "pair c[];\n";
	for (int i = 0; i <= n; ++i) {
		cout << "c[" << i << "] = (" << pts[i % n].x << ", " << pts[i % n].y << ") scaled r;\n";
	}

	cout << "for i := 0 step 1 until " << n - 1 << ":\n";
	cout << "  drawarrow(c[i]--c[i+1]);\n";
	cout << "endfor;\n";

	Pt u{1, 0};
	for (int it = 0; it < 6; ++it) {
		int opt = 0;
		for (int i = 0; i < n; ++i) {
			if (cross(pts[i], u) > cross(pts[opt], u)) {
				opt = i;
			}
		}

		cout << "draw (c[" << opt << "] - ((r * " << n << " / 6, 0) rotated " << 60 * it << "))--(c[" << opt << "] + ((r * " << n << " / 6, 0) rotated " << 60 * it << ")) dashed evenly;\n";

		u.rotate(pi / 3);
	}
	cout << "for i := 0 step 1 until " << n - 1 << ":\n";
	cout << "  dotlabel(btex$$etex, c[i]);\n";
	cout << "  draw disk shifted c[i] dashed evenly;\n";
	cout << "endfor;\n";

	cout << "pickup pencircle scaled 0.2;\n";

	cout << "pair outer[];\n";
	cout << "numeric par[];\n";
	int sz = 0;
	int last = -1;
	for (int i = 0; i < n; ++i) {
		Pt cur = pts[i];
		Pt pr = pts[(i - 1 + n) % n];
		Pt nx = pts[(i + 1) % n];
		if (last == -1) {
			last = 0;
			while (!(cross(pr - cur, u) >= 0 && cross(u, nx - cur) >= 0 && dot(pr - cur, u) <= 0.5 && dot(nx - cur, u) <= 0.5)) {
				++last;
				u.rotate(pi / 3);
			}
		}
		while (!(cross(pr - cur, u) >= 0 && cross(u, nx - cur) >= 0 && dot(pr - cur, u) <= 0.5 && dot(nx - cur, u) <= 0.5)) {
			++last;
			u.rotate(pi / 3);
		}
		while (true) {
			if (cross(pr - cur, u) >= 0 && cross(u, nx - cur) >= 0 && dot(pr - cur, u) <= 0.5 && dot(nx - cur, u) <= 0.5) {
				cout << "outer[" << sz << "] = c[" << i << "] shifted ((r, 0) rotated " << 60 * last << ");\n";
				cout << "par[" << sz++ << "] = " << i << ";\n";
			} else {
				last = (last + 5) % 6;
				u.rotate(-pi / 3);
				break;
			}
			++last;
			if (last == 6) {
				last = 0;
			}
			u.rotate(pi / 3);
		}
	}
	cout << "outer[" << sz << "] = outer[0];\n";
	cout << "for i := 0 step 1 until " << sz - 1 << ":\n";
	cout << "  dotlabel(btex$$etex, outer[i]);\n";
	cout << "  drawarrow(c[par[i]]--outer[i]);\n";
	cout << "  drawarrow(outer[i]--outer[i+1]);\n";
	cout << "  draw disk shifted outer[i];\n";
	cout << "endfor;\n";

	return 0;
}
