// #include <vector>
// #include <stack>
#include <iostream>
// #include <sstream>
// #include <algorithm>
using namespace std;

class Solution {
public:
    bool ispalin(string s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }

    string longestPalindrome(string s) {
        int len = s.size();
        int globalmax = 1;
        int begin = 0;

        if (len == 1) return s;

        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                int localmax = j - i + 1;
                if (localmax > globalmax && ispalin(s, i, j)) {
                    globalmax = localmax;
                    begin = i;
                }
            }
        }
		std::cout << "globalmax: " << globalmax << std::endl;
		std::cout << "begin:     " << begin << std::endl;
        return s.substr(begin, globalmax);
    }
};

int main() {
    Solution s;
    string stest = "cbbbbd";
	string c = s.longestPalindrome(stest);
    std::cout << "string: " << stest << std::endl;
	std::cout << "ans:    " << c << '\n';
    return 0;
}
