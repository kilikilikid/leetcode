#include <iostream>
#include <vector>
#include <string>

using std::string;
// using namespace std;

std::vector<std::vector<string>> solveNQueens(int n);
void bk(int row, std::vector<string>& board, std::vector<int>& cols, 
		std::vector<int>& diag1, std::vector<int>& diag2, 
		std::vector<std::vector<string>>& ans);

int main() {
		int n = 4;
		std::vector<std::vector<string>> ans;
		ans = solveNQueens(n);
		for (int i = 0; i < ans.size(); i++) {
			for (int j = 0; j < ans[0].size(); j++)
				std::cout << ans[i][j] << std::endl;
			std::cout << std::endl;
		}
		std::cout << "Total: " << ans.size() << " solutions." << std::endl;
		return 0;
}

std::vector<std::vector<string>> solveNQueens(int n) {
	std::vector<string> board(n, string(n, '.'));
	std::vector<int> cols(n, 0), diag1(n + n - 1, 0), diag2(n + n - 1, 0);
	std::vector<std::vector<string>> ans;
	bk(0, board, cols, diag1, diag2, ans);
	return ans;
}

void bk(int row, std::vector<string>& board, std::vector<int>& cols, 
		std::vector<int>& diag1, std::vector<int>& diag2, 
		std::vector<std::vector<string>>& ans) {
	if (row == board.size()) {
		ans.emplace_back(board);
		return;
	}
	int N = board.size() - 1;
	for (int col = 0; col <= N; ++col) {
		if (!cols[col] && !diag1[N - row + col] && !diag2[row + col]) {
			board[row][col] = 'Q';
			cols[col]++;
			diag1[N - row + col]++;
			diag2[row + col]++;

			bk(row + 1, board, cols, diag1, diag2, ans);

			board[row][col] = '.';
			cols[col]--;
			diag1[N - row + col]--;
			diag2[row + col]--;
		}
	}
}
