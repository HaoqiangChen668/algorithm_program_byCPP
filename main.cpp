#include "Solutions.h"
#include "Bitset.h"

using std::cout;
using std::endl;
using std::string;

static int val = 0b00000000001001000001000000001111;
static int reverse_val = 0;
static int left = 13;
static int right = 15;
static solution solu;

int main() {
	if (1)cout << solu.near2power(val) << endl;
	if (1)cout << solu.isPowerOfTow(val) << endl;
	if (1)cout << solu.isPowerOfThree(val) << endl;
	if (1)cout << solu.rangeBitwiseAnd(left, right) << endl;
	if (1)cout << solu.printBits(val) << endl;
	if (1) {
		cout << "orignal:" << endl << solu.printBits(val) << endl;
		reverse_val = solu.reverseBits(val);
		cout << "reversal:" << endl << solu.printBits(reverse_val) << endl;
	}
	if (1) {
		cout << "orignal:" << endl << solu.printBits(val) << endl;
		cout << "cntBitsOne:" << endl << solu.cntBitsOne(val) << endl;
	}


	//位图的对数器测试
	if (1) {
		const int n = 10000000;
		const int testTimes = 100;
		std::unordered_map<int, bool> arr_com;
		Bitset arr_test(n);
		srand(time(0));
		//插入一个错误看看
		if (0) { arr_com[1] = true; }
		cout << "The test start..." << endl;
		cout << "The program was invoked..." << endl;
		for (int i = 0; i < testTimes; ++i) {
			int decide = rand() % 3;
			int theVal = rand() % n;
			if (decide == 0) {
				arr_com[theVal] = true;
				arr_test.add(theVal);
			}
			else if (decide == 1) {
				arr_com[theVal] = false;
				arr_test.remove(theVal);
			}
			else {
				arr_com[theVal] = !arr_com[theVal];
				arr_test.reverse(theVal);
			}
		}
		cout << "Finish invoking..." << endl;
		cout << "Testing..." << endl;

		bool isallCorret = true;
		for (int val = 0; val < n; ++val) { 
			bool st_map = arr_com.count(val) ? arr_com[val] : false;
			bool st_bit = arr_test.find(val);
			if (st_bit != st_map) {
				cout << "Error !!! " << "val=" << val << ",st_map=" << st_map << ",st_bit=" << st_bit<< endl;
				isallCorret = false;
			}
		}
		if (isallCorret) {
			cout << "All right..." << endl;
		}
		else {
			cout << "Something worry..." << endl;
		}
	}


	//位运算四则运算测试
	if (1) {
		int a = 280, b = 25;
		cout << a << " + " << b << " = " << solu.bitAdd(a, b) << endl;
		cout << a << " - " << b << " = " << solu.bitMinus(a, b) << endl;
		cout << a << " * " << b << " = " << solu.bitMultiply(a, b) << endl;
		cout << a << " / " << b << " = " << solu.bitDivide(a, b) << endl;
	}

	cout << "hello world 你好世界" << endl;
}
