#include <iostream>
#include <vector>
#include <stack>
#include <queue>
// using namespace std;

void solve(std::vector<std::vector<char>>& board);
void dfs(std::vector<std::vector<char>>& board, int r, int c);
void solve_dfs_stack(std::vector<std::vector<char>>& board);
void solve_bfs_queue(std::vector<std::vector<char>>& board);

// class UnionFind {
// private:
// 	std::vector<int> parent;
// 	std::vector<int> size;
// 	int _max_area = 0;
// public:
// 	UnionFind(std::vector<std::vector<int>>);
// 	int find(int);
// 	void unite(int, int);
// 	int getMax() {return _max_area;}
// };
// int solve_unionFind(std::vector<std::vector<char>>& board);

int nr, nc;
std::vector<std::vector<char>> board {
	{'X','X','X','X'},
	{'X','O','O','X'},
	{'X','X','O','X'},
	{'X','O','X','X'}
};

int main() {
	std::vector<std::vector<char>> board1, board2, board3;
	board1 = board2 = board3 = board;
	
	nr = board.size();
	nc = board[0].size();
	
	std::cout << std::endl << "Before:" << std::endl;
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			std::cout << board[r][c];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "DFS After:" << std::endl;
	solve(board1);
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			std::cout << board1[r][c];
		}
		std::cout << std::endl;
	}
	
	std::cout << std::endl << "DFS Stack After:" << std::endl;
	solve_dfs_stack(board2);
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			std::cout << board2[r][c];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "BFS Queue After:" << std::endl;
	solve_bfs_queue(board3);
	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			std::cout << board3[r][c];
		}
		std::cout << std::endl;
	}

	// std::cout << solve_unionFind(board) << std::endl;
	return 0;
}

void dfs(std::vector<std::vector<char>>& board, int r, int c) {
	if (r < 0 || c < 0 || r == nr || c == nc || board[r][c] != 'O')
		return;
	board[r][c] = '#';
	dfs(board, r - 1, c);
	dfs(board, r + 1, c);
	dfs(board, r, c - 1);
	dfs(board, r, c + 1);
}

void solve(std::vector<std::vector<char>>& board) {

	for (int r = 0; r < nr; r++) {
		dfs(board, r, 0);
		dfs(board, r, nc - 1);
	}
	for (int c = 1; c < nc - 1; c++) {
		dfs(board, 0, c);
		dfs(board, nr - 1, c);
	}

	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (board[r][c] == '#')
				board[r][c] = 'O';
			else if (board[r][c] == 'O')
				board[r][c] = 'X';
		}
	}
}


void solve_dfs_stack(std::vector<std::vector<char>>& board) {
	
	std::stack<std::pair<int, int>> stk;
	for (int r = 0; r < nr; r++) {
		if (board[r][0] == 'O') {
			stk.push({r, 0});
			board[r][0] = '#';
		}
		if (board[r][nc - 1] == 'O') {
			stk.push({r, nc - 1});
			board[r][nc - 1] = '#';
		}
	}
	for (int c = 1; c < nc - 1; c++) {
		if (board[0][c] == 'O') {
			stk.push({0, c});
			board[0][c] = '#';
		}
		if (board[nr - 1][c] == 'O') {
			stk.push({nr - 1, c});
			board[nr - 1][c] = '#';
		}
	}

	const int dirc[4][2] { {-1,0}, {1,0}, {0,-1}, {0,1} };
	while (!stk.empty()) {
		int row = stk.top().first, col = stk.top().second;
		stk.pop();
		for (int i = 0; i < 4; i++) {
			int new_r = row + dirc[i][0], new_c = col + dirc[i][1];
			if (new_r < 0 || new_c < 0 || new_r == nr || new_c == nc || board[new_r][new_c] != 'O')
				continue;
			stk.push({new_r, new_c});
			board[new_r][new_c] = '#';
		}
	}

	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (board[r][c] == '#')
				board[r][c] = 'O';
			else if (board[r][c] == 'O')
				board[r][c] = 'X';
		}
	}
}


void solve_bfs_queue(std::vector<std::vector<char>>& board) {
	
	std::queue<std::pair<int, int>> que;
	for (int r = 0; r < nr; r++) {
		if (board[r][0] == 'O') {
			que.push({r, 0});
			board[r][0] = '#';
		}
		if (board[r][nc - 1] == 'O') {
			que.push({r, nc - 1});
			board[r][nc - 1] = '#';
		}
	}
	for (int c = 1; c < nc - 1; c++) {
		if (board[0][c] == 'O') {
			que.push({0, c});
			board[0][c] = '#';
		}
		if (board[nr - 1][c] == 'O') {
			que.push({nr - 1, c});
			board[nr - 1][c] = '#';
		}
	}

	const int dirc[4][2] { {-1,0}, {1,0}, {0,-1}, {0,1} };
	while (!que.empty()) {
		int row = que.front().first, col = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int new_r = row + dirc[i][0], new_c = col + dirc[i][1];
			if (new_r < 0 || new_c < 0 || new_r == nr || new_c == nc || board[new_r][new_c] != 'O')
				continue;
			que.push({new_r, new_c});
			board[new_r][new_c] = '#';
		}
	}

	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (board[r][c] == '#')
				board[r][c] = 'O';
			else if (board[r][c] == 'O')
				board[r][c] = 'X';
		}
	}
}


// UnionFind::UnionFind(std::vector<std::vector<int>> board) {
// 	int nr = board.size(), nc = board[0].size();
// 	parent = std::vector<int> (nr * nc, 0);
// 	size = std::vector<int> (nr * nc, 0);

	// for (int r = 0; r < nr; r++) {
	// 	for (int c = 0; c < nc; c++) {
	// 		if (board[r][c]) {
	// 			parent[r * nc + c] = r * nc + c;
	// 			size[r * nc + c] = 1;
	// 			if (_max_area != 1) _max_area = 1;
	// 		}
	// 	}
	// }
// }

// int UnionFind::find(int x) {
// 	if (parent[x] == x) return x;
// 	return parent[x] = find(parent[x]);
// }

// void UnionFind::unite(int x, int y) {
// 	int rootx = find(x);
// 	int rooty = find(y);

	// if (rootx != rooty) {
	// 	if (size[rootx] < size[rooty]) std::swap(rootx, rooty);
	// 	parent[rooty] = rootx;
	// 	size[rootx] += size[rooty];
	// 	_max_area = std::max(_max_area, size[rootx]);
	// }
// }

// int solve_unionFind(std::vector<std::vector<char>>& board) {
// 	int nr = board.size(), nc = board[0].size();
// 	UnionFind uf(board);

// 	for (int r = 0; r < nr; r++) {
// 		for (int c = 0; c < nc; c++) {
// 			if (board[r][c] == 1) {
// 				if (r < nr - 1 && board[r + 1][c]) uf.unite(r * nc + c, (r + 1) * nc + c);
// 				if (c < nc - 1 && board[r][c + 1]) uf.unite(r * nc + c, r * nc + c + 1);
// 			}
// 		}
// 	}
// 	return uf.getMax();
// }
