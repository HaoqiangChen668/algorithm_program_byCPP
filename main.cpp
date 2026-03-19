#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
void PrintfArr(const vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i];
		if (i != arr.size()-1)cout << ',';
		if (i == arr.size() - 1)cout << '\n';
	}
}
vector<int> RadomArr(int n, int v) {
	vector<int> arr;
	for (int i = 0; i < n; i++) {
		int temp = rand() % (v + 1);
		arr.push_back(temp);
	}
	return arr;
}
void swap(vector<int>& arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void BubbleSort(vector<int>& arr) {
	int n = arr.size();
	if (n == 0)return;
	for (int i = 0; i < n - 1; i++) {
		bool end = true;
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);
				end = false;
			}
		}
		if (end)break;
	}
}
void SelectionSort(vector<int>& arr) {
	int n = arr.size();
	if (n == 0)return;
	for (int min_idx,i = 0; i < n - 1; i++) {
		min_idx = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[min_idx] > arr[j]) {
				min_idx = j;
			}
		}
		swap(arr, min_idx, i);
	}
}
void InsertSort(vector<int>& arr) {
	int n = arr.size();
	if (n == 0)return;
	for (int i = 1; i < n; i++) {
		int temp = arr[i]; int j = i - 1;
		while (j >= 0 && arr[j] > temp) {
			arr[j + 1] = arr[j]; j--;
		}
		arr[j + 1] = temp;
	}
}
void PrintList(const int& N,const int& V,const int& T) {
	system("cls");
	cout << "<<——三傻排序对数器——>>\n";
	cout << "随机数组最大长度：" << N << "\n";
	cout << "随机数组中最大数值：" << V << "\n";
	cout << "随机次数：" << T << "\n";
	cout << "#输入“start”开始\n";
	cout << "#输入“change”修改对数器数值\n";
	cout << "#输入“end”退出\n";
}
void Input(int& N, int& V, int& T) {
	cout << "随机数组最大长度："; cin >> N;
	cout << "随机数组中最大数值："; cin >> V;
	cout << "随机次数："; cin >> T;
}
bool ArrEqiup(const vector<int>& arr1, const vector<int>& arr2) {
	int n1 = arr1.size(); int n2 = arr2.size();
	if (n1 != n2)return false;
	for (int i = 0; i < n1; i++) {
		if (arr1[i] != arr2[i])return false;
	}
	return true;
}
void Text(const int& N, const int& V, const int& T) {
	cout << "Texting...\n";
	for (int i = 0; i < T; i++) {
		int n = rand() % (N + 1);
		vector<int> arr = RadomArr(n, V);
		vector<int> arr1(arr);
		vector<int> arr2(arr);
		vector<int> arr3(arr);
		vector<int> arr4(arr);
		BubbleSort(arr1);
		SelectionSort(arr2);
		InsertSort(arr3);
		sort(arr4.begin(), arr4.end());
		if (1) {
			cout << "text" << i + 1 << '\n';
			PrintfArr(arr);
			PrintfArr(arr1);
			PrintfArr(arr2);
			PrintfArr(arr3);
			PrintfArr(arr4);
		}
		if (!ArrEqiup(arr1, arr4) || !ArrEqiup(arr2, arr4) || !ArrEqiup(arr3, arr4)) {
			cout << "Worry appearing!!!\n";
		}
	}
	cout << "Text end...\n";
	string temp; if (cin >> temp)return;
}
int main() {
	srand((unsigned int)time(0));
	int N = 0, V = 0, T = 0;
	string choice("");
	do {
		PrintList(N, V, T);
		cin >> choice;
		if (choice == "change") Input(N, V, T);
		else if (choice == "start") Text(N, V, T);
		else if (choice == "end")break;
	} while (choice!="end");
	return 0;
}