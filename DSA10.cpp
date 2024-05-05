/*Read the marks obtained by students of second year in an online examination of particular subject. 
Find out maximum and minimum marks obtained in that subject. Use heap data structure. Analyze the algorithm.*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
private:
    vector<int> heap;

    // Helper functions for heap operations
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    // Heapify up operation
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

   
public:
    // Insert value into heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    // Get maximum value from heap
    int getMax() {
        return heap.front();
    }

    // Get minimum value from heap
    int getMin() {
        return *min_element(heap.begin(), heap.end());
    }

    // Check if heap is empty
    bool isEmpty() {
        return heap.empty();
    }
};

int main() {
    Heap marksHeap;

    // Input number of students
    cout << "Enter the number of students: ";
    int numStudents;
    cin >> numStudents;

    // Input marks obtained by students
    cout << "Enter marks obtained by students:\n";
    for (int i = 0; i < numStudents; ++i) {
        int marks;
        cin >> marks;
        marksHeap.insert(marks);
    }

    // Calculate and display maximum and minimum marks
    if (!marksHeap.isEmpty()) {
        int maxMarks = marksHeap.getMax();
        int minMarks = marksHeap.getMin();

        cout << "Maximum marks obtained: " << maxMarks << endl;
        cout << "Minimum marks obtained: " << minMarks << endl;
        
    } else {
        cout << "No marks entered!\n";
    }

    return 0;
}
