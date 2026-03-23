// 这个程序将实现简单队列、堆与栈

// 作者：Saber（HaoqiangChen668）

// 使用工具：Visual Studio 2026

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;

static const int add_size = 10;

// 栈
template <typename T>
class myStack {

private:

	T* stack;
	int l, r;
	int stack_size;
	int cur_size;

public:

	myStack(int size) :stack_size(size) {
		l = r = cur_size = 0;
		stack = new T[size];
	}

	myStack(const myStack& other) {
		this->cur_size = other.cur_size;
		this->stack_size = other.stack_size;
		this->l = other.l;
		this->r = other.r;
		this->stack = new T[stack_size];
		for (int i = 0; i < cur_size; ++i) {
			this->stack[i] = other.stack[i];
		}
	}

	~myStack() {
		delete[] stack;
	}

	void rebuild(const vector<T>& arr) {
		delete[] stack;
		int n = arr.size();
		stack = new T[n + add_size];
		cur_size = n;
		stack_size = n + add_size;
		l = 0; 
		r = cur_size;
		for (int i = cur_size - 1; i >= 0; --i) {
			stack[i] = arr[i];
		}
	}

	int size()const {
		return cur_size;
	}

	int maxSize()const {
		return stack_size;
	}

	void resize(int size) {
		l = r = cur_size = 0;
		stack_size = size;
		delete[] stack;
		stack = new T[size];
	}

	bool empty()const {
		return cur_size == 0;
	}

	bool full()const {
		return cur_size == stack_size;
	}

	void push(T val) {
		if (full()) return;
		stack[r] = val;
		r = r + 1 == stack_size ? 0 : r + 1;
		cur_size++;
	}

	void pop() {
		if (empty()) return;
		r = r == 0 ? stack_size - 1 : r - 1;
		cur_size--;
	}

	T top()const {
		return r == 0 ? stack[stack_size - 1] : stack[r - 1];
	}

};


// 队列
template <typename T>
class myQueue {

private:

	T* queue;
	int l, r;
	int cur_size, queue_size;

public:

	myQueue(int size) :queue_size(size) {
		l = r = cur_size = 0;
		queue = new T[size];
	}

	myQueue(const myQueue& other) {
		this->cur_size = other.cur_size;
		this->queue_size = other.queue_size;
		this->l = other.l;
		this->r = other.r;
		this->queue = new T[queue_size];
		for (int i = 0; i < cur_size; ++i) {
			this->queue[i] = other.queue[i];
		}
	}

	~myQueue() {
		delete[] queue;
	}

	void resize(int size) {
		delete[] queue;
		queue = new T[size];
		cur_size = 0;
		queue_size = size;
		l = r = 0;
	}

	void rebuild(const vector<T>& arr) {
		delete[] queue;
		int n = arr.size();
		queue = new T[n + add_size];
		cur_size = n;
		queue_size = n + add_size;
		l = 0;
		r = cur_size;
		for (int i = 0; i < cur_size; ++i) {
			queue[i] = arr[i];
		}
	}

	int size()const {
		return cur_size;
	}

	int maxSize()const {
		return queue_size;
	}

	bool empty()const {
		return cur_size == 0;
	}

	bool full()const {
		return cur_size == queue_size;
	}

	void push(T val) {
		if (full()) return;
		l = l == 0 ? queue_size - 1 : l - 1;
		queue[l] = val;
		cur_size++;
	}

	void pop() {
		if (empty()) return;
		r = r == 0 ? queue_size - 1 : r - 1;
		cur_size--;
	}

	T front() const{
		return r == 0 ? queue[queue_size - 1] : queue[r - 1];
	}

	T back() const{
		return queue[l];
	}
};


// 默认小顶堆
template <typename T>
class less {
public:
	bool operator()(const T& a, const T& b) const{
		return a < b;
	}
};

// 改大顶堆
template <typename T>
class greater {
public:
	bool operator()(const T& a, const T& b) const {
		return a > b;
	}
};

// 堆
template <typename T, typename Compare = less<T>>
class myHeap {

private:

	T* heap;
	int cur_size, heap_size;
	Compare comp;

	// 上滤
	void swim(int site) {
		if (site == 0) return;
		int fatherNode = (site - 1) / 2;
		while (!comp(heap[fatherNode], heap[site])) {
			mySwap(heap[fatherNode], heap[site]);
			if (fatherNode == 0) break;
			site = fatherNode;
			fatherNode = (site - 1) / 2;
		}
	}

	// 下滤
	void sink(int site) {
		int childNode = site * 2 + 1;
		while (true) {
			if (childNode >= cur_size) break;
			if (childNode + 1 < cur_size) {
				childNode = comp(heap[childNode], heap[childNode + 1]) ? childNode : childNode + 1;
			}
			if (comp(heap[site], heap[childNode])) break;
			mySwap(heap[site], heap[childNode]);
			site = childNode;
			childNode = site * 2 + 1;
		}
	}

	// 下滤构建堆的有序
	void buildHeap() {
		for (int i = (cur_size - 2) / 2; i >= 0; --i) {
			sink(i);
		}
	}

	// 交换两数据
	void mySwap(T& val1, T& val2) {
		T temp = val1;
		val1 = val2;
		val2 = temp;
	}

public:

	myHeap(int size) :heap_size(size) {
		cur_size = 0;
		heap = new T[size];
	}

	myHeap(const vector<T>& arr) {
		cur_size = heap_size = arr.size();
		heap = new T[heap_size];
		for (int i = 0; i < cur_size; ++i) {
			heap[i] = arr[i];
		}
		buildHeap();
	}

	myHeap(const myHeap& other) {
		this->cur_size = other.cur_size;
		this->heap_size = other.heap_size;
		this->heap = new T[heap_size];
		for (int i = 0; i < cur_size; ++i) {
			this->heap[i] = other.heap[i];
		}
	}

	~myHeap() {
		delete[] heap;
	}

	void rebuild(const vector<T>& arr) {
		cur_size =arr.size();
		heap_size = cur_size + add_size;
		delete[] heap;
		heap = new T[heap_size];
		for (int i = 0; i < cur_size; ++i) {
			heap[i] = arr[i];
		}
		buildHeap();
	}

	void resize(int size) {
		cur_size = 0;
		heap_size = size;
		delete[] heap;
		heap = new T[size];
	}

	bool empty()const {
		return cur_size == 0;
	}

	bool full()const {
		return cur_size == heap_size;
	}

	void push(T val) {
		if (full()) return;
		heap[cur_size++] = val;
		swim(cur_size - 1);
	}

	void pop() {
		if (empty()) return;
		mySwap(heap[0], heap[cur_size - 1]);
		cur_size--;
		sink(0);
	}

	T top() {
		return heap[0];
	}

	int maxSize()const {
		return heap_size;
	}

	int size()const {
		return cur_size;
	}

};


static myStack<int> stack(10);
static myQueue<int> queue(10);
static myHeap<int> heap(10);

// 主函数

int main() {
	
	cout << "简单测试：" << endl;
	vector<int> arr = {
		93, 38, 71, 12, 61, 1, 88, 22, 40, 59, 101 
	};

	stack.rebuild(arr);
	queue.rebuild(arr);
	heap.rebuild(arr);

	stack.push(11);
	queue.push(5201314);
	heap.push(114514);

	cout << "stack:";
	while (!stack.empty()) {
		cout << stack.top() << ' ';
		stack.pop();
	}
	cout << endl;

	cout << "queue:";
	while (!queue.empty()) {
		cout << queue.front() << ' ';
		queue.pop();
	}
	cout << endl;

	cout << "heap:";
	while (!heap.empty()) {
		cout << heap.top() << ' ';
		heap.pop();
	}
	cout << endl;

}