#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int HEAP_SIZE = 201;


void insertNumberInHeap(int* heap, int num);
int getLeftIndex(int index);
int getRightIndex(int index);
int getParentIndex(int index);
void zeroHeap(int* heap);
void printHeap(int* heap);
void print(int* heap, int index, int depth);

int main() {

	int* heap = new int[HEAP_SIZE];

  cout << "Would you like to enter a file? (y/n)" << endl;

  string input;
  cin >> input;


  int num = 0;
  
  if (input == "y") {
    cout << "Enter the file name: " << endl;
    string fileName;
    cin >> fileName;

    fstream file(fileName);
    
    string numStr;
    int counter = 0;

    while (getline(file, numStr) && counter < HEAP_SIZE - 1) {
      num = stoi(numStr);
      cout << "Converted " << numStr << " into " << num << "." << endl;
      insertNumberInHeap(heap, num);
      counter++;
    }

    printHeap(heap);

  }



	while (true) {
		cout << "Please enter a number:" << endl;
		cin >> num;

		insertNumberInHeap(heap, num);

		printHeap(heap);
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

void printHeap(int* heap) {
	cout << "Heap:" << endl;
	print(heap, 1, 1);
	cout << endl;
}

void print(int* heap, int index, int depth) {

	if (heap[getRightIndex(index)] != 0) {
		print(heap, getRightIndex(index), depth + to_string(heap[index]).length() + 3);
	}

	for (int i = 0; i < depth; i++) {
		cout << " ";
	}	

	cout << heap[index];
	cout << endl;

	if (heap[getLeftIndex(index)] != 0) {
		print(heap, getLeftIndex(index), depth + to_string(heap[index]).length() + 3);
	}
}

