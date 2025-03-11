#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Wstawianie klucza do drzewa
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Znalezienie minimalnego węzła w poddrzewie
Node* minValueNode(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Usuwanie węzła z drzewa
Node* remove(Node* root, int key) {
    if (!root) return root;
    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
    }
    return root;
}

// Znalezienie następnego klucza
Node* findSuccessor(Node* root, int key) {
    Node* successor = nullptr;
    while (root) {
        if (key < root->key) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return successor;
}

// Funkcja pomocnicza do wyświetlania drzewa (inorder)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;
    
    root = remove(root, 50);
    cout << "After deletion: ";
    inorder(root);
    cout << endl;
    
    Node* successor = findSuccessor(root, 40);
    if (successor)
        cout << "Successor of 40: " << successor->key << endl;
    else
        cout << "No successor found." << endl;
    
    return 0;
}

