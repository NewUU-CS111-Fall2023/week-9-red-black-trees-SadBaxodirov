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
private:
    Node* root;
    Node* nil; // Sentinel node

    void leftRotate(Node* x){
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
    void rightRotate(Node* y){
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
    void insertFix(Node* z){
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
    void deleteNode(Node* z){
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
    void deleteFixup(Node* x){
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
    Node* minimum(Node* x) const{
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }
    void transplant(Node* u, Node* v){
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    void printTree(Node* root) const{
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
    void insert1(int key){
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
    void insert2(int key){
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
    void insert3(int key){
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

    void printTree() const{
        printTree(root);
    }
};


