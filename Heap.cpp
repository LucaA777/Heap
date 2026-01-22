#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

const int HEAP_SIZE = 201;


void insertNumberInHeap(int* &heap, int num);
int getLeftIndex(int index);
int getRightIndex(int index);
int getParentIndex(int index);
void zeroHeap(int* &heap);
void printHeap(int* heap);
void print(int* heap, int index, int depth);
string lowerCase(string str);
void processFile(int* &heap);
int removeHead(int* &heap);

int main() {

  int* heap = new int[HEAP_SIZE];

  string input;

  while (input != "quit") {
    cout << "Enter a command (Add, Print, File, Remove, RemoveAll, Quit):" << endl;
    cin >> input;
    input = lowerCase(input);

    try {
      int num = stoi(input);
      insertNumberInHeap(heap, num);
      printHeap(heap);
    }
    catch(...) {}
    
    if (input == "add") {
      int num = 0;
      cout << "Enter a number:" << endl;
      cin >> num;

      insertNumberInHeap(heap, num);
      printHeap(heap);
    }

    else if (input == "print") {
      printHeap(heap);
    }

    else if (input == "file") {
      processFile(heap);
      printHeap(heap);
    }

    else if (input == "remove") {
      removeHead(heap);
      printHeap(heap);
    }

    else if (input == "removeall") {
      while (removeHead(heap) != 0) {}
    }


  }	




  return 0;
}

void insertNumberInHeap(int* &heap, int num) {

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

string lowerCase(string str) {
  for (char& c : str) {
    c = tolower(c);
  }

  return str;
}

void processFile(int* &heap) {
  int num = 0;
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

}

int removeHead(int* &heap) {

  if (heap[1] == 0) {
    return 0;
  }

  int head = heap[1];

  int index = 1;
  while (heap[index] != 0) {
    if (heap[getLeftIndex(index)] > heap[getRightIndex(index)]) {
      heap[index] = heap[getLeftIndex(index)];
      index = getLeftIndex(index);
    }
    else {
      heap[index] = heap[getRightIndex(index)];
      index = getRightIndex(index);
    }
  }

  cout << "Removed: " << head << endl;
  return head;
}
