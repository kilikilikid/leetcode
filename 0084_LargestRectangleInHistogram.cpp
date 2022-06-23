#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int largestRectangleArea(vector<int>& heights);

int main() {
	vector<int> heights = { 2,1,5,6,2,3 };
	cout << largestRectangleArea(heights) << endl;
	return 0;
}

int largestRectangleArea(vector<int>& heights) {
	heights.insert(heights.begin(), 0);
	heights.push_back(0);
	int n = heights.size();
	int ans = 0;
	stack<int> stk;
	stk.push(0);
	for (int i = 1; i < n; i++) {
		while (!stk.empty() && heights[i] < heights[stk.top()]) {
			int top = stk.top();
			stk.pop();
			int width = i - stk.top() - 1;
			ans = max(ans, width * heights[top]);
		}
		stk.push(i);
	}
	return ans;
}
