//Given sequence k = k1 <k2< …… <kn of n sorted keys, with a search probability pi for each key ki .
// Build the Binary search tree that has the least search cost given the access probability for each key? 

#include <iostream>
#include <limits>
using namespace std;

struct Node {
    int key;
    double probability;
    Node* left;
    Node* right;
   Node(int k, double p) 
	{
		key=k;
		probability=p;
		left=NULL;
		right=NULL;
	}
};

Node* constructOptimalBST(int keys[], double probabilities[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    double minCost = numeric_limits<double>::max();
    int rootIndex = -1;
    for (int i = start; i <= end; ++i) {
        double cost = 0;
        for (int j = start; j <= end; ++j) {
            if (j < i) {
                cost += probabilities[j];
            } else if (j > i) {
                cost += probabilities[j];
            } else {
                cost += probabilities[j];
            }
        }
        if (cost < minCost) {
            minCost = cost;
            rootIndex = i;
        }
    }
    Node* root = new Node(keys[rootIndex], probabilities[rootIndex]);
    root->left = constructOptimalBST(keys, probabilities, start, rootIndex - 1);
    root->right = constructOptimalBST(keys, probabilities, rootIndex + 1, end);

    return root;
}

void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    cout << "(" << root->key << ", " << root->probability << ") ";
    inorderTraversal(root->right);
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;
    int keys[n];
    double probabilities[n];
    cout << "Enter the keys and their probabilities:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> keys[i] >> probabilities[i];
    }
    Node* root = constructOptimalBST(keys, probabilities, 0, n - 1);
    cout << "Inorder traversal of the optimal binary search tree:" << endl;
    inorderTraversal(root);
    cout << endl;
    return 0;
}

//output:
//
//Enter the number of keys: 3
//Enter the keys and their probabilities:
//3 0.2
//1 0.5
//2 0.7
//Inorder traversal of the optimal binary search tree:
//(3, 0.2) (1, 0.5) (2, 0.7) 
