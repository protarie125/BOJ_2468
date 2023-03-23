#include <iostream>
#include <vector>

using namespace std;

using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;

const auto& dx = vi{ -1,1,0,0 };
const auto& dy = vi{ 0,0,-1,1 };

void dfs(int n, const vvi& f, int a, vvb& isChecked, int y, int x) {
	isChecked[y][x] = true;

	for (auto d = 0; d < 4; ++d) {
		const auto& nx = x + dx[d];
		const auto& ny = y + dy[d];

		if (nx < 0 || n <= nx ||
			ny < 0 || n <= ny) {
			continue;
		}

		if (isChecked[ny][nx]) {
			continue;
		}

		if (f[ny][nx] <= a) {
			continue;
		}

		dfs(n, f, a, isChecked, ny, nx);
	}
};

int solve(int n, const vvi& f, int a) {
	auto ret = int{ 0 };

	auto isChecked = vvb(n, vb(n, false));
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			if (isChecked[i][j]) {
				continue;
			}

			if (f[i][j] <= a) {
				continue;
			}

			dfs(n, f, a, isChecked, i, j);
			++ret;
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n; cin >> n;
	auto f = vvi(n, vi(n));
	auto mxA = int{ 0 };
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			cin >> f[i][j];
			if (mxA < f[i][j]) {
				mxA = f[i][j];
			}
		}
	}

	auto ans = int{ 0 };
	for (auto i = 0; i < mxA; ++i) {
		const auto& ct = solve(n, f, i);
		if (ans < ct) {
			ans = ct;
		}
	}

	cout << ans;

	return 0;
}