/*
  This program allows a user to create a max heap, which is a binary tree sorted with the 
  largest numbers towards the root, and implemented with an array rather than nodes. The 
  user is able to add numbers both manually and through files, as well as remove the head 
  or all nodes from the heap. 
  Author: Luca Ardanaz
  Last Update: 1/21/2026
*/
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

  //input loop
  while (input != "quit") {
    //asks for input
    cout << endl << endl;
    cout << "Enter a number to add or a command (Print, File, Remove, RemoveAll, Quit):" << endl;
    cin >> input;
    input = lowerCase(input);
    cout << endl;
    //attempts to process the input at a number and add it to the heap
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
      //repeatedly run remove function until the heap is empty
      while (removeHead(heap) != 0) {}
    }


  }	




  return 0;
}

//insets any number in heap sorted to have higher numbers towards the root
void insertNumberInHeap(int* &heap, int num) {

  //find first empty space
  int index = 0;
  for (int i = 1; i < HEAP_SIZE; i++) {
    if (heap[i] == 0) {
      index = i;
      break;
    }
  }

  //insert new number
  heap[index] = num;

  //check all parents to see if they need to be swapped
  //reuses index variable to track the current index
  while (heap[index] > heap[getParentIndex(index)] && index >  1) {
    int temp = heap[getParentIndex(index)];
    heap[getParentIndex(index)] = heap[index];
    heap[index] = temp;

    index = getParentIndex(index);
  }


} 

//fill the heap with zeros
void zeroHeap(int* heap) {
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

//caller for recursive printing
void printHeap(int* heap) {
  cout << "Heap:" << endl;
  print(heap, 1, 1);
  cout << endl;
}

//recursively prints tree
void print(int* heap, int index, int depth) {

  //prints everything to the right of an index first
  if (heap[getRightIndex(index)] != 0) {
    print(heap, getRightIndex(index), depth + 1);
  }

  //adds appropriate spacing
  for (int i = 0; i < depth - 1; i++) {
    cout << "\t";
  }	

  //prints index
  cout << heap[index];
  cout << endl;

  //then prints everything to the left
  if (heap[getLeftIndex(index)] != 0) {
    print(heap, getLeftIndex(index), depth + 1);
  }
}

string lowerCase(string str) {
  for (char& c : str) {
    c = tolower(c);
  }

  return str;
}

//reads a file and adds all values to the heap
void processFile(int* &heap) {
  int num = 0;

  //get the file name from the user
  cout << "Enter the file name: " << endl;
  string fileName;
  cin >> fileName;

  fstream file(fileName);

  string numStr;
  int counter = 0;

  //add each line of the file, if it can be converted to an integer
  while (getline(file, numStr) && counter < HEAP_SIZE - 1) {
    try {
      num = stoi(numStr);
      insertNumberInHeap(heap, num);
      counter++;
    }
    catch(...) {}
  }

}

int removeHead(int* &heap) {
  //if the heap is empty, return immediately 
  if (heap[1] == 0) {
    return 0;
  }

  int head = heap[1];

  //choose the larger side
  //copy that number into the current index
  //repeat again at that side
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
