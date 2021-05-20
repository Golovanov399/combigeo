#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

using ld = long double;
const ld pi = acosl(-1);

ld inner_rad(ld r, ld phi, ld d = 1) {
	ld psi = pi - asin(sin(phi) * r);
	return sqrt(r * r + d * d - 2 * r * d * cos(psi));
}

ld outer_rad(ld r, ld phi, ld d = 1) {
	ld psi = asin(sin(phi) * r);
	return sqrt(r * r + d * d - 2 * r * d * cos(psi));
}

ld takes(ld r, ld where, ld d = 1) {
	return 2 * where * acos((r * r + where * where - d * d) / (2 * r * where));
}

ld sqr(ld x) {
	return x * x;
}

int main() {
	ld le = 2, ri = 3;
	for (int it = 0; it < 30; ++it) {
		ld r1 = (le + ri) / 2, r2 = 1 + sqrt(15) / 2;
		ld r = hypot((r1 + r2) / 2, sqrt(0.25 - sqr((r2 - r1) / 2)));
		if ((2 * pi * r - 6 * takes(3, r, 0.5)) / takes(r1, r, 0.5) + 6 >= 19) {
			le = r1;
		} else {
			ri = r1;
		}
	}
	ld r1 = (le + ri) / 2, r2 = 1 + sqrt(15) / 2;
	ld r = hypot((r1 + r2) / 2, sqrt(0.25 - sqr((r2 - r1) / 2)));
	cerr << r1 << " " << r2 << " " << r << "\n";
	cerr << takes(r1, r, 0.5) << " " << takes(r2, r, 0.5) << "\n";
	cout << (2 * pi * r - 6 * takes(3, r, 0.5)) / takes(r1, r, 0.5) + 6 << "\n";
 
	return 0;
}