#include<iostream>
#include<vector>
#include<limits>

using namespace std;

class Solution {
public:



	// Question1: 使用规格8和规格6的袋子买苹果，装不完返回-1，否则返回所需的最少袋子数
	int appleMinPags1(int n) {
		int ans = appleMinPags1_f(n);
		return ans == INT_MAX ? -1 : ans;
	}
	int appleMinPags2(int n) {
		if (n == 6 || n == 8) return 1;
		else if (n == 12 || n == 14 || n == 16) return 2;
		else if (n < 18) return -1;
		return (n - 18) % 8 % 2 == 0 ? 3 + (n - 18) / 8 : -1;
	}



	// Question2: 吃草，每次只能吃4的n次幂，A先吃，B后吃，谁赢...
	char grassWinner1(int n) {
		return grassWinner1_f(n, 'A');
	}
	char grassWinner2(int n) {
		return ((n % 5) == 0 || (n % 5) == 2) ? 'B' : 'A';
	}



	// Questionn3: 判断一个数是否是连续正整数的和
	bool numContinueSum1(int n) {
		for (int i = 1; i < n; ++i) {
			int sum = i;
			int count = i + 1;
			while (sum < n) {
				sum += count++;
			}
			if (sum == n) return true;
		}
		return false;
	}
	bool numContinueSum2(int n) {
		return (n & (-n)) != n;
	}



	// Question4: 只能由'r'、'e'、'd'三个字符组成的长度为n的所有字符串中，有且只有一个包含了长度大于2的回文串的字串有多少个
	int goodString1(int n) {
		vector<char> path(n);
		return goodString1_f(path, 0);
	}
	int goodString2(int n) {
		if (n < 4) {
			if (n == 0 || n == 1) return 0;
			else if (n == 2) return 3;
			else return 18;
		}
		else {
			return 30 + (n - 4) * 6;
		}
	}



private:

	int appleMinPags1_f(int rest) {
		if (rest < 0) return INT_MAX;
		else if (rest == 0) return 0;
		int p1 = appleMinPags1_f(rest - 8);
		int p2 = appleMinPags1_f(rest - 6);
		p1 += p1 == INT_MAX ? 0 : 1;
		p2 += p2 == INT_MAX ? 0 : 1;
		return min(p1, p2);
	}

	char grassWinner1_f(int rest, char cur) {
		int emery = cur == 'A' ? 'B' : 'A';
		if (rest < 5) {
			if (rest == 2 || rest == 0) return emery;
			else return cur;
		}
		int temp = 1;
		while (temp < rest) {
			if (grassWinner1_f(rest - temp, emery) == cur) {
				return cur;
			}
			temp *= 4;
		}
		return emery;
	}

	int goodString1_f(vector<char>& path, int i) {
		int len = path.size();
		if (i == len) {
			int cnt = 0;
			for (int left = 0; left < len - 1; ++left) {
				for (int right = left + 1; right < len; ++right) {
					if (goodString1_is(path, left, right)) {
						++cnt;
					}
					if (cnt > 1) {
						return 0;
					}
				}
			}
			return cnt;
		}
		else {
			int ans = 0;
			path[i] = 'r';
			ans += goodString1_f(path, i + 1);
			path[i] = 'e';
			ans += goodString1_f(path, i + 1);
			path[i] = 'd';
			ans += goodString1_f(path, i + 1);
			return ans;
		}
	}

	bool goodString1_is(const vector<char>& path, int left, int right) {
		while (left < right) {
			if (path[left++] != path[right--]) return false;
		}
		return true;
	}

};

int main() {

	Solution solu;

	// 测试
	//for (int i = 1; i < 100; ++i) {
	//	if (solu.appleMinPags1(i) != solu.appleMinPags2(i)) {
	//		cout << "worry!!!" << i;
	//		break;
	//	}
	//}

	//for (int i = 0; i < 70; ++i) {
	//	cout << i << ": " << solu.grassWinner1(i) << endl;
	//}

	//for (int i = 0; i < 70; ++i) {
	//	if (solu.grassWinner1(i) != solu.grassWinner2(i)) {
	//		cout << "worry!!!" << i;
	//		break;
	//	}
	//}

	//for (int i = 0; i < 100; ++i) {
	//	string s = solu.numContinueSum1(i + 1) ? "true" : "false";
	//	cout << i + 1 << ": " << s << endl;
	//}

	//for (int i = 1; i < 1000; ++i) {
	//	if (solu.numContinueSum2(i) != solu.numContinueSum1(i)) {
	//		cout << "worry!!!";
	//		break;
	//	}
	//}

	//for (int i = 0; i < 100; ++i) {
	//	cout << i << ": " << solu.goodString2(i) << endl;
	//}

	//for (int i = 1; i < 15; ++i) {
	//	if (solu.goodString1(i) != solu.goodString2(i)) {
	//		cout << "worry!!!";
	//		break;
	//	}
	//}

}