#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include "AVLTree.h"
#include "IndexHandler.h"
#include "QueryEngine.h"
#include "HashMap.h"
#include "document.h"
#include "UserInterface.h"

using namespace std;
using namespace rapidjson;

void testAVLTree(){
    AVLTree<int, int> tree;
    tree.insert(20, 34);
    tree.insert(12, 213);
    for(int i=0;i<15;i++){
        tree.insert(rand()%100, i+1);
    }
    tree.display();
    cout << "20: " << tree.get(20) << " " << tree.contains(20)<< endl;
    cout << "12: " << tree.get(12) << " " << tree.contains(-1) << endl;
}

int main(int argc, char *argv[]) {
    UserInterface ui;
    return 0;
}
