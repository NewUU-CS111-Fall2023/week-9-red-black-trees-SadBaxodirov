#include <iostream>
using namespace std;
enum Color {
    RED,
    BLACK
};
string result = "";

class Node {
public:
    int data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
    Node(int val, Color col = RED, Node* par = nullptr, Node* l = nullptr, Node* r = nullptr)
            : data(val), color(col), parent(par), left(l), right(r) {}
};

class RedBlackTree {
public:
private:
    Node* root;
    Node* nil; // Sentinel node
    void leftRotate(Node* x){// Big O(1), no recursive calls, no loops so only fixed amount of operations
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(Node* y){// Big O(1), no recursive calls, no loops so only fixed amount of operations
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nil) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }
    void insertFix(Node* z){// Big O(log(n)) where n is the number of nodes. The code looks through each node
        while (z->parent != nil && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    void deleteNode(Node* z){//Big O(log(n)) where n is the number of nodes in the RB tree
        Node* y = z;
        Node* x;
        Color y_original_color = y->color;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (y_original_color == BLACK) {
            deleteFixup(x);
        }

        delete z;
    }
    void deleteFixup(Node* x){// Big O(log(n)) where n is the number of nodes of RB tree
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    Node* minimum(Node* x) const{//worst case - Big O(n) if all elements of the RB tree are on the left
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }
    void transplant(Node* u, Node* v){//Big O(1), no recursion or loops
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    void printTree(Node* root) const{// Big O(n) where n is the number of nodes in RB tree
        if (root == nil) {
            return;
        }

        cout<<"(" << root->data << "(" << (root->color == RED ? "RED" : "BLACK") << ")";

        printTree(root->left);
        printTree(root->right);
        cout<<")";
    }
public:
    RedBlackTree(){
        nil = new Node(0, BLACK);
        root = nil;
    }
    void insert1(int key){ // Big O(log(n)) where n is the number of nodes in the RB tree
        if (root == nil){
            root->data=key;
            root->color = BLACK;
            root->left = nil;
            root->right = nil;
        }
        Node* z = new Node(key);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->color = RED;
        root->color = BLACK;

    }
    void insert2(int key){// Big O(log(n)) where n is the number of nodes in the RB tree
        if (root == nil){
            root->data=key;
            root->color = BLACK;
            root->left = nil;
            root->right = nil;
        }
        Node* z = new Node(key);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->color = RED;
        root->color = BLACK;
        insertFix(z);
    }
    void insert4(int key){// Big O(log(n)) where n is the number of nodes in the RB tree
        if (root == nil){
            root->data=key;
            root->color = BLACK;
            root->left = nil;
            root->right = nil;
        }
        Node* z = new Node(key);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if (z->data > x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        } else if (z->data > y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->color = RED;
        root->color = BLACK;
        insertFix(z);
    }
    int childCounter(Node* root, int counter){
        if (root==nil){
            return 0;
        }
        if (root->left!=nil){
            counter = childCounter(root->left,++counter);
        }
        if (root->right!=nil){
            counter = childCounter(root->right,++counter);
        }
        return counter;
    }
    void printChildNumbers(Node* root){
        if (root == nil) {
            return;
        }
        cout<< root->data<< "-"<<childCounter(root, 0)<<endl;

        printChildNumbers(root->left);
        printChildNumbers(root->right);
    }
    int blackHeightCounter(Node* root, int counter){
        if (root==nil){
            return 0;
        }
        if (root->left!=nil&&root->left->color==BLACK){
            counter = blackHeightCounter(root->left,++counter);
            return counter;
        }
        if (root->right!=nil&&root->right->color==BLACK){
            counter = blackHeightCounter(root->right,++counter);
            return counter;
        }
        return counter;
        //10 20 5 6 12 30 15 3 8 25 35 1 7 18
    }
    void blackHeights(Node* root){
        if (root == nil) {
            return;
        }
        cout<< root->data<< "-"<<blackHeightCounter(root, 0)+1<<endl;

        blackHeights(root->left);
        blackHeights(root->right);
    }
    int heightCounter(Node* root){
        if (root == nil) {
            return 0;
        }
        int leftHeight = heightCounter(root->left);
        int rightHeight = heightCounter(root->right);
        return 1 + max(leftHeight, rightHeight);
    }
    int search(int value){
        Node* current = this->root;

        while (current != nil) {
            if (value == current->data) {
                return heightCounter(current);
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // Value not found
        return 0;
    }
    void inOrderTraversal(Node* node, int* elements, int index){
        if (node != nil) {
            inOrderTraversal(node->left, elements, index);
            elements[index++] = node->data;
            inOrderTraversal(node->right, elements, index);
        }
    }
    void printTree() const{
        printTree(root);
    }
    Node* getRoot(){
        return this->root;
    }
};


