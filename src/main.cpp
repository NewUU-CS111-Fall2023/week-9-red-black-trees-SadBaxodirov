/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <cmath>
#include "task_1.h"

int main() {
    cout << "Task 1" << endl;
    RedBlackTree* RBtree1 = new RedBlackTree();
    // call for task 1
    int N;
    cout << "Enter the number of nodes (N): ";
    cin >> N;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N; i++) {
        int value;
        cin >> value;
        RBtree1->insert1(value);
    }

    cout << "Red-Black Tree:" << endl;
    RBtree1->printTree();
    cout<<endl;
    cout << "Task 2" << endl;
    // call for task 2
    RedBlackTree* RBtree2 = new RedBlackTree();
    int N2;
    cout << "Enter the number of nodes (N): ";
    cin >> N2;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N2; i++) {
        int value;
        cin >> value;
        RBtree2->insert2(value);
    }

    cout << "Red-Black Tree:" << endl;
    RBtree2->printTree();
    cout<<endl;
    cout << "Task 3" << endl;
    // call for task 3
    RedBlackTree* RBtree3 = new RedBlackTree();
    int N3;
    cout << "Enter the number of nodes (N): ";
    cin >> N3;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N3; i++) {
        int value;
        cin >> value;
        RBtree3->insert2(value);
    }

    cout << "Red-Black Tree:" << endl;
    RBtree3->printTree();
    cout<<endl;
    cout << "Task 4" << endl;
    // call for task 4
    RedBlackTree* RBtree4 = new RedBlackTree();
    int N4;
    cout << "Enter the number of nodes (N): ";
    cin >> N4;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N4; i++) {
        int value;
        cin >> value;
        RBtree4->insert4(value);
    }

    cout << "Red-Black Tree:" << endl;
    RBtree4->printTree();
    cout<<endl;
    cout << "Task 5" << endl;
    // call for task 5
    RedBlackTree* RBtree5 = new RedBlackTree();
    int N5;
    cout << "Enter the number of nodes (N): ";
    cin >> N5;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N5; i++) {
        int value;
        cin >> value;
        RBtree5->insert2(value);
    }//11 18 10 15 23 9 17 8 16 20
    Node* root5 = RBtree5->getRoot();
    RBtree5->printChildNumbers(root5);
    cout << "Task 6" << endl;
    // call for task 6
    RedBlackTree* RBtree6 = new RedBlackTree();
    int N6;
    cout << "Enter the number of nodes (N): ";
    cin >> N6;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N6; i++) {
        int value;
        cin >> value;
        RBtree6->insert2(value);
    }//11 18 10 15 23 9 17 8 16 20
    Node* root6 = RBtree6->getRoot();
    RBtree6->blackHeights(root6);
    cout << "Task 7" << endl;
    // call for task 7
    RedBlackTree* RBtree7 = new RedBlackTree();
    int N7;
    cout << "Enter the number of nodes (N): ";
    cin >> N7;

    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N7; i++) {
        int value;
        cin >> value;
        RBtree7->insert2(value);
    }//11 18 10 15 23 9 17 8 16 20
    int value;
    cin>>value;
    Node* root7 = RBtree7->getRoot();
    if (RBtree7->search(value)==0)
        cout<<value<<" is not found"<<endl;
    else
        cout<<value<<" is found, its height is "<<RBtree7->search(value)<<endl;
    cout << "Task 8" << endl;
    // call for task 8
    RedBlackTree* RBtree8 = new RedBlackTree();
    int N8;
    cout << "Enter the number of nodes (N): ";
    cin >> N8;
    int elements[N8];
    cout << "Enter the values of nodes:" << endl;
    for (int i = 0; i < N8; i++) {
        int value;
        cin >> value;
        RBtree8->insert2(value);
    }//11 18 10 15 23 9 17 8 16 20
    Node* root8 = RBtree8->getRoot();
    //RBtree8->inOrderTraversal(root, elements,0);
    /*if (N8%2==1){
        cout<<elements[(N8+1)/2]<<" is median"<<endl;
    } else{
        cout<<std::floor((elements[N8/2]+elements[(N8/2)+1])/2)<<endl;
    }*/
    int size = 0;
    RBtree8->inOrderTraversal(root8,elements,size);
    for (int i=0;i<N8;i++)
        cout<<elements[i]<<endl;
    return 0;
}
