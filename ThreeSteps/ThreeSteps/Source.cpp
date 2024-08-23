#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    Tree tree;

    tree.setRoot(2);

    tree.addNode(0, 2);
    tree.addNode(3, 2);
    tree.addNode(4, 2);
    tree.addNode(5, 3);
    tree.addNode(6, 3);
    tree.addNode(1, 4);
    tree.addNode(7, 4);
    tree.addNode(8, 4);
    tree.addNode(9, 8);
    tree.addNode(10, 9);
    tree.addNode(11, 9);

    tree.addConnect(0, 2);
    tree.addConnect(3, 2);
    tree.addConnect(4, 2);
    tree.addConnect(0, 3);
    tree.addConnect(2, 3);
    tree.addConnect(4, 3);
    tree.addConnect(5, 3);
    tree.addConnect(6, 3);
    tree.addConnect(1, 4);
    tree.addConnect(7, 4);
    tree.addConnect(8, 4);
    tree.addConnect(0, 5);
    tree.addConnect(2, 5);
    tree.addConnect(4, 5);
    tree.addConnect(7, 6);
    tree.addConnect(3, 7);
    tree.addConnect(3, 8);
    tree.addConnect(5, 8);
    tree.addConnect(8, 6);
    tree.addConnect(9, 8);
    tree.addConnect(10, 9);
    tree.addConnect(11, 9);


    tree.printThreeSteps(4);
    tree.printThreeSteps(2);
    tree.printThreeSteps(0);
    tree.printThreeSteps(9);
    tree.printThreeSteps(5);
}