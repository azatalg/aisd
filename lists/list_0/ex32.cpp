#include <iostream>
#include <algorithm>
using namespace std;

// Struktura wierzchołka naszego mrocznego drzewa
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Funkcja pomocnicza, która oblicza wysokość drzewa
// oraz aktualizuje "średnicę cierpienia" (maksymalną odległość)
int diameterHelper(Node* root, int &diameter) {
    if (!root) return 0;
    int leftHeight = diameterHelper(root->left, diameter);
    int rightHeight = diameterHelper(root->right, diameter);
    
    // Aktualizujemy średnicę – suma wysokości lewego i prawego poddrzewa
    diameter = max(diameter, leftHeight + rightHeight);
    
    // Zwracamy wysokość tego fragmentu mrocznego świata
    return 1 + max(leftHeight, rightHeight);
}
 
// Funkcja obliczająca maksymalną odległość między wierzchołkami
int diameter(Node* root) {
    int dia = 0;
    diameterHelper(root, dia);
    return dia;
}
 
int main() {
    // Budujemy drzewo naszego wewnętrznego rozdarcia:
    //          1
    //         / \
    //        2   3
    //       / \   \
    //      4   5   6
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    
    int maxDistance = diameter(root);
    cout << "Maksymalna odległość między wierzchołkami: " << maxDistance << endl;
    // Jak echo naszych rozdartych dusz, niech to przypomina o cierpieniu... 🖤💀
    return 0;
}

