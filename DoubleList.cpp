// 本程序展示双向链表的增删改查以及一些基础的扩展

// 作者：Saber（HaoqiangChen668）

// 使用工具： Visual Studio 2026

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<unordered_map>
#include<unordered_set>
#include<string>
#define INT_MAX 2147483647

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::to_string;


// 链表节点的定义
template <typename T>
class ListNode {
public:
	T val;
	ListNode* next;
	ListNode* last;
	ListNode(T val) :val(val), next(nullptr), last(nullptr) {}
	ListNode(T val, ListNode* next, ListNode* last) :val(val), next(next), last(last) {}
};



// 定义一个类，包含链表的所有算法
template <typename T>
class myList {

private:

	ListNode<T>* head;
	ListNode<T>* tail;
	int list_size;

	unordered_map<T, int> counter;

	// 将节点B插入到A之后
	void InsertAfter(ListNode<T>* A, ListNode<T>* B) {
		B->next = A->next;
		A->next->last = B;
		A->next = B;
		B->last = A;
	}

	// 删除该节点的下一个节点
	void deleteNext(ListNode<T>* node) {
		if (node->next == tail) return;
		else {
			ListNode<T>* Next = node->next;
			node->next->next->last = node;
			node->next = node->next->next;
			delete Next;
		}
	}

	// 反转单个节点
	void reverseSingleNode(ListNode<T>* node) {
		ListNode<T>* nextNode = node->next;
		node->next = node->last;
		node->last = nextNode;
	}


	// 这些是归并排序的相关函数
	// //节点脱离
	void removeNode(ListNode<T>* node) {
		node->next->last = node->last;
		node->last->next = node->next;
	}
	//将一段链表插入到某一节点后
	void insertListAfterNode(ListNode<T>* headA, ListNode<T>* tailA, ListNode<T>* B) {
		headA->last->next = tailA->next;
		tailA->next->last = headA->last;
		B->next->last = tailA;
		tailA->next = B->next;
		headA->last = B;
		B->next = headA;
	}
	//找到node的step的尾节点
	ListNode<T>* findEnd(ListNode<T>* node, int step) {
		while (--step && node->next != tail) node = node->next;
		return node;
	}
	//merge过程
	ListNode<T>* merge(ListNode<T>* l1, ListNode<T>* r1, ListNode<T>* l2, ListNode<T>* r2) {
		ListNode<T>* theNext = nullptr;
		ListNode<T>* l1End = r1->next;
		ListNode<T>* l2End = r2->next;
		ListNode<T>* cur = l1->val < l2->val ? l1 : l2;
		ListNode<T>* ret = cur;

		l1 = l1 == cur ? l1->next : l1;
		l2 = l2 == cur ? l2->next : l2;

		while (l1 != l1End && l2 != l2End) {
			theNext = l1->val < l2->val ? l1 : l2;
			l1 = l1 == theNext ? l1->next : l1;
			l2 = l2 == theNext ? l2->next : l2;
			removeNode(theNext);
			InsertAfter(cur, theNext);
			cur = theNext;
		}
		if (l1 == l1End) insertListAfterNode(l2, r2, cur);
		else insertListAfterNode(l1, r1, cur);
		return ret;
	}


public:


	// 构造函数
	myList() {
		head = new ListNode<T>(0);
		tail = new ListNode<T>(0);
		head->next = tail;
		tail->last = head;
		list_size = 0;
		counter.clear();
	}


	// 拷贝构造函数
	myList(const myList<T>& other) {
		head = new ListNode(0);
		tail = new ListNode(0);
		this->list_size = other.size();
		this->counter = other.counter;
		ListNode<T>* cur = other.head->next;
		ListNode<T>* node = nullptr;
		while (cur != other.tail) {
			node = new ListNode<T>(cur->val);
			this->InsertAfter(tail->last, node);
			cur = cur->next;
		}
	}


	// 析构函数
	~myList() {
		ListNode<T>* cur = head;
		while (cur != nullptr) {
			ListNode<T>* next_node = cur->next;
			delete cur;
			cur = next_node;
		}
	}


	// 返回大小
	int size() const {
		return list_size;
	}


	// 返回为空
	bool empty() const {
		return list_size == 0;
	}


	// 清空链表
	void clear() {
		ListNode<T>* cur = head->next;
		while (cur != tail) {
			ListNode<T>* next_node = cur->next;
			delete cur;
			cur = next_node;
		}
		head->next = tail;
		tail->last = head;
		list_size = 0;
		counter.clear();
	}


	// 头部新增
	void push_front(T val) {
		ListNode<T>* node = new ListNode<T>(val);
		InsertAfter(head, node);
		list_size++;
		if (counter.count(val) == 0) {
			counter[val] = 1;
		}
		else {
			counter[val]++;
		}
	}


	// 尾部新增
	void push_back(T val) {
		ListNode<T>* node = new ListNode<T>(val);
		InsertAfter(tail->last, node);
		list_size++;
		if (counter.count(val) == 0) {
			counter[val] = 1;
		}
		else {
			counter[val]++;
		}
	}


	// 插入一个数据
	void insert(T val, int pos) {
		if (pos < 0) return;
		if (pos >= size()) {
			push_back(val);
		}
		else {
			ListNode<T>* cur = head;
			ListNode<T>* node = new ListNode<T>(val);
			while (pos-- > 0) cur = cur->next;
			InsertAfter(cur, node);
			list_size++;
			if (counter.count(val) == 0) {
				counter[val] = 1;
			}
			else {
				counter[val]++;
			}
		}
	}


	// 插入若干相同数据
	void insert(int n, T val, int pos) {
		if (pos < 0) return;
		if (pos >= size()) {
			list_size += n;
			while (n-- > 0) push_back(val);
		}
		else {
			list_size += n;
			if (counter.count(val) == 0) {
				counter[val] = n;
			}
			else {
				counter[val] += n;
			}
			ListNode<T>* cur = head;
			while (pos-- > 0) cur = cur->next;
			while (n-- > 0) {
				ListNode<T>* node = new ListNode<T>(val);
				InsertAfter(cur, node);
			}
		}
	}


	// 删除头部
	void pop_front() {
		if (empty()) return;
		T val = head->next->val;
		if (counter[val] == 1) counter.erase(val);
		else counter[val]--;
		deleteNext(head);
		list_size--;
	}


	// 删除尾部
	void pop_back() {
		if (empty()) return;
		T val = tail->last->val;
		if (counter[val] == 1) counter.erase(val);
		else counter[val]--;
		deleteNext(tail->last->last);
		list_size--;
	}


	// 删除指定位置元素
	void erase(int pos) {
		if (empty() || pos < 0 || pos >= size()) return;
		if (pos == 0) {
			pop_front();
		}
		else if (pos + 1 == size()) {
			pop_back();
		}
		else {
			ListNode<T>* cur = head;
			while (pos-- > 0) cur = cur->next;
			T val = cur->next->val;
			if (counter[val] == 1) counter.erase(val);
			else counter[val]--;
			deleteNext(cur);
			list_size--;
		}
	}


	// 删除指定区间元素
	void erase(int pos1, int pos2) {
		if (pos1 > pos2) return;
		int n = pos2 - pos1 + 1;
		if (pos1 <= 0 && pos2 >= size() - 1) {
			clear();
		}
		else if (pos1 <= 0) {
			for (int i = 0; i <= pos2; ++i) {
				T val = head->next->val;
				if (counter[val] == 1) counter.erase(val);
				else counter[val]--;
				deleteNext(head);
			}
			list_size -= (pos2 + 1);
		}
		else if (pos2 >= size() - 1) {
			ListNode<T>* cur = head;
			for (int i = 0; i < pos1; ++i) {
				cur = cur->next;
			}
			while (cur->next != tail) {
				T val = cur->next->val;
				if (counter[val] == 1) counter.erase(val);
				else counter[val]--;
				deleteNext(cur);
			}
			list_size = pos1 + 1;
		}
		else {
			ListNode<T>* cur = head;
			for (int i = 0; i < pos1; ++i) {
				cur = cur->next;
			}
			for (int i = 0; i < n; ++i) {
				T val = cur->next->val;
				if (counter[val] == 1) counter.erase(val);
				else counter[val]--;
				deleteNext(cur);
			}
			list_size -= n;
		}
	}


	// 删除所有值为val的元素
	void remove(T val) {
		if (empty()) return;
		ListNode<T>* cur = head->next;
		while (cur != tail) {
			if (cur->val == val) {
				cur = cur->last;
				deleteNext(cur);
				list_size--;
			}
			cur = cur->next;
		}
		counter.erase(val);
	}


	// 修改头部元素的值
	void replace_front(T val) {
		if (empty()) return;
		T orignal_val = head->next->val;
		if (counter[orignal_val] == 1) counter.erase(orignal_val);
		else counter[orignal_val]--;
		head->next->val = val;
		if (counter.count(val) == 0) {
			counter[val] = 1;
		}
		else {
			counter[val]++;
		}
	}


	// 修改尾部元素的值
	void replace_back(T val) {
		if (empty()) return;
		T orignal_val = tail->last->val;
		if (counter[orignal_val] == 1) counter.erase(orignal_val);
		else counter[orignal_val]--;
		tail->last->val = val;
		if (counter.count(val) == 0) {
			counter[val] = 1;
		}
		else {
			counter[val]++;
		}
	}


	// 修改指定位置的元素值
	void replace(T val, int pos) {
		if (empty()) return;
		if (pos < 0 || pos >= size()) return;
		ListNode<T>* cur = head->next;
		for (int i = 0; i < pos; ++i) {
			cur = cur->next;
		}
		cur->val = val;
	}


	// 某元素存在
	bool have(T val) {
		return counter.count(val) == 1;
	}


	// 某元素的数量
	int count(T val) {
		if (!have(val)) return 0;
		return counter[val];
	}


	// 元素所在最左下标，没有就返回-1
	int find_index(T val) {
		if (empty() || !have(val)) return -1;
		ListNode<T>* cur = head->next;
		int result = 0;
		while (cur->val != val) {
			result++;
			cur = cur->next;
		}
		return result;
	}


	// 元素所在最右下标，没有就返回-1
	int rfind_index(T val) {
		if (empty() || !have(val)) return -1;
		ListNode<T>* cur = tail->last;
		int result = size() - 1;
		while (cur->val != val) {
			result--;
			cur = cur->last;
		}
		return result;
	}


	// 下标所对应元素，没有就返回int类型最大值
	T find_val(int pos) {
		if (pos < 0 || pos >= size()) return INT_MAX; // 这里其实不应该这样返回，因为T不一定就是int类型
		ListNode<T>* cur = head->next;
		for (int i = 0; i < pos; ++i) {
			cur = cur->next;
		}
		return cur->val;
	}


	// 反转链表
	void reverse() {
		// 为了练习coding能力，采用了传统的反转，是O(n)的时间复杂度
		// 其实可以用一个全局变量来控制是否反转的，可以做到O(1)的时间复杂度
		if (empty()) return;
		ListNode<T>* cur = head->next;
		while (cur != tail) {
			ListNode<T>* nextNode = cur->next;
			reverseSingleNode(cur);
			cur = nextNode;
		}
		tail->next = tail->last;
		tail->last = nullptr;
		head->last = head->next;
		head->next = nullptr;
		cur = tail;
		tail = head;
		head = cur;
	}


	// 链表去除重复元素
	void unique() {
		unordered_set<T> set;
		ListNode<T>* cur = head->next;
		while (cur != tail) {
			counter[cur->val] = 1;
			if (set.count(cur->val) == 1) {
				cur = cur->last;
				deleteNext(cur);
				list_size--;
			}
			else {
				set.insert(cur->val);
			}
			cur = cur->next;
		}
	}

	// 升序排序
	void sort() {

		//不符合排序条件直接返回
		if (empty() || size() == 1) return;

		//初始化各变量
		ListNode<T>* l1 = nullptr;
		ListNode<T>* r1 = nullptr;
		ListNode<T>* l2 = nullptr;
		ListNode<T>* r2 = nullptr;
		ListNode<T>* theNext = nullptr;

		//排序过程
		for (int step = 1; step < size(); step <<= 1) {
			l1 = head->next;
			r1 = findEnd(l1, step);
			l2 = r1->next;
			if (l2 == tail) break;
			r2 = findEnd(l2, step);
			theNext = r2->next;
			merge(l1, r1, l2, r2);
			while (theNext != tail) {
				l1 = theNext;
				r1 = findEnd(l1, step);
				l2 = r1->next;
				if (l2 == tail) break;
				r2 = findEnd(l2, step);
				theNext = r2->next;
				merge(l1, r1, l2, r2);
			}
		}

	}


	// 重载+=运算符，合并两个链表
	myList& operator+=(const myList& other) {
		myList copy(other);
		ListNode<T>* cur = copy.head->next;
		this->list_size += copy.list_size;
		this->tail->last->next = copy.head->next;
		copy.head->next->last = this->tail->last;
		delete this->tail;
		delete copy.head;
		this->tail = copy.tail;
		while (cur != copy.tail) {
			if (this->counter.count(cur->val) == 0) {
				this->counter[cur->val] = 1;
			}
			else {
				this->counter[cur->val]++;
			}
			cur = cur->next;
		}
	}


	// 方便打印数组的一个函数
	vector<T> arr() {
		vector<T> ret;
		ListNode<T>* cur = head->next;
		while (cur != tail) {
			ret.emplace_back(cur->val);
			cur = cur->next;
		}
		return ret;
	}
};



static vector<int> vals;
static myList<int> list;

// 获取随机链表
static void random(int maxlen, int maxval) {
	int len = rand() % (maxlen + 1);
	for (int i = 0; i < len; ++i) {
		int val = rand() % (maxval + 1);
		list.push_back(val);
	}
}

// 链表的打印
static void printlist() {
	vals = list.arr();

	const string s0 = " <-> ";
	const string s1 = "head";
	const string s2 = "tail";
	const string s3 = "null";
	const string s4 = "     ";
	
	cout << s3 << s0;
	for (int i = 0; i < vals.size(); ++i) {
		cout << vals[i] << s0;
	}
	cout << s3 << endl;

	cout << s1 << s4;
	for (int i = 0; i < vals.size(); ++i) {
		int n = to_string(vals[i]).size() - to_string(i).size();
		while (n-- > 0) cout << ' ';
		cout << i << s4;
	}
	cout << s2;
}

// 面板
static void panel() {
	system("cls");
	cout << "<<------- 双向链表 ------->>" << endl;
	cout << "# 温馨提示：上面的是节点和数据，下面是下标~" << endl;
	cout << "# 会有一个提供的初始链表~清空请输入8~" << endl << endl;
	printlist();cout << endl << endl;
	cout << "# 提供一些操作来操作链表：" << endl;
	cout << "# 说明：比如我想在头部插入一个数字520，就输入“1 1 520”" << endl;
	cout << "# 这只能展示一部分功能，更多功能请看源码~" << endl << endl;
	cout << "# 0 - - - 结束程序" << endl;
	cout << "# 1 - 1 - 在尾部插入一个数据（push_back）" << endl;
	cout << "#     2 - 在头部插入一个数据（push_front）" << endl;
	cout << "#     3 - 插入一个数据（insert）（先写数据再写下标）" << endl;
	cout << "# 2 - 1 - 删除尾部元素（pop_back）" << endl;
	cout << "#     2 - 删除头部元素（pop_front）" << endl;
	cout << "#     3 - 删除指定下标的元素（erase)" << endl;
	cout << "#     4 - 删除区间下标的元素（erase)（下标按照次序写）" << endl;
	cout << "# 3 - 1 - 更改尾部元素值（replace_back）" << endl;
	cout << "#     2 - 更改头部元素值（replace_front）" << endl;
	cout << "#     3 - 更改指定下标元素值（replace）（先写数据再写下标）" << endl;
	cout << "# 4 - - - 去除与你写入的值相同的节点（remove）" << endl;
	cout << "# 5 - - - 反转链表（reverse）" << endl;
	cout << "# 6 - - - 链表升序排序（sort）" << endl;
	cout << "# 7 - - - 链表去重（sort）" << endl;
	cout << "# 8 - - - 清空链表（clear）" << endl;
	cout << "# 9 - - - 获取随机链表（random）（依次写最大长度、最大数值）" << endl << endl;
}

// 主函数
int main() {

	srand((unsigned int)time(0));
	int input = 0;
	list.push_back(520);
	list.push_back(1314);
	list.push_back(666);
	list.push_back(888);

	do {
		panel();
		cin >> input;
		switch (input) {
		case 0:break;
			// 增
		case 1: {
			int a1; cin >> a1;
			switch (a1) {
				case 1: {
					int val; cin >> val;
					list.push_back(val);
					break;
				}
				case 2: {
					int val; cin >> val;
					list.push_front(val);
					break;
				}
				case 3: {
					int val, pos;
					cin >> val >> pos;
					list.insert(val, pos);
					break;
				}
				default: {
					cout << "# 错误输入~";
					system("pause");
					break;
				}
			}
			break;
		}
			  // 删
		case 2: {
			int a1; cin >> a1;
			switch (a1) {
			case 1: {
				list.pop_back();
				break;
			}
			case 2: {
				list.pop_front();
				break;
			}
			case 3: {
				int pos;
				cin >> pos;
				list.erase(pos);
				break;
			}
			case 4: {
				int pos1, pos2;
				cin >> pos1 >> pos2;
				list.erase(pos1, pos2);
				break;
			}
			default: {
				cout << "# 错误输入~";
				system("pause");
				break;
			}
			}
			break;
		}
			  // 改
		case 3: {
			int a1; cin >> a1;
			switch (a1) {
			case 1: {
				int val; cin >> val;
				list.replace_back(val);
				break;
			}
			case 2: {
				int val; cin >> val;
				list.replace_front(val);
				break;
			}
			case 3: {
				int val, pos;
				cin >> val >> pos;
				list.replace(val, pos);
				break;
			}
			default: {
				cout << "# 错误输入~";
				system("pause");
				break;
			}
			}
			break;
		}
		case 4: {
			int val; cin >> val;
			list.remove(val);
			break;
		}
		case 5: {
			list.reverse();
			break;
		}
		case 6: {
			list.sort();
			break;
		}
		case 7: {
			list.unique();
			break;
		}
		case 8: {
			list.clear();
			break;
		}
		case 9: {
			list.clear();
			int maxlen, maxval;
			cin >> maxlen >> maxval;
			random(maxlen, maxval);
			break;
		}
		default: {
			cout << "# 错误输入~";
			system("pause");
			break;
		}
		}
	} while (input != 0);
}