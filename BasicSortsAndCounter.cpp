// 本程序展示三个基础排序：冒泡，选择，插入

// 并实现一个对数器用以验证

// 作者：Saber（HaoQiangChen668）

// 使用工具： Visual Studio 2026


#include <iostream>
#include <algorithm> // 用sort函数验证
#include <vector>
#include <cstdlib>
#include <ctime>

using std::cout; using std::cin; 
using std::endl; using std::vector;
using std::string;


// 最大长度，最大数值，实验次数，控制实验过程的展示
static int MAXLEN, MAXVAL, TIMES, SHOW;


// 交换两个数
void swapint(int& n1, int& n2) {

	// 使用的位运算
	n1 = n1 ^ n2;
	n2 = n1 ^ n2;
	n1 = n1 ^ n2;

	// 也可以写成这样
	// int temp = n1;
	// n1 = n2;
	// n2 = temp;
}



// 冒泡排序的实现
static void BubbleSort(vector<int>& arr) {
	int n = arr.size();
	if (n == 0) return;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swapint(arr[j], arr[j + 1]);
			}
		}
	}
}



// 选择排序的实现
static void SelectSort(vector<int>& arr) {
	int n = arr.size();
	if (n == 0) return;
	for (int minVal_idx, i = 0; i < n - 1; ++i) {
		minVal_idx = i;
		for (int j = i + 1; j < n; ++j) {
			if (arr[minVal_idx] > arr[j]) {
				minVal_idx = j;
			}
		}
		if (minVal_idx != i) {
			swapint(arr[i], arr[minVal_idx]);
		}
	}
}



// 插入排序的实现
static void InsertSort(vector<int>& arr) {
	int n = arr.size();
	if (n == 0) return;
	for (int i = 1; i < n; ++i) {
		int current_val = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > current_val) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = current_val;
	}
}



// 获取随机数组: 长度（0 ~ maxLen）、数据大小（0 ~ maxVal）
static vector<int> GetRandomArr() {
	vector<int> ret;
	int len = rand() % (MAXLEN + 1); // 定义随机到的数组长度
	int val = 0;
	for (int i = 0; i < len; ++i) {
		val = rand() % (MAXVAL + 1); // 随机生成数据
		ret.emplace_back(val); // 构造在数组尾部
	}
	return ret;
}



// 打印数组（用逗号分隔）
void PrintArr(vector<int> arr) {

	// 这里使用的迭代器遍历
	for (vector<int>::iterator it = arr.begin(); it < arr.end(); ++it) {
		cout << (*it);
		if (it + 1 != arr.end()) cout << ',';
	}

}



// 重新获取实验参数
void reSet() {
	system("cls");
	cout << "随机数组最大长度:"; cin >> MAXLEN;
	cout << "随机数组中最大数值:"; cin >> MAXVAL;
	cout << "随机次数:"; cin >> TIMES;
	cout << "是否展示实验过程（1/0）:"; cin >> SHOW;
}



// 终端的面板
void Panel() {
	system("cls");
	cout << "<<-- 基础排序与对数器实验 -->>" << endl;
	cout << "随机数组最大长度：" << MAXLEN << endl;
	cout << "随机数组中最大数值：" << MAXVAL << endl;
	cout << "随机次数：" << TIMES << endl;
	cout << "是否展示实验过程：";
	if (SHOW) {
		cout << "是" << endl;
	}
	else {
		cout << "否" << endl;
	}
	cout << "#输入 start 开始" << endl;
	cout << "#输入 change 修改对数器数值" << endl;
	cout << "#输入 end 退出" << endl;
}



// 判断两个数组是否相等
bool IsArrEqiup(const vector<int>& arr1, const vector<int>& arr2) {
	int n1 = arr1.size(), n2 = arr2.size();
	if (n1 != n2) return false;
	for (int i = 0; i < n1; ++i) {
		if (arr1[i] != arr2[i]) return false;
	}
	return true;
}



// 对数器实验
void Counter() {
	cout << "Text start ... " << endl;
	vector<int> orignal_arr;
	vector<int> Bubble_arr;
	vector<int> Select_arr;
	vector<int> Insert_arr;
	vector<int> sort_arr;
	for (int i = 0; i < TIMES; ++i) {
		// 获取初始数组
		int len = rand() % (MAXLEN + 1);
		orignal_arr = GetRandomArr();
		Bubble_arr = orignal_arr;
		Select_arr = orignal_arr;
		Insert_arr = orignal_arr;
		sort_arr = orignal_arr;
		// 调用排序方法
		BubbleSort(Bubble_arr);
		SelectSort(Select_arr);
		InsertSort(Insert_arr);
		sort(sort_arr.begin(), sort_arr.end());
		if (SHOW) {
			cout << endl << "text" << i + 1 << endl;
			cout << "orignal:\n"; PrintArr(orignal_arr); cout << endl;
			cout << "true sort:\n"; PrintArr(sort_arr); cout << endl;
			cout << "bubble sort:\n"; PrintArr(Bubble_arr); cout << endl;
			cout << "insert sort:\n"; PrintArr(Insert_arr); cout << endl;
			cout << "select sort:\n"; PrintArr(Select_arr); cout << endl;
		}
		if (!IsArrEqiup(sort_arr, Bubble_arr) || !IsArrEqiup(sort_arr, Select_arr) || !IsArrEqiup(sort_arr, Insert_arr)) {
			cout << "Error sort appearing !!!" << endl;
		}
	}
	cout << "Text end ... " << endl;
	system("pause");
}



// 主函数
int main() {

	//完成初始化
	srand((unsigned int)time(0));
	MAXLEN = MAXVAL = TIMES = 0;
	SHOW = false;
	string choice = "";

	do {
		Panel();
		cin >> choice;
		if (choice == "change") reSet();
		else if (choice == "start") Counter();
		else if (choice == "end") break;
		else {
			cout << "错误输入" << endl;
			system("pause");
		}
	} while (choice != "end");

}