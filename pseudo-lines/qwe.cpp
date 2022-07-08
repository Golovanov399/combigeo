#include <bits/stdc++.h>
#include "../pe/base/ostream.h"
#include "../pe/geometry/svg.h"

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

using Pt = Point<double>;

void visualize(int n, const vector<pair<int, int>>& res) {
	SVG svg;
	const double pi = acos(-1);
	vector<pair<Pt, Pt>> cur_side(n);
	for (int i = 0; i < n; ++i) {
		cur_side[i].first = Pt{0, (double)n}.rotated(pi / n * (i + 1));
		cur_side[i].second = Pt{0, (double)n}.rotated(pi / n * i) - cur_side[i].first;
	}
	for (auto [p, v] : cur_side) {
		svg.draw(Segment{p, p + v});
	}
	vector<int> old(n, -1);
	vector<Pt> last_center(n);
	double text_x = n + 0.5;
	double text_y = n;
	for (auto [i, j] : res) {
		if (i > j) {
			swap(i, j);
		}
		Pt new_center = cur_side[j].first + cur_side[i].second / 2 + cur_side[j].second / 2;
		if (old[i] > -1 && old[i] == old[j]) {
			int k = old[i];
			svg.draw(Polygon{vector{last_center[i], last_center[i] - cur_side[i].second / 2, last_center[j], last_center[j] + cur_side[k].second * (k < j ? 1 : -1) / 2, new_center, new_center + cur_side[j].second / 2}}, "#FF7777", "none");
			text_y -= 0.6;
			svg.text(to_string(i + 1) + "-" + to_string(j + 1) + "-" + to_string(k + 1), text_x, text_y, "black", 0.5);
		}
		last_center[i] = last_center[j] = new_center;
		old[i] = j;
		old[j] = i;
		svg.draw(Segment{new_center - cur_side[j].second / 2, new_center + cur_side[j].second / 2}, "blue", 0.03);
		svg.draw(Segment{new_center - cur_side[i].second / 2, new_center + cur_side[i].second / 2}, "blue", 0.03);
		cur_side[i].first -= cur_side[j].second;
		cur_side[j].first += cur_side[i].second;
		svg.draw(Segment{cur_side[i].first, cur_side[i].first + cur_side[i].second});
		svg.draw(Segment{cur_side[j].first, cur_side[j].first + cur_side[j].second});
	}
	svg.save("out.svg");
}

struct Dsu {
	int n;
	vector<int> color;
	vector<vector<int>> by_col;
	int cnt;

	vector<vector<tuple<int, int, int>>> changes;

	Dsu(int _n): n(_n), color(_n), by_col(_n), cnt(_n) {
		iota(all(color), 0);
		for (int i = 0; i < n; ++i) {
			by_col[i] = {i};
		}
	}

	void merge(int u, int v) {
		u = color[u], v = color[v];
		if (u == v) {
			return;
		}
		changes.back().push_back({-1, cnt, 0});
		cnt -= 1;
		if (by_col[u].size() < by_col[v].size()) {
			swap(u, v);
		}
		changes.back().push_back({u, v, by_col[v].size()});
		for (auto x : by_col[v]) {
			color[x] = u;
		}
		by_col[u].insert(by_col[u].end(), all(by_col[v]));
		by_col[v] = {};
	}

	void checkpoint() {
		changes.push_back({});
	}

	void rollback() {
		while (!changes.back().empty()) {
			const auto& [a, b, c] = changes.back().back();
			changes.back().pop_back();
			if (a == -1) {
				cnt = b;
			} else {
				by_col[b].insert(by_col[b].begin(), by_col[a].end() - c, by_col[a].end());
				by_col[a].resize((int)by_col[a].size() - c);
				for (auto x : by_col[b]) {
					color[x] = b;
				}
			}
		}
		changes.pop_back();
	}
};

void rec(int n, vector<int>& rem, vector<int>& p, int bad_prefix, int it, Dsu& dsu, vector<int>& old, vector<pair<int, int>>& res, int trs) {
	if (trs > n - 2) {
		return;
	}
	if (it == n * (n - 1) / 2) {
		if (trs == n - 2 && rand() % 78687 == 0) {
			visualize(n, res);
			exit(0);
		}
		if (dsu.cnt != 1) {
			cout << res << "\n";
			exit(0);
		}
		return;
	}
	for (int i = bad_prefix - 1; i < n - 1; ++i) {
		if (rem[p[i]] >= 1 && p[i] < p[i + 1]) {
			--rem[p[i]];
			bool new_triangle = it >= 2 && old[p[i]] > -1 && old[p[i]] == old[p[i + 1]];
			if (new_triangle) {
				dsu.checkpoint();
				dsu.merge(p[i], p[i + 1]);
				dsu.merge(res[it - 1].first, res[it - 1].second);
			}
			res[it] = {p[i], p[i + 1]};
			// if (new_triangle) {
			// 	cerr << string(it, ' ') << "found a new triangle: " << vector(res.begin() + it - 2, res.begin() + it + 1) << "\n";
			// }
			int x = old[p[i]], y = old[p[i + 1]];
			old[p[i]] = p[i + 1];
			old[p[i + 1]] = p[i];
			swap(p[i], p[i + 1]);
			rec(n, rem, p, max(i, 1), it + 1, dsu, old, res, trs + new_triangle);
			swap(p[i], p[i + 1]);
			old[p[i]] = x;
			old[p[i + 1]] = y;
			if (new_triangle) {
				dsu.rollback();
			}
			++rem[p[i]];
		}
	}
}

void try_all_pseudolines(int n) {
	Dsu dsu(n);
	vector<int> rem(n);
	iota(all(rem), 0);
	reverse(all(rem));
	vector<int> p(n);
	iota(all(p), 0);
	vector<int> old(n, -1);
	vector<pair<int, int>> res(n * (n - 1) / 2);
	rec(n, rem, p, 1, 0, dsu, old, res, 0);
}

int main() {
	try_all_pseudolines(nxt());

	return 0;
}
