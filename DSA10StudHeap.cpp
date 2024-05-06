/*Read the marks obtained by students of second year in an online examination of particular subject. 
Find out maximum and minimum marks obtained in that subject. Use heap data structure. Analyze the algorithm.*/

#include <iostream>
using namespace std;
// Function to heapify the array as a max heap
void maxHeapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        maxHeapify(arr, n, largest);
    }
}

// Function to build max heap
void buildMaxHeap(int arr[], int n) {
    // Index of the last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal from the last non-leaf node
    // and heapify each node
    for (int i = startIdx; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
    
    for(int i=0;i<n;i++)
    {
    	cout<<arr[i]<<"\n";
	}
}

// Function to heapify the array as a min heap
void minHeapify(int arr[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is smaller than root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);

        // Recursively heapify the affected sub-tree
        minHeapify(arr, n, smallest);
    }
}

// Function to build min heap
void buildMinHeap(int arr[], int n) {
    // Index of the last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal from the last non-leaf node
    // and heapify each node
    for (int i = startIdx; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
    
    for(int i=0;i<n;i++)
    {
    	cout<<arr[i]<<"\n";
	}
}

// Function to find maximum and minimum marks
void findMaxMinMarks(int arr[], int n) {
    // Build max heap
    buildMaxHeap(arr, n);

    // Maximum marks will be at root of max heap
    cout << "Maximum Marks: " << arr[0] << std::endl;

    // Build min heap
    buildMinHeap(arr, n);

    // Minimum marks will be at root of min heap
    cout << "Minimum Marks: " << arr[0] << std::endl;
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    int *marks = new int[n];

    cout << "Enter the marks obtained by each student:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Student " << i + 1 << ": ";
    	cin >> marks[i];
    }

    findMaxMinMarks(marks, n);

    delete[] marks;
    return 0;
}
