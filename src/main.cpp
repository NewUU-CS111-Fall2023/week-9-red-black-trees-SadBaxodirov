/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include "task_1.h"

int main() {
    cout << "Task 1" << endl;/*
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
    cout<<endl;*/
    cout << "Task 2" << endl;
    // call for task 2
    RedBlackTree* RBtree2 = new RedBlackTree();
    // call for task 1
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

    cout << "Task 4" << endl;
    // call for task 4
    cout << "Task 5" << endl;
    // call for task 5
    return 0;
}
