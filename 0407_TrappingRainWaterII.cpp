#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Node {
    int val;
    int row;
    int col;
    Node(int x, int r, int c) : val(x), row(r), col(c) {}
    bool operator< (const Node& b) const {
        return this->val > b.val;
    }
};

int trapRainWater(vector<vector<int>>& heightMap);

int main() {
	vector<vector<int>> heightMap = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
	cout << trapRainWater(heightMap) << endl;
	return 0;
}

int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        priority_queue<Node> min_heap;
        bool visit[m][n];
        memset(visit, 0, sizeof visit);
	// cout << "Traverse the boundary: \n";
        for (int c = 0; c < n - 1; ++c) {
            visit[0][c] = 1;
            min_heap.emplace(Node(heightMap[0][c], 0, c));
        }
        for (int r = 0; r < m - 1; ++r) {
            visit[r][n - 1] = 1;
            min_heap.emplace(Node(heightMap[r][n - 1], r, n - 1));
        }
        for (int c = n - 1; c > 0; --c) {
            visit[m - 1][c] = 1;
            min_heap.emplace(Node(heightMap[m - 1][c], m - 1, c));
        }
        for (int r = m - 1; r > 0; --r) {
            visit[r][0] = 1;
            min_heap.emplace(Node(heightMap[r][0], r, 0));
        }

        int water = 0;
        int max_val = 0;
        while (!min_heap.empty()) {
            Node cur = min_heap.top();
	    // cout << "heap top: " << cur.val << ", at (" << cur.row << ", " << cur.col << ")" << endl;
            min_heap.pop();
            max_val = max(max_val, cur.val);
	    // cout << "current max: " << max_val << endl;
            int row = cur.row;
            int col = cur.col;
            if (row > 0 && !visit[row - 1][col]) {
                water += max(0, max_val - heightMap[row - 1][col]);
                visit[row - 1][col] = 1;
	    	// cout << "check: " << heightMap[row - 1][col] << ", at (" << row - 1 << ", " << col << ")" << endl;
		// cout << "total water: " << water << endl;
                min_heap.emplace(Node(heightMap[row - 1][col], row - 1, col));
            }
            if (row < m - 1 && !visit[row + 1][col]) {
                water += max(0, max_val - heightMap[row + 1][col]);
                visit[row + 1][col] = 1;
	    	// cout << "check: " << heightMap[row + 1][col] << ", at (" << row + 1 << ", " << col << ")" << endl;
		// cout << "total water: " << water << endl;
                min_heap.emplace(Node(heightMap[row + 1][col], row + 1, col));
            }
            if (col > 0 && !visit[row][col - 1]) {
                water += max(0, max_val - heightMap[row][col - 1]);
                visit[row][col - 1] = 1;
	    	// cout << "check: " << heightMap[row][col - 1] << ", at (" << row << ", " << col - 1 << ")" << endl;
		// cout << "total water: " << water << endl;
                min_heap.emplace(Node(heightMap[row][col - 1], row, col - 1));
            }
            if (col < n - 1 && !visit[row][col + 1]) {
                water += max(0, max_val - heightMap[row][col + 1]);
                visit[row][col + 1] = 1;
	    	// cout << "check: " << heightMap[row][col + 1] << ", at (" << row << ", " << col + 1 << ")" << endl;
		// cout << "total water: " << water << endl;
                min_heap.emplace(Node(heightMap[row][col + 1], row, col + 1));
            }

	    // cout << "---- Next: \n\n";
        }
        return water;
}
