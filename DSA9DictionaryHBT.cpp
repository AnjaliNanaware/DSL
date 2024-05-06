// Dictionary stores keywords & its meanings. Provide facility for adding new keywords, 
// deleting keywords, updating values of any entry. Provide facility to display whole data sorted
//  in ascending/ Descending order. Also find how many maximum comparisons may require for finding 
//  any keyword. Use Height balance tree and find the complexity for finding a keyword. 


#include <iostream>
#include <algorithm>
using namespace std;
struct Node {
    string keyword, meaning;
    int height;
    Node *left, *right;

	Node(string key, string val) {
	  keyword=key;
	  meaning=val;
	  height = 1;
	  left = NULL;
	  right = NULL;
	}
};
int height(Node* node) {
    return (node == NULL) ? 0 : node->height;
}
int getBalance(Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}
Node* rightRotate(Node* y) {
    Node *x = y->left, *T2 = x->right;
    x->right = y, y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
Node* leftRotate(Node* x) {
    Node *y = x->right, *T2 = y->left;
    y->left = x, x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
Node* insert(Node* root, string key, string val, int& cmp) {
    if (!root) return new Node(key, val);
    if (key < root->keyword) root->left = insert(root->left, key, val, ++cmp);
    else if (key > root->keyword) root->right = insert(root->right, key, val, ++cmp);
    else root->meaning = val;
    root->height = 1 + max(height(root->left), height(root->right));
    int bal = getBalance(root);
    if (bal > 1 && key < root->left->keyword) return rightRotate(root);
    if (bal < -1 && key > root->right->keyword) return leftRotate(root);
    if (bal > 1 && key > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bal < -1 && key < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
Node* minValueNode(Node* node) {
    Node* curr = node;
    while (curr && curr->left) curr = curr->left;
    return curr;
}
Node* deleteNode(Node* root, string key, int& cmp) {
    if (!root) return root;
    if (key < root->keyword) root->left = deleteNode(root->left, key, ++cmp);
    else if (key > root->keyword) root->right = deleteNode(root->right, key, ++cmp);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword, cmp);
        }
    }
    if (!root) return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int bal = getBalance(root);
    if (bal > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (bal < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (bal > 1 && getBalance(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (bal < -1 && getBalance(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }
    return root;
}
Node* search(Node* root, string key, int& cmp) {
    while (root) {
        ++cmp;
        if (key == root->keyword) return root;
        else if (key < root->keyword) root = root->left;
        else root = root->right;
    }
    return nullptr;
}
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->keyword << ": " << root->meaning << endl;
    inorder(root->right);
}
void reverseInorder(Node* root) {
    if (!root) return;
    reverseInorder(root->right);
    cout << root->keyword << ": " << root->meaning << endl;
    reverseInorder(root->left);
}
int main() {
    Node* root = nullptr;
    int cmp = 0;

    cout << "Enter keyword and meaning (type 'exit' to stop):\n";
    while (true) {
        string key, val;
        cin >> key;
        if (key == "exit") break;
        cin.ignore(); 
        getline(cin, val);
        root = insert(root, key, val, cmp);
    }
    cout << "\nInorder traversal (ascending order):\n";
    inorder(root);
    cout << "\nReverse Inorder traversal (descending order):\n";
    reverseInorder(root);
    string searchKey = "banana";
    Node* result = search(root, searchKey, cmp);
    if (result) cout << "\nMeaning of " << searchKey << ": " << result->meaning << endl;
    else cout << "Keyword '" << searchKey << "' not found." << endl;
    cout << "\nMaximum comparisons for finding a keyword: " << cmp << endl;
    return 0;
}
//output:
//
//Enter keyword and meaning (type 'exit' to stop):
//123 raw
//23 tre
//456 fr
//exit
//
//Inorder traversal (ascending order):
//123: raw
//23: tre
//456: fr
//
//Reverse Inorder traversal (descending order):
//456: fr
//23: tre
//123: raw
//Keyword 'banana' not found.
//
//Maximum comparisons for finding a keyword: 5
