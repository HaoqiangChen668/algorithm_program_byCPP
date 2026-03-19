#pragma once
#include <iostream>

class solution {
private:
public:

	//打印二进制形式
	std::string printBits(int val);

	//大于或等于该数的最小的2的n次幂
	int near2power(int val);

	//是否是2的n次幂
	bool isPowerOfTow(int val);
	
	//是否是3的n次幂
	bool isPowerOfThree(int val);

	//返回left到right区间所有数的&的结果
	int rangeBitwiseAnd(int left, int right);

	//返回逆序二进制
	int reverseBits(int val);

	//数一个数的二进制表示有几个‘1’
	int cntBitsOne(int val);

	//位运算实现加法，异或和与
	int bitAdd(int a, int b);

	//位运算实现减法
	int bitMinus(int a, int b);
	//辅助函数取反加一，即取相反数
	int neg(int n);

	//位运算实现乘法
	int bitMultiply(int a, int b);

	//位运算实现除法
	int bitDiv(int a, int b);
	int bitDivide(int a, int b);
};