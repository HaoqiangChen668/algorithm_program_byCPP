#include "Solutions.h"
#include <climits>
#define MIN INT_MIN
#define MAX INT_MAX

int solution::near2power(int val) {
	if (val < 2) return 1;
	--val;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	return ++val;
}

bool solution::isPowerOfTow(int val) {
	return val > 0 && val == (val & -val);
}

bool solution::isPowerOfThree(int val) {
	return val > 0 && 1162261467 % val == 0;
}

int solution::rangeBitwiseAnd(int left, int right) {
	while (left < right) {
		right -= (right & -right);
	}
	return right;
}

int solution::reverseBits(int val) {
	val = (((val & 0xaaaaaaaa) >> 1) | ((val & 0x55555555) << 1));
	val = (((val & 0xcccccccc) >> 2) | ((val & 0x33333333) << 2));
	val = (((val & 0xf0f0f0f0) >> 4) | ((val & 0x0f0f0f0f) << 4));
	val = (((val & 0xff00ff00) >> 8) | ((val & 0x00ff00ff) << 8));
	val = (((val & 0xffff0000) >> 16) | ((val & 0x0000ffff) << 16));
	return val;
}

std::string solution::printBits(int val) {
	std::string ans("");
	for (int i = 31; i >= 0; --i) {
		ans += (val & (1 << i)) == 0 ? '0' : '1';
	}
	return ans;
}

int solution::cntBitsOne(int val) {
	val = (val & 0x55555555) + ((val >> 1) & 0x55555555);
	val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
	val = (val & 0x0f0f0f0f) + ((val >> 4) & 0x0f0f0f0f);
	val = (val & 0x00ff00ff) + ((val >> 8) & 0x00ff00ff);
	val = (val & 0x0000ffff) + ((val >> 16) & 0x0000ffff);
	return val;
}

int solution::bitAdd(int a, int b) {
	int ans = a;
	while (b != 0) {
		ans = a ^ b;
		b = (a & b) << 1;
		a = ans;
	}
	return ans;
}

int solution::bitMinus(int a, int b) {
	return bitAdd(a, neg(b));
}

int solution::neg(int n) {
	return bitAdd(~n, 1);
}

int solution::bitMultiply(int a, int b) {
	int ans = 0;
	while (b != 0) {
		if ((b & 1) != 0) {
			ans = bitAdd(ans, a);
		}
		//b = (b & 0xFFFFFFFFu) >> 1;
		b = (unsigned int)b >> 1;
		a <<= 1;
	}
	return ans;
}

int solution::bitDiv(int a, int b) {
	int x = a < 0 ? neg(a) : a;
	int y = b < 0 ? neg(b) : b;
	int ans = 0;
	for (int i = 30; i >= 0; i = bitMinus(i, 1)) {
		if ((x >> i) >= y) {
			ans |= (1 << i);
			x = bitMinus(x, (y << i));
		}
	}
	return a < 0 ^ b < 0 ? neg(ans) : ans;
}

int solution::bitDivide(int a, int b) {
	if (a == MIN && b == MIN) {
		return 1;
	}
	if (a != MIN && b != MIN) {
		return bitDiv(a, b);
	}
	if (b == MIN) {
		return 0;
	}
	if (b == neg(1)) {
		return MAX;
	}
	a = bitAdd(a, b > 0 ? b : neg(b));
	int ans = bitDiv(a, b);
	int offest = b > 0 ? neg(1) : 1;
	return bitAdd(ans, offest);
}