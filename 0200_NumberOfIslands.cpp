#include <iostream>
#include <vector>
#include <queue>

// using namespace std;

class UnionFind {
private:
	int count;
	std::vector<int> rank;
	std::vector<int> parent;
public:
	UnionFind (std::vector<std::vector<char>>& grid) {
		count = 0;
		int nrow = grid.size();
		int ncol = grid[0].size();
		for (int r = 0; r < nrow; r++) {
			for (int c = 0; c < ncol; c++) {
				if (grid[r][c] == '1') {
					parent.emplace_back(r * ncol + c);
					++count;
				}
				else {
					parent.emplace_back(-1);
				}
				rank.emplace_back(0);
			}
		}
	}
	int find(int x) {
		if (parent[x] != x) parent[x] = find(parent[x]);
		return parent[x];
	}
	void unite(int x, int y) {
		int rootx = find(x);
		int rooty = find(y);
		if (rootx != rooty) {
			if (rank[rootx] < rank[rooty]) std::swap(rootx, rooty);
			parent[rooty] = rootx;
			if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
			count--;
		}
	}
	int getCount() {return count;}
};

int numIslands_unifind(std::vector<std::vector<char>>& grid);
int numIslands_dfs(std::vector<std::vector<char>>& grid);
int numIslands_bfs(std::vector<std::vector<char>>& grid);
void dfs(std::vector<std::vector<char>>& grid, int r, int c);

int main() {
	std::vector<std::vector<char>> grid = {
		{'1','1','0','0','0'},
		{'1','1','0','0','0'},
		{'0','0','1','0','0'},
		{'0','0','0','1','1'},
	};
	std::cout << numIslands_unifind(grid) << std::endl;
	std::cout << numIslands_dfs(grid) << std::endl;
	grid = {
		{'1','1','0','0','0'},
		{'1','1','0','0','0'},
		{'0','0','1','0','0'},
		{'0','0','0','1','1'},
	};
	std::cout << numIslands_bfs(grid) << std::endl;
	return 0;
}

int numIslands_dfs(std::vector<std::vector<char>>& grid) {
	int nr = grid.size();
	if (!nr) return 0;
	int nc = grid[0].size();
	int ans = 0;
	for (int r = 0; r < nr; ++r) {
		for (int c = 0; c < nc; c++) {
			if (grid[r][c] == '1') {
				ans++;
				dfs(grid, r, c);
			}
		}
	}
	return ans;
}
// void dfs(std::vector<std::vector<char>>& grid, int r, int c) {
// 	int nr = grid.size();
// 	int nc = grid[0].size();
// 	grid[r][c] = '0';
// 	// up
// 	if (r - 1 >= 0 && grid[r - 1][c] == '1') dfs(grid, r - 1, c);
// 	// down
// 	if (r + 1 < nr && grid[r + 1][c] == '1') dfs(grid, r + 1, c);
// 	// left
// 	if (c - 1 >= 0 && grid[r][c - 1] == '1') dfs(grid, r, c - 1);
// 	// right
// 	if (c + 1 < nc && grid[r][c + 1] == '1') dfs(grid, r, c + 1);
// }
void dfs(std::vector<std::vector<char>>& grid, int r, int c) {
	int nr = grid.size();
	int nc = grid[0].size();
	if (r < 0 || c < 0 || r >= nr || c >= nc || grid[r][c] == '0') return;
	grid[r][c] = '0';
	// up
	dfs(grid, r - 1, c);
	// down
	dfs(grid, r + 1, c);
	// left
	dfs(grid, r, c - 1);
	// right
	dfs(grid, r, c + 1);
}

int numIslands_bfs(std::vector<std::vector<char>>& grid) {
	int nr = grid.size();
	if (!nr) return 0;
	int nc = grid[0].size();
	int ans = 0;
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (grid[r][c] == '1') {
				ans++;
				grid[r][c] = '0';
				std::queue<std::pair<int, int>> neighbors;
				neighbors.push({r, c});
				while (!neighbors.empty()) {
					auto rc = neighbors.front();
					neighbors.pop();
					int row = rc.first, col = rc.second;
					if (row > 0 && grid[row - 1][col] == '1') {
						neighbors.push({row - 1, col});
						grid[row - 1][col] = '0';
					}
					if (row + 1 < nr && grid[row + 1][col] == '1') {
						neighbors.push({row + 1, col});
						grid[row + 1][col] = '0';
					}
					if (col > 0 && grid[row][col - 1] == '1') {
						neighbors.push({row, col - 1});
						grid[row][col - 1] = '0';
					}
					if (col + 1 < nc && grid[row][col + 1] == '1') {
						neighbors.push({row, col + 1});
						grid[row][col + 1] = '0';
					}
				}
			}
		}
	}
	return ans;
}

int numIslands_unifind(std::vector<std::vector<char>>& grid) {
	int nr = grid.size();
	if (!nr) return 0;
	int nc = grid[0].size();
	UnionFind uf(grid);
	for (int r = 0; r < nr; ++r) {
		for (int c = 0; c < nc; c++) {
			if (grid[r][c] == '1') {
				if (r - 1 >= 0 && grid[r - 1][c] == '1') 
					uf.unite(r * nc + c, (r - 1) * nc + c);
				if (r + 1 < nr && grid[r + 1][c] == '1') 
					uf.unite(r * nc + c, (r + 1) * nc + c);
				if (c - 1 >= 0 && grid[r][c - 1] == '1') 
					uf.unite(r * nc + c, r * nc + c - 1);
				if (c + 1 < nc && grid[r][c + 1] == '1') 
					uf.unite(r * nc + c, r * nc + c + 1);
			}
		}
	}
	return uf.getCount();
}
