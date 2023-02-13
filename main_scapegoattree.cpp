#include <iostream>

#include "ScapegoatTree.h"

int main() {


    ScapegoatTree<int> tree;
    int a=15;
    tree.insert(10);
    tree.insert(5);
    tree.insert(7);
    tree.insert(6);
    tree.insert(15);
    tree.insert(13);
    tree.insert(14);
    tree.remove(15);
    tree.removeAllNodes();
    tree.printPretty();

    return 0;
}
