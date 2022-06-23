#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int minCostConnectPoints(vector<vector<int>>& points);

int main() {
	vector<vector<int>> points = { {0,0}, {2,2}, {3,10}, {5,2}, {7,0} };

	int ans = -1;
	ans = minCostConnectPoints(points);

	cout << ans << endl;

	return 0;
}

int minCostConnectPoints(vector<vector<int>>& points) {
	int n = points.size();
	vector<vector<int>> distMtx(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			distMtx[i][j] = abs(points[i][0] - points[j][0]) + 
							abs(points[i][1] - points[j][1]);
			distMtx[j][i] = distMtx[i][j];
		}
	}
	vector<bool> visited(n);
	vector<int> minDist2Visited(n);
	for (int i = 0; i < n; ++i)
		minDist2Visited[i] = distMtx[0][i];
	int ans = 0;

	visited[0] = 1;
	for (int k = 1; k < n; ++k) {
		int nearestUnVisitiedIdx = -1;
		int minCost = 0x3f3f3f3f;
		for (int i = 1; i < n; ++i) {
			if (visited[i]) continue;
			if (minDist2Visited[i] < minCost) {
				nearestUnVisitiedIdx = i;
				minCost = minDist2Visited[i];
			}
		}
		// cout << "nearestUnVisitiedIdx: " << nearestUnVisitiedIdx << "\nminCost: " << minCost << endl;
		ans += minCost;
		visited[nearestUnVisitiedIdx] = 1;
		for (int i = 0; i < n; ++i) {
			if (visited[i]) continue;
			minDist2Visited[i] = min(minDist2Visited[i], 
							distMtx[nearestUnVisitiedIdx][i]);
		}
	}
	return ans;
}
