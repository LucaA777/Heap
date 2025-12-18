#include <iostream>

using namespace std;

const int HEAP_SIZE = 101;


void insertNumberInHeap(int* heap, int num);
int getLeftIndex(int index);
int getRightIndex(int index);
int getParentIndex(int index);
void zeroHeap(int* heap);

int main() {

	int* heap = new int[HEAP_SIZE];

	int num = 0;

	while (true) {
		cout << "Please enter a number:" << endl;
		cin >> num;

		insertNumberInHeap(heap, num);

		cout << "Heap: " << heap << endl;

	}	

	


	return 0;
}

void insertNumberInHeap(int* heap, int num) {
	
	//find first empty space
	int index = 0;
	for (int i = 1; i < HEAP_SIZE; i++) {
		if (heap[i] == 0) {
			index = i;
			break;
		}
	}
	
	cout << "Found empty spot at " << index << endl;
	//insert new number
	heap[index] = num;

	//check all parents to see if they need to be swapped
	//reuses index variable to track the current index
	while (heap[index] > heap[getParentIndex(index)] && index >  1) {
		int temp = heap[getParentIndex(index)];
		heap[getParentIndex(index)] = heap[index];
		heap[index] = temp;
		
		index = getParentIndex(index);
		
		cout << "Swapped with parent" << endl;
		cout << "Now at index " << index << endl;
	}

} 

void zeroHeap(int * heap) {
	for (int i = 0; i < HEAP_SIZE; i++) {
		heap[i] = 0;
	}		
}

int getLeftIndex(int index) {
	return index * 2;
}

int getRightIndex(int index) {
	return index * 2 + 1;
}

int getParentIndex(int index) {
	return index / 2 > 0 ? index / 2 : 1;
}

