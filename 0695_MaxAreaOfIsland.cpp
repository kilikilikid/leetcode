#include <iostream>
#include <vector>
#include <stack>
#include <queue>
// using namespace std;

int maxAreaOfIsland(std::vector<std::vector<int>>& grid);
int dfs(std::vector<std::vector<int>>& grid, int r, int c);
int maxAreaOfIsland_dfs_stack(std::vector<std::vector<int>>& grid);
int maxAreaOfIsland_bfs_queue(std::vector<std::vector<int>>& grid);
class UnionFind {
private:
	std::vector<int> parent;
	std::vector<int> size;
	int _max_area = 0;
public:
	UnionFind(std::vector<std::vector<int>>);
	int find(int);
	void unite(int, int);
	int getMax() {return _max_area;}
};
int maxAreaOfIsland_unionFind(std::vector<std::vector<int>>& grid);

int nr, nc;
std::vector<std::vector<int>> grid {
	{0,0,1,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0},
	{0,1,1,0,1,0,0,0,0,0,0,0,0},
	{0,1,0,0,1,1,0,0,1,0,1,0,0},
	{0,1,0,0,1,1,0,0,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,1,1,0,0,0,0}
};

int main() {
	std::vector<std::vector<int>> grid1, grid2, grid3;
	grid1 = grid2 = grid3 = grid;

	std::cout << maxAreaOfIsland(grid1) << std::endl;
	std::cout << maxAreaOfIsland_dfs_stack(grid2) << std::endl;
	std::cout << maxAreaOfIsland_bfs_queue(grid3) << std::endl;
	std::cout << maxAreaOfIsland_unionFind(grid) << std::endl;
	return 0;
}

int dfs(std::vector<std::vector<int>>& grid, int r, int c) {
	if (r < 0 || c < 0 || r == nr || c == nc || grid[r][c] == 0)
		return 0;
	grid[r][c] = 0;
	int area = 1;
	area += dfs(grid, r - 1, c) + dfs(grid, r + 1, c) + dfs(grid, r, c - 1) + dfs(grid, r, c + 1);
	return area;
}

int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
	nr = grid.size();
	nc = grid[0].size();
	int max_area = 0;

	for (int r = 0; r < nr; r++)
		for (int c = 0; c < nc; c++)
			if (grid[r][c])
				max_area = std::max(max_area, dfs(grid, r, c));
	return max_area;
}


int maxAreaOfIsland_dfs_stack(std::vector<std::vector<int>>& grid) {
	nr = grid.size();
	nc = grid[0].size();
	int max_area = 0;

	std::stack<std::pair<int, int>> stk;
	const int dirc[4][2] { {-1,0}, {1,0}, {0,-1}, {0,1} };
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			int area = 0;
			stk.push({r, c});
			while (!stk.empty()) {
				int row = stk.top().first, col = stk.top().second;
				stk.pop();
				if (row < 0 || col < 0 || row == nr || col == nc || grid[row][col] == 0)
					continue;
				area++; // cause grid[row][col] == 1
				grid[row][col] = 0;
				for (int i = 0; i < 4; i++) {
					int new_r = row + dirc[i][0], new_c = col + dirc[i][1];
					stk.push({new_r, new_c});
				}
			}
			max_area = std::max(max_area, area);
		}
	}
	return max_area;
}

int maxAreaOfIsland_bfs_queue(std::vector<std::vector<int>>& grid) {
	nr = grid.size();
	nc = grid[0].size();
	int max_area = 0;

	std::queue<std::pair<int, int>> q;
	const int dirc[4][2] { {-1,0}, {1,0}, {0,-1}, {0,1} };
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			int area = 0;
			q.push({r, c});
			while (!q.empty()) {
				int row = q.front().first, col = q.front().second;
				q.pop();
				if (row < 0 || col < 0 || row == nr || col == nc || grid[row][col] == 0)
					continue;
				area++; // cause grid[row][col] == 1
				grid[row][col] = 0;
				for (int i = 0; i < 4; i++) {
					int new_r = row + dirc[i][0], new_c = col + dirc[i][1];
					q.push({new_r, new_c});
				}
			}
			max_area = std::max(max_area, area);
		}
	}
	return max_area;
}

UnionFind::UnionFind(std::vector<std::vector<int>> grid) {
	int nr = grid.size(), nc = grid[0].size();
	parent = std::vector<int> (nr * nc, 0);
	size = std::vector<int> (nr * nc, 0);

	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (grid[r][c]) {
				parent[r * nc + c] = r * nc + c;
				size[r * nc + c] = 1;
				if (_max_area != 1) _max_area = 1;
			}
		}
	}
}

int UnionFind::find(int x) {
	if (parent[x] == x) return x;
	return parent[x] = find(parent[x]);
}

void UnionFind::unite(int x, int y) {
	int rootx = find(x);
	int rooty = find(y);

	if (rootx != rooty) {
		if (size[rootx] < size[rooty]) std::swap(rootx, rooty);
		parent[rooty] = rootx;
		size[rootx] += size[rooty];
		_max_area = std::max(_max_area, size[rootx]);
	}
}

int maxAreaOfIsland_unionFind(std::vector<std::vector<int>>& grid) {
	int nr = grid.size(), nc = grid[0].size();
	UnionFind uf(grid);

	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (grid[r][c] == 1) {
				if (r < nr - 1 && grid[r + 1][c]) uf.unite(r * nc + c, (r + 1) * nc + c);
				if (c < nc - 1 && grid[r][c + 1]) uf.unite(r * nc + c, r * nc + c + 1);
			}
		}
	}
	return uf.getMax();
}
