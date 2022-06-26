#include <iostream>
#include <vector>
// using namespace std;

void dfs(std::vector<std::vector<int>>& heights, std::vector<std::vector<bool>>& oceanflow, int r, int c);
std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights);
std::vector<std::vector<int>> pacificAtlantic_dfs_stk(std::vector<std::vector<int>>& heights;

int main() {
	std::vector<std::vector<int>> heights = {
		{1,2,2,3,5},
		{3,2,3,4,4},
		{2,4,5,3,1},
		{6,7,1,4,5},
		{5,1,1,2,4},
	};
	std::vector<std::vector<int>> ans = pacificAtlantic(heights);
	for (int i = 0; i < ans.size(); ++i) {
		std::cout << "[" << ans[i][0] << ", " << ans[i][1] << "], ";
	}
	std::cout << std::endl;
	return 0;
}


void dfs(std::vector<std::vector<int>>& heights, std::vector<std::vector<bool>>& oceanflow, int r, int c) {
	if (oceanflow[r][c] == 1) return;
	int nr = heights.size(), nc = heights[0].size();
	oceanflow[r][c] = 1;
	int dirc[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
	for (int i = 0; i < 4; ++i) {
		int row = r + dirc[i][0], col = c + dirc[i][1];
		if (row >= 0 && row < nr && col >= 0 && col < nc && heights[row][col] >= heights[r][c])
			dfs(heights, oceanflow, row, col);
	}
}

std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) {
	int nr = heights.size(), nc = heights[0].size();
	std::vector<std::vector<int>> ans;
	std::vector<std::vector<bool>> pacific(nr, std::vector<bool>(nc, false));
	std::vector<std::vector<bool>> atlantic(nr, std::vector<bool>(nc, false));
	for (int r = 0; r < nr; ++r) {
		dfs(heights, pacific, r, 0);
		dfs(heights, atlantic, r, nc - 1);
	}
	for (int c = 0; c < nc; ++c) {
		dfs(heights, pacific, 0, c);
		dfs(heights, atlantic, nr - 1, c);
	}
	for (int r = 0; r < nr; ++r) {
		for (int c = 0; c < nc; ++c) {
			if (pacific[r][c] && atlantic[r][c]) {
				ans.emplace_back(std::vector<int> {r, c});
			}
		}
	}
	return ans;
}
