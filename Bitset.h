#pragma once
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<ctime>

class Bitset {
private:
	std::vector<int> arr;
public:
	//初始化位图
	Bitset(long long int n) { arr.resize((n + 31) / 32, 0); }

	//对应的一些操作
	void add(int number) { arr[number / 32] |= (1 << (number % 32)); }
	void remove(int number) { arr[number / 32] &= ~(1 << (number % 32)); }
	void reverse(int number) { arr[number / 32] ^= (1 << (number % 32)); }
	bool find(int  number) { return ((arr[number / 32] >> (number % 32)) & 1) == 1; }
};