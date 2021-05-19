#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

using ld = long double;
const ld pi = acosl(-1);

ld h(ld c) {
	return abs(c) > 0.5 ? 0 : sqrt(0.25 - c * c);
}

const int N = 9;
const ld l = 1, r = 3;

ld get_r(int i) {
	return l + (r - l) * i / (N - 1);
}

ld rem[N];
ld hc[2 * N + 1];
vector<int> cur;

bool add(int i) {
	cur.push_back(i);
	bool success = true;
	for (int j = -i; j < N - i; ++j) {
		rem[i + j] -= hc[j + N];
		if (rem[i + j] < 0) {
			success = false;
		}
	}
	return success;
}

void del(int i) {
	cur.pop_back();
	for (int j = -i; j < N - i; ++j) {
		rem[i + j] += hc[j + N];
	}
}

pair<int, vector<int>> mx = {0, {}};
void rec(int i) {
	if (i == N) {
		mx = max(mx, {(int)cur.size(), cur});
		return;
	}
	if (add(i)) {
		rec(i);
	}
	del(i);
	rec(i + 1);
}

int main() {
	for (int i = 0; i < N; ++i) {
		rem[i] = pi * get_r(i);
	}
	for (int i = -N; i <= N; ++i) {
		hc[N + i] = h((r - l) / (N - 1) * i);
	}

	for (int i = 0; i < 6; ++i) {
		add(0);
	}
	rec(1);
	cerr << mx.first << "\n";
	for (int x : mx.second) {
		cerr << get_r(x) << " ";
	}
	cerr << "\n";
 
	return 0;
}