#ifndef SEARCH_ENGINE_AVLNODE_H
#define SEARCH_ENGINE_AVLNODE_H

//! \class AVLNode Class
/*!
 * \brief Holds the templated arguments stored within an AVL Tree
 * Two templated paramaters are held to represent the key stored in the AVL Tree and the value it represents.
 * It can be modififed, printed, and retrieved by the AVLTree
 */

template <class a, class b>
class AVLNode{
public:
    //data stored
    a key; ///\var Value sorted in AVL Tree
    b data; ///\var Value key is associated with
    //nodes in tree
    AVLNode *left, *right; ///\var Values holding left and right node variables
    //height of tree
    int height; ///\var Value holding height from node to the root of tree
    //constructors
    AVLNode(const a&, const b&);
    AVLNode(const a&, const b&, AVLNode*, AVLNode*, int);
    AVLNode(const AVLNode& node);
    AVLNode<a,b>& operator= (const AVLNode<a,b>&);
    ~AVLNode();

    friend std::ostream& operator<< (std::ostream&, const AVLNode<a,b>&);
};
/*! \fn constructor for AVLNode with only values
 *
 * \param &k the key value
 * \param &d the data associated with the key
 */
template <class a, class b>
AVLNode<a, b>::AVLNode(const a &k, const b &d) {
    key = k;
    data = d;
    left = nullptr;
    right = nullptr;
    height = 0;
}
/*!
 * \fn constructor for AVLNode with all values
 *
 * \param e the key value
 * \param e2 the data associated with the key
 * \param lt AVLNode to the left of the current node
 * \param rt AVLNode to the right of the current node
 * \param h height from node to the root of tree
 */
template <class a, class b>
AVLNode<a,b>::AVLNode(const a &e, const b &e2, AVLNode *lt, AVLNode *rt, int h) {
    key = e;
    data = e2;
    left = lt;
    right = rt;
    height = h;
}

/*!
 *  @fn copy constructor
 *
 *  @param node constant node to copy all data from
 */
template <class a, class b>
AVLNode<a, b>::AVLNode(const AVLNode<a, b> &node) {
    key = node.key;
    data = node.data;
    left = node.left;
    right = node.right;
    height = node.height;
}
/*!
 * \fn override equals operator
 *
 * \param AVLNode to copy data from into current node
 * \return current node
 */
template <class a, class b>
AVLNode<a,b>& AVLNode<a,b>::operator= (const AVLNode<a,b>& node){
    key = node.key;
    data = node.data;
    left = node.left;
    right = node.right;
    height = node.height;
}

/*!
 * \fn Destructor for AVLNode
 */
template <class a, class b>
AVLNode<a, b>::~AVLNode() {
    height = -1;
}

/*!
 * @fn Override the outstream operator
 *
 * output the key of each node into stream
 * \param out ostream output
 * \param node node to be output
 *  \return ostream with output
 */
template <class a, class b>
std::ostream& operator<< (std::ostream& out, const AVLNode<a,b>& node){
    out << node->key << "\n";
    return out;
}
#endif //SEARCH_ENGINE_AVLNODE_H
