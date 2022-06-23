#include <iostream>
#include <vector>

using namespace std;

int majorityElement(vector<int>& nums);

int main() {
	vector<int> nums { 2,2,1,1,1,2,2 };
	cout << majorityElement(nums) << endl;
	return 0;
}


int majorityElement(vector<int>& nums) {
	int ans = nums[0];
	int count = 1;
	for (int i = 1; i < nums.size(); ++i) {
		if (count = 0) ans = nums[i];
		count += (ans == nums[i] ? 1 : -1);
	}
	return ans;
}
