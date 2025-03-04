#include <iostream>
#include <algorithm>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

int countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int diameterHelper(Node* root, int &diameter) {
    if (!root) return 0;
    int leftHeight = diameterHelper(root->left, diameter);
    int rightHeight = diameterHelper(root->right, diameter);
    
    diameter = max(diameter, leftHeight + rightHeight);
    
    return 1 + max(leftHeight, rightHeight);
}
 
int diameter(Node* root) {
    int dia = 0;
    diameterHelper(root, dia);
    return dia;
}

int main() {
    // Construct a sample tree, each node an echo of internal turmoil:
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    std::cout << "Count of nodes (souls): " << countNodes(root) << std::endl;
    std::cout << "Diameter (longest path of despair): " << diameter(root) << std::endl;

    delete root->left->left;
    delete root->left->right;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}

