//
// Created by katie on 4/9/2021.
//

#ifndef SEARCH_ENGINE_AVLTREE_H
#define SEARCH_ENGINE_AVLTREE_H

#include "AVLNode.h"
#include "document.h"
#include <vector>
#include <stdexcept>
#include <ostream>
#include <iostream>
#include <fstream>

using namespace std;
/*!
 * \class Balanced AVLTree to hold information and data associated with it
 * @tparam a paramter one
 * @tparam b parameter two
 */
template <class a, class b>
class AVLTree{
    private:
        AVLNode<a, b> *root; //!@private \var root or base node of the tree
        float size; ///@private \var number of nodes within the tree

        //change Tree
        AVLNode<a,b>* insert(a, b, AVLNode<a, b>*);
        void empty(AVLNode<a, b>*);
        void copyNode(AVLNode<a, b>*);

        //rotates
        AVLNode<a,b>* balance(AVLNode<a, b>*);
        AVLNode<a,b>* RightRotateSingle(AVLNode<a, b>*);
        AVLNode<a,b>* LeftRotateSingle(AVLNode<a, b>*);
        AVLNode<a,b>* LeftRotateDouble(AVLNode<a, b>*);
        AVLNode<a,b>* RightRotateDouble(AVLNode<a, b>*);

        //get information
        int getHeight(AVLNode<a, b>*);
        void printInOrder(AVLNode<a,b>*);
        void printPreOrder(AVLNode<a,b>*);
        void printPostOrder(AVLNode<a,b>*);
        int max(int x, int y);
        AVLNode<a, b>* get(AVLNode<a, b>*, a);
        bool contains(AVLNode<a, b>*, a);
        void storeData(AVLNode<string,vector<document>>*);
        vector<document> mostFreq(vector<document>, int, AVLNode<string, vector<document>>*);

    public:
        //constructors
        AVLTree();
        AVLTree(const AVLTree<a, b>&);
        ~AVLTree();
        AVLTree<a,b>& operator= (const AVLTree<a,b>&);

        //change information
        void insert(a, b);
        void clear();

        //display information
        void display();
        b& get(a);
        bool contains(a);
        float getSize();

        void createPersistentIndex(AVLTree<string, vector<document>>);
        void storeData();

        vector<document> mostFreq();
};

/*!
 * \fn default constructor
 * sets root to null and size to zero
 */
template <class a, class b>
AVLTree<a,b>::AVLTree(){
    root = nullptr;
    size = 0;
}
/*!
 * \fn copy constructor
 * call recursive function copyNode for each node in tree to insert into current tree
 * \param tree AVLtree to be copied
 */
template <class a, class b>
AVLTree<a,b>::AVLTree(const AVLTree<a, b>& tree){
    if(tree.root == nullptr) {
        root = nullptr;
        return;
    }
    copyNode(tree.root);
}
/*!
 * \fn destructor
 * call recursive function to delete all elements in the array
 */
template <class a, class b>
AVLTree<a,b>::~AVLTree(){
    empty(root);
}
/*!
 * \fn override equal operator
 * calls recursive function to copy all nodes
 * \param tree to copy information from
 * \return current tree
 */
template <class a, class b>
AVLTree<a,b>& AVLTree<a,b>::operator= (const AVLTree<a,b>& tree){
    if(tree.root == nullptr) {
        root = nullptr;
    } else {
        copyNode(tree.root);
    }
    return this;
}
/*!
 * \fn insert element and data into array
 * if root is empty assign to root, else call recursive insert function
 * \param key key to be sorted in balanced tree
 * \param data data to be associated with the key in the tree
 */
template <class a, class b>
void AVLTree<a,b>::insert(a key, b data){
    size++;
    if(root == nullptr){
        root = new AVLNode<a,b>(key, data);
    } else {
        root = insert(key, data, root);
    }
}
/*!
 * \fn remove all elements from tree
 * set size to 0 and call recursive function empty()
 */
template <class a, class b>
void AVLTree<a,b>::clear(){
    size = 0;
    empty(root);
}

/*!
 * @private \fn Recursively delete all nodes in a tree
 * call function for left and right node until reach end then delete current node
 * \param node current AVLNode in tree to delete
 */
template <class a, class b>
void AVLTree<a,b>::empty(AVLNode<a, b>* node){
    if(node == nullptr)
        return;
    empty(node->left);
    empty(node->right);
    delete node;
}

/*!
 * @private \fn copy node from AVLTree
 * insert copy of node into AVL tree and recursively copy elements from left to right
 * \param node AVLNode to copy
 */
template <class a, class b>
void AVLTree<a,b>::copyNode(AVLNode<a, b>* node){
    if(node == nullptr)
        return;
    insert(new AVLNode<a, b>(node->key, node->data));
    copy(node->left);
    copy(node->right);
}
/*!
 * @private \fn insert a node in correct location recursively
 * recursively traverse tree from current node until we reach end of the tree where create node and insert
 * \param key value to be stored in AVLTree
 * \param data data stored with value in AVLTree
 * \param current current node accessed on AVLTree
 */
template <class a, class b>
AVLNode<a,b>* AVLTree<a,b>::insert(a key, b data, AVLNode<a, b>* current){
    //if at the end of a tree, create and return
    if(current == nullptr)
        return new AVLNode<a, b>(key, data);
    //traverse left if smaller
    if(key < current->key){
        current->left = insert(key, data, current->left);
    } else {
        //traverse right if larger
        current->right = insert(key, data, current->right);
    }
    //ensure tree is balanced
    current = balance(current);
    //set heigh to largest + current one
    current->height = 1 + max(getHeight(current->left), getHeight(current->right));
    return current;
}
/*!
 * @private \fn rotate the AVLtree to balance tree from unbalanced node
 * check the height of each child to determine which rotation need to be made
 * \param alpha unbalanced node to balance
 * \return current balanced node
 */
template <class a, class b>
AVLNode<a,b>* AVLTree<a,b>::balance(AVLNode<a, b>* alpha){
    if(getHeight(alpha->left)-getHeight(alpha->right) > 1){
        if(getHeight(alpha->left->left) >= getHeight(alpha->left->right))
            return LeftRotateSingle(alpha);  //case 1 : LL
        else
            return LeftRotateDouble(alpha);  //case 2 : LR
    } else if(getHeight(alpha->right) - getHeight(alpha->left) > 1){
        if(getHeight(alpha->right->left) >= getHeight(alpha->right->right))
            return RightRotateDouble(alpha); //case 3 : RL
        else
            return RightRotateSingle(alpha); //case 4 : RR
    }
    return alpha;
}
//Case 4: RR
/*!
 * @private \fn rotate unbalanced node to the right once
 * rotate all nodes to the right one
 * \param k2 unbalanced node that needs to be balanced
 * \return current balanced node
 */
template <class a, class b>
AVLNode<a,b>* AVLTree<a,b>::RightRotateSingle(AVLNode<a, b>* k2){
    AVLNode<a, b> *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(getHeight(k2->right), getHeight(k2->left))+1;
    k1->height = max(getHeight(k1->right), getHeight(k2))+1;
    k2 = k1;
    return k1;
}
//Case 1: LL
/*!
 * @private \fn rotate unbalanced node to the left once
 * rotate all nodes to the left one
 * \param k2 unbalanced node that needs to be balanced
 * \return current balanced node
 */
template <class a, class b>
AVLNode<a,b>* AVLTree<a,b>::LeftRotateSingle(AVLNode<a, b>* k2){
    AVLNode<a, b> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(getHeight(k2->left), getHeight(k2->right))+1;
    k1->height = max(getHeight(k1->left), getHeight(k2))+1;
    k2 = k1;
    return k1;
}

//Case 3: RL
/*!
 * @private \fn rotate unbalanced node to the right twice
 * rotate all nodes under left child to the right then rotate all left
 * \param k2 unbalanced node that needs to be balanced
 * \return current balanced node
 */
template <class a, class b>
AVLNode<a,b>* AVLTree<a,b>::LeftRotateDouble(AVLNode<a, b>* k2){
    k2->left = RightRotateSingle(k2->left);
    return LeftRotateSingle(k2);
}

//Case 2: LR
/*!
 * @private \fn rotate unbalanced node to the left twice
 * rotate all nodes under right child to the left then rotate all right
 * \param k2 unbalanced node that needs to be balanced
 * \return current balanced node
 */
template <class a, class b>
AVLNode<a,b>* AVLTree<a,b>::RightRotateDouble(AVLNode<a, b>* k2){
    k2->right = LeftRotateSingle(k2->right);
    return RightRotateSingle(k2);
}

/*!
 * \fn return the total distance from node to root
 * return -1 if at the bottom of the tree
 * \param node node to determine height of
 * \return height of current node
 */
template <class a, class b>
int AVLTree<a,b>::getHeight(AVLNode<a, b>* node){
    if(node == nullptr)
        return -1;
    return node->height;
}

/*!
 * @private \fn print all nodes in order
 * print all nodes to left then current's key then right
 * \param node AVLnode to print
 */
template<class a, class b>
void AVLTree<a,b>::printInOrder(AVLNode<a,b>* node){
    if(node == nullptr)
        return;
    printInOrder(node->left);
    cout << node->key << endl;
    printInOrder(node->right);
}

/*!
 * @private \fn print all nodes in preorder
 * print current node's key before left nodes then right
 * param node AVLNode to print
 */
template<class a, class b>
void AVLTree<a,b>::printPreOrder(AVLNode<a,b>* node){
    if(node == nullptr)
        return;
    cout << node->key << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
}

/*!
 * @private \fn print all nodes in postorder
 * print left nodes then right nodes then current node's key
 * \param node AVLNode to print
 */
template<class a, class b>
void AVLTree<a,b>::printPostOrder(AVLNode<a,b>* node){
    if(node == nullptr)
        return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    cout << node->key << " ";
}

/*!
 * \fn display all nodes in the tree
 * call printInOrder() function
 */
template <class a, class b>
void AVLTree<a,b>::display() {
    printInOrder(root);
    cout << endl;
}

/*!
 * \fn retrieve an element from the tree
 * call recursive get() function to find node that holds element
 * \param element key to search for in the tree
 * \return return the data associated with the key
 */
template <class a, class b>
b& AVLTree<a,b>::get(a element){
    if(get(root, element) == nullptr)
        throw std::out_of_range("Element does not exist");
    return get(root, element)->data;
}

/*!
 * @private \fn recursively get a data from a given key
 * check if data exists then check left right and current
 * \param node current node to check
 * \param item key searching for
 * \return data associated with key
 */
template <class a, class b>
AVLNode<a, b>* AVLTree<a,b>::get(AVLNode<a, b>* node, a item){
    if(node == nullptr)
        return nullptr;
    else if(item == node->key)
        return node;
    else if(node->key < item)
        return get(node->right, item);
    else if(node->key > item)
        return get(node->left, item);
}

/*!
 * @private \fn check if node contains key
 * check if node's key is current element then check left or right depending on value
 * \param node current node to check
 * \param item key searching for
 * \return boolean of if element found
 */
template <class a, class b>
bool AVLTree<a,b>::contains(AVLNode<a, b>* node, a element){
    if(node == nullptr)
        return false;
    else if(node->key == element)
        return true;
    else if(node->key < element)
        return contains(node->right, element);
    else if(node->key > element)
        return contains(node->left, element);
}

/*!
 * \fn check if key is within tree
 * call recursive function contains() with root node
 * \param element key to search for
 * \return boolean of if element found
 */
template <class a, class b>
bool AVLTree<a,b>::contains(a element){
    return contains(root, element);
}

/*!
 * \fn return the maximum value of two integers
 * \param x first integer
 * \param y second integer
 * \return maximum integer
 */
template <class a, class b>
int AVLTree<a,b>::max(int x, int y) {
    if(x > y)
        return x;
    return y;
}

/*!
 * \fn return number of elements in tree
 * \return size of tree
 */
template <class a, class b>
float AVLTree<a,b>::getSize() {
    return size;
}

/*!
 * @private \fn create a persistent index of keys and data
 * create a file then call recursive function storeData() with root
 */
template <class a, class b>
void AVLTree<a,b>::storeData(){
    std::ofstream myfile;
    myfile.open("persistentIndex.txt");
    storeData(root);
    myfile.close();
}

/*!
 * @private \fn create a persistent index with data from node
 * open persistent index in append then add the key and the value of node
 * \param node current node to store data
 */
template <class a, class b>
void AVLTree<a,b>::storeData(AVLNode<string, vector<document>> *node){
    ofstream out("persistentIndex.txt", std::ios_base::app);
    if(node == nullptr){
        out.close();
        return;
    }
    storeData(node->left);
    out << node->key;
    for(int i=0;i<node->data.size();i++){
        out << " " << node->data.at(i).getID();
        out << " " << node->data.at(i).getOccurances();
        out << " " << node->data.at(i).getTotalWords();
    }
    out << "\n";
    storeData(node->right);
    out.close();

}

/*!
 * \fn create a persistent index
 * call function storeData()
 */
template <class a, class b>
void AVLTree<a,b>::createPersistentIndex(AVLTree<string, vector<document>> tree){
    tree.storeData();
}
#endif //SEARCH_ENGINE_AVLTREE_H
