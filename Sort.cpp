#include "Sort.h"

void fSwap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

void fInsertionSort1(int* A, int n) {
	for (int i = 1; i < n; i++) {
		int key = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > key) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}
}

void fSelectionSort1(int* A, int n) {
	for (int i = 0; i < n-1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (A[j] < A[minIndex]) minIndex = j;
		}
		fSwap(A[i], A[minIndex]);
	}
}

void fBubbleSort1(int* A, int n) {
	for (int i = 1; i < n; i++) {
		int j = i;
		while (j > 0 && A[j] < A[j - 1]) {
			fSwap(A[j], A[j - 1]);
			j--;
		}
	}
}

void fPushDown(int* heap, int nHeap, int pos) {
	int key = heap[pos];
	while (pos * 2 + 1 < nHeap) {
		int c = pos * 2 + 1;
		if (c + 1 < nHeap && heap[c] < heap[c + 1]) c++;
		if (heap[c] < key) break;
		heap[pos] = heap[c];
		pos = c;
	}
	heap[pos] = key;
}

int fGetMaxHeap(int* heap, int& nHeap) {
	int ans = heap[0];
	heap[0] = heap[nHeap - 1];
	nHeap--;
	fPushDown(heap, nHeap, 0);
	return ans;
}

void fHeapSort1(int* A, int n) {
	for (int i = n - 1; i >= 0; i--) fPushDown(A, n, i);
	int nHeap = n;
	int i = n-1;
	while (nHeap != 0) {
		A[i] = fGetMaxHeap(A, nHeap);
		i--;
	}
}

void fQuickSort1(int* A, int left, int right) {
	if (left >= right) return;
	int key = A[(left + right) / 2];
	int l = left;
	int r = right;
	while (l < r) {
		while (A[l] < key) l++;
		while (A[r] > key) r--;
		if (l <= r) {
			fSwap(A[l], A[r]);
			l++;
			r--;
		}
	}
	fQuickSort1(A, left, r);
	fQuickSort1(A, l, right);
}

void fMergeSort1(int* A, int l, int r) {
	if (l >= r) return;
	int m = (l + r) / 2;
	fMergeSort1(A, l, m);
	fMergeSort1(A, m + 1, r);
	int* L = new int[m - l + 1];
	int* R = new int[r - m];
	for (int i = l; i <= m; i++) {
		L[i - l] = A[i];
	}
	for (int i = m + 1; i <= r; i++) {
		R[i - m - 1] = A[i];
	}
	int i = 0;
	int j = 0;
	int k = l;
	while (k <= r) {
		if (i == m - l + 1) {
			A[k] = R[j];
			j++;
		}
		else if (j == r - m) {
			A[k] = L[i];
			i++;
		}
		else if (L[i] < R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
		k++;
	}
	delete[]L;
	delete[]R;
}

void fInsertSortedList(node*& sortedHead, node*& sortedTail, node* cur) {
	cur->next = NULL;
	if (sortedHead == NULL) {
		sortedHead = sortedTail = cur;
		return;
	}
	if (cur->data < sortedHead->data) {
		// cur duoc chen dau list
		cur->next = sortedHead;
		sortedHead = cur;
	}
	else if (cur->data > sortedTail->data) {
		// cur duoc chen cuoi list
		sortedTail->next = cur;
		sortedTail = cur;
	}
	else {
		// cur duoc chen o giua list
		node* p = sortedHead;
		while (p->data < cur->data && p->next->data < cur->data) p = p->next;
		cur->next = p->next;
		p->next = cur;
	}

}

void fInsertionSort2(node*& head, node* &tail) {
	node* cur = head;
	node* sortedHead = NULL;
	node* sortedTail = NULL;
	while (cur != NULL) {
		node* oldCur = cur;
		cur = cur->next;
		fInsertSortedList(sortedHead, sortedTail, oldCur);
	}
	head = sortedHead;
	tail = sortedTail;
}

void fSelectionSort2(node* head, node* tail) {
	node* i = head;
	while (i != NULL) {
		node* j = i->next;
		node* minPointer = i;
		while (j != NULL) {
			if (j->data < minPointer->data) {
				minPointer = j;
			}
			j = j->next;
		}
		fSwap(i->data, minPointer->data);
		i = i->next;
	}
}

void fBubbleSort2(node* head, node* tail) {
	if (head == NULL) return;
	if (head == tail) return;
	node* end = tail;
	while (end != head) {
		node* start = head;
		while (true) {
			if (start->data > start->next->data) {
				fSwap(start->data, start->next->data);
			}
			if (start->next == end) break;
			start = start->next;
		}
		end = start;
		start = head;
	}
}

void fSplitList(node* head, node* tail, node*&mid, node*&beforeSlow) {
	node* fast = head;
	node* slow = head;
	beforeSlow = NULL;
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			fast = fast->next;
			beforeSlow = slow;
			slow = slow->next;
		}
	}
	mid = slow;
}

node* fSortedMerge(node* a, node* b, node*&tail) {
	if (a == NULL) return b;
	else if (b == NULL) return a;
	node* res = NULL;
	if (a->data <= b->data) {
		res = a;
		res->next = fSortedMerge(a->next, b, tail);
	}
	else {
		res = b;
		res->next = fSortedMerge(a, b->next, tail);
	}
	if (res->next == NULL) tail = res;
	return res;
}

void fMergeSort2(node*& head, node*& tail) {
	if (head == NULL) return;
	if (head == tail) return;
	node* mid, * beforeSlow;
	fSplitList(head, tail, mid, beforeSlow);
	beforeSlow->next = NULL;
	tail->next = NULL;
	fMergeSort2(head, beforeSlow);
	fMergeSort2(mid, tail);
	
	head=fSortedMerge(head, mid, tail);
}

node* fPartion(node* head, node* tail, node*& newHead, node*& newTail) {
	node* pivot = tail;
	newHead = NULL;
	newTail = NULL;
	node* prev = NULL;
	node* cur = head;
	while (cur != pivot) {
		if (cur->data < pivot->data) {
			if (newHead == NULL) newHead = cur;
			prev = cur;
			cur = cur->next;
		}
		else {
			if (prev != NULL) prev->next = cur->next;
			node* tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			
			tail = cur;
			cur = tmp;
		}
	}
	if (newHead == NULL) newHead = pivot;
	newTail = tail;
	return pivot;
}

void fQuickSort2(node*& head, node*& tail) {
	if (head == NULL || head == tail) return;
	node* newHead, * newTail;
	node* pivot = fPartion(head, tail, newHead, newTail);
	if (newHead != pivot) {
		node* tmp = newHead;
		while (tmp->next != pivot) tmp = tmp->next;
		tmp->next = NULL;
		fQuickSort2(newHead, tmp);
		tmp->next = pivot;
	}
	fQuickSort2(pivot->next, newTail);
	head = newHead;
	tail = newTail;
}