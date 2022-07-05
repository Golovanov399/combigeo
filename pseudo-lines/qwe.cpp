#include <bits/stdc++.h>
#include "../pe/base/ostream.h"

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
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

void rec(int n, vector<int>& rem, vector<int>& p, int bad_prefix, int it, Dsu& dsu, vector<int>& old, vector<pair<int, int>>& res) {
	if (it == n * (n - 1) / 2) {
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
			rec(n, rem, p, max(i, 1), it + 1, dsu, old, res);
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
	rec(n, rem, p, 1, 0, dsu, old, res);
}

int main() {
	try_all_pseudolines(nxt());

	return 0;
}
