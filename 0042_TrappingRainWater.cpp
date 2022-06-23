#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

int trap_2pt(vector<int>& height);
int trap_monoStk(vector<int>& height);
int trap_dp(vector<int>& height);

int main() {
	vector<int> height = { 0,1,0,2,1,0,1,3,2,1,2,1 };
	cout << trap_2pt(height) << endl;
	cout << trap_monoStk(height) << endl;
	cout << trap_dp(height) << endl;
	return 0;
}

int trap_2pt(vector<int>& height) {
	int n = height.size();
	int L = 1, R = n - 2;
	int Lmax = height[0], Rmax = height[n - 1];
	int water = 0;
	while (L <= R) {
		if (Lmax < Rmax) {
			water += max(0, Lmax - height[L]);
			Lmax = max(Lmax, height[L]);
			L++;
		}
		else {
			water += max(0, Rmax - height[R]);
			Rmax = max(Rmax, height[R]);
			R--;
		}
	}
	return water;
}

int trap_monoStk(vector<int>& height) {
	int n = height.size();
	if (n < 3) return 0;
	stack<int> stk;
	// stk.push(0);
	int water = 0;
	for (int i = 0; i < n; ++i) {
		while (!stk.empty() && height[i] > height[stk.top()]) {
			int top = stk.top();
			stk.pop();
			if (stk.empty()) break;
			int width = i - stk.top() - 1;
			int h = min(height[i], height[stk.top()]) - height[top];
			water += width * h;
		}
		stk.push(i);
	}
	return water;
}


int trap_dp(vector<int>& height) {
	int n = height.size();
	int water = 0;
	int Lmax[n], Rmax[n];
	memset(Lmax, 0, sizeof Lmax);
	memset(Rmax, 0, sizeof Rmax);
	Lmax[0] = height[0];
	Rmax[n - 1] = height[n - 1];
	for (int i = 1; i < n; ++i) Lmax[i] = max(Lmax[i - 1], height[i]);
	for (int i = n - 2; i >= 0; --i) Rmax[i] = max(Rmax[i + 1], height[i]);
	for (int i = 0; i < n; ++i) {
		water += max(0, min(Lmax[i], Rmax[i]) - height[i]);
	}
	return water;
}
