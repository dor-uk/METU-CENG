#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"


enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    
    Node<T> *copy_node(Node<T>* node);  //helper function 
    void delete_node(Node<T>* node);  //helper function 
    int get_size_parameter(Node<T>* node) const; //helper function 
    int get_height_parameter(Node<T>* node) const; //helper function 
    const T &get_parameter(Node<T>* node, const T &element) const; //helper function 
    const T &min_with_parameter(Node<T>* node) const; //helper function 
    const T &max_with_parameter(Node<T>* node) const; //helper function 
    Node<T> *ceiling_parameter(Node<T>* node, const T element) const; //helper function 
    Node<T> *floor_parameter(Node<T>* node, const T element) const; //helper function 
    Node<T> *getNext_parameter(Node<T>* node, const T element) const; //helper function 
    
    void insert_with_parameter(Node<T>* &node, const T &element); //helper function 
    Node<T> *get_max(Node<T>* node); //helper function
    void remove_with_parameter(Node<T>* &node, const T &element); //helper function 
    Node<T> *find_parent(Node<T>* node, const T &element);  //helper function
    Node<T> *find(Node<T>* node, const T &element); //helper function
    Node<T> *search(const T &element); //helper function
    int put_in_array(Node<T>* node, Node<T>* arr[], int i); //helper function
    
    //const T &put_in_array2(Node<T>* arr[], int i) const; //helper function
    
    void rebuild(Node<T>* node); //helper function 
    Node<T> *buildfrom_arr(Node<T>** arr, int i, int n);  //helper function
    //void helper_balance(Node<T>* &node, const T &element); //helper function
    //Node<T> * getRoot();
    
    
private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H



/*---------------------------------------helper functions-------------------------------------*/


template<class T>
Node<T>* ScapegoatTree<T>::copy_node(Node<T>* node) {  //helper function
    
    if(node != NULL)
    {
        return new Node<T>(node->element, this->copy_node(node->left), this->copy_node(node->right));
    }
    
    return NULL;
}

template<class T>
void ScapegoatTree<T>::delete_node(Node<T>* node) {  //helper function
    
    if(node != NULL)
    {
        delete_node(node->left);
        delete_node(node->right);
        delete node;
    }
    
    
}

template<class T>
int ScapegoatTree<T>::get_size_parameter(Node<T>* node) const {  //helper function
    
    if(node == NULL)
    {
        return 0;
    }
    
    else
    {
        return (1 + get_size_parameter(node->left) + get_size_parameter(node->right));
    }
}

template<class T>
int ScapegoatTree<T>::get_height_parameter(Node<T>* node) const {  //helper function

    if(node == NULL)
    {
        return 0;
    }
    
    else
    {
        int left_h = get_height_parameter(node->left);
        int right_h = get_height_parameter(node->right);
        
        if(left_h > right_h)
        {
            return (left_h + 1);
        }
        else
        {
            return (right_h + 1);
        }
    }
    
    
}

template<class T>
const T &ScapegoatTree<T>::get_parameter(Node<T>* node, const T &element) const {  //helper function
    
    if(node == NULL) 
    {
        throw NoSuchItemException();
    }
    
    if(node->element == element)
    {
        return node->element;
    }
    
    
    
    if(node->element > element)
    {
        get_parameter(node->left, element);
    }

    else if(node->element < element)
    {
        get_parameter(node->right, element);
    }
    
    //throw NoSuchItemException();
    
    
}

template<class T>
const T &ScapegoatTree<T>::min_with_parameter(Node<T>* node) const {
    
    if(node == NULL)
    {
        throw NoSuchItemException();
    }
    else
    {
        Node<T>* current = node;
        while(current->left != NULL)
        {
            current = current->left;
        }
    
        return current->element;
    }
}

template<class T>
const T &ScapegoatTree<T>::max_with_parameter(Node<T>* node) const { //helper function
    
    if(node == NULL)
    {
        throw NoSuchItemException();
    }
    else
    {
        Node<T>* current = node;
        while(current->right != NULL)
        {
            current = current->right;
        }
    
        return current->element;
    }
    
}

template<class T>
Node<T>* ScapegoatTree<T>::ceiling_parameter(Node<T>* node, const T element) const { //helper function
    
    if(node == NULL)
    {
        return NULL;
        //throw NoSuchItemException();
    }
    
    if(element == node->element)
    {
        return node;
    }
    
    if(node->element > element)
    {
        if(node->left == NULL)
        {
            return node;
        }
        
        if(node->left)
        {
            if(node->left->element >= element)
            {
                return ceiling_parameter(node->left, element);
            }
            
            Node<T>* suspect = ceiling_parameter(node->left, element);
            if(!suspect)
            {
                return node;
            }
            else
            {
                return suspect->element < node->element ? suspect : node;
            }
            
        }
        
        
    }
    
    else
    {
        return  ceiling_parameter(node->right, element);
    }
    
    
    
    
    
}

template<class T>
Node<T>* ScapegoatTree<T>::floor_parameter(Node<T>* node, const T element) const { //helper function
    
    if(node == NULL)
    {
        return NULL;
        //throw NoSuchItemException();
    }
    
    if(element == node->element)
    {
        return node;
    }
    
    if(node->element < element)
    {
        if(node->right == NULL)
        {
            return node;
        }
        
        if(node->right)
        {
            if(node->right->element <= element)
            {
                return floor_parameter(node->right, element);
            }
            
            Node<T>* suspect = floor_parameter(node->right, element);
            if(!suspect)
            {
                return node;
            }
            else
            {
                return suspect->element > node->element ? suspect : node;
            }
            
        }
        
        
    }
    
    else
    {
        return  floor_parameter(node->left, element);
    }
    
    
}

template<class T>
Node<T>* ScapegoatTree<T>::getNext_parameter(Node<T>* node, const T element) const {  //helper function
    

    
    if(node == NULL)
    {
        return NULL;
        //throw NoSuchItemException();
    }
    
    /*if(element == node->element)
    {
        return node;
    }*/
    
    if(node->element > element)
    {
        if(node->left == NULL)
        {
            return node;
        }
        
        if(node->left)
        {
            if(node->left->element > element)
            {
                return getNext_parameter(node->left, element);
            }
            
            Node<T>* suspect = getNext_parameter(node->left, element);
            if(!suspect)
            {
                return node;
            }
            else
            {
                return suspect->element < node->element ? suspect : node;
            }
            
        }
        
        
    }
    
    else
    {
        return  getNext_parameter(node->right, element);
    }
    
    
    
}

template<class T>
void ScapegoatTree<T>::insert_with_parameter(Node<T>* &node, const T &element) { //helper function

    if(node == NULL)
    {
        node = new Node<T>(element, NULL, NULL);
    }
    
    if(element > node->element)
    {
        insert_with_parameter(node->right, element);
    }
    
    else if(element < node->element)
    {
        insert_with_parameter(node->left, element);
    }
    
    
}

template<class T>
Node<T>* ScapegoatTree<T>::get_max(Node<T>* node) { //helper function

    
    if(node->right == NULL)
    {
        return node;
    }
    
    return get_max(node->right);
    
}

template<class T>
void ScapegoatTree<T>::remove_with_parameter(Node<T>* &node, const T &element) { //helper function

    
    
    if(node == NULL)
    {
        return; 
    }
    
    if(element < node->element)
    {
        remove_with_parameter(node->left, element);
    }
    
    else if(element > node->element) 
    {
        remove_with_parameter(node->right, element);
    }
    
    else 
    {
        
        if(node->left == NULL && node->right == NULL) 
        {
            Node<T> *prev = node; 
            delete prev; 
            node = NULL;
            return;
        }
        
        else if(node->left == NULL && node->right != NULL)
        {
            Node<T> *prev = node;
            node = node->right; 
            delete prev; 
            return;
        }
        
        else if(node->right == NULL && node->left != NULL)
        {
            Node<T> *prev = node; 
            node = node->left; 
            delete prev; 
            return;
        }
        
        
        else// if(node->right != NULL && node->left != NULL)
        {
            node->element = get_max(node->left)->element;
            remove_with_parameter(node->left, node->element);
        }
        
    }
    
}

template<class T>
Node<T>* ScapegoatTree<T>::find_parent(Node<T>* node, const T &element) { //helper function

    if(node == NULL || node->element == element) //hata olabilir
    {
        return NULL;
    }
    
    if(node->left)
    {
        if(node->left->element == element)
        {
            return node;
        }
    }
    
    if(node->right)
    {
        if(node->right->element == element)
        {
            return node;
        }
    }
    
    if(node->element > element)
    {
        return find_parent(node->left, element);
    }
    
    else if(node->element < element)
    {
        return find_parent(node->right, element);
    }
    
    
    
    
}

template<class T>
Node<T>* ScapegoatTree<T>::find(Node<T>* node, const T &element) { //helper function

    if(node == NULL)
    {
        return NULL;
    }
        
    if(node->element == element)
    {
        return node;
    }
        
    Node<T>* found = find(node->left, element);
    
    if(found != NULL)
    {
        return found;
    }
    
    return find(node->right, element);
    
    
}

template<class T>
Node<T>* ScapegoatTree<T>::search(const T &element) { //helper function

    Node<T>* found = find(root,element);
}



template<class T>
int ScapegoatTree<T>::put_in_array(Node<T>* node, Node<T>* arr[], int i) {
    //hata olabilir sorted mi
    
    if(node == NULL)
    {
        return i;
    }
    
    i = put_in_array(node->left, arr, i);
    arr[i] = node;
    i++;
    return put_in_array(node->right, arr, i);
}

template<class T>
void ScapegoatTree<T>::rebuild(Node<T>* node) {
    
    int size = get_size_parameter(node);
    Node<T>* parent = find_parent(root, node->element);
    Node<T>** arr = new Node<T>* [size];
    
    put_in_array(node, arr, 0);
    
    if(parent == NULL)
    {
        
        root = buildfrom_arr(arr, 0, size);
    }
    
    else if(parent->right == node)
    {
        parent->right = buildfrom_arr(arr, 0 , size);
        Node<T>* right_parent = find_parent(root, parent->right->element);
        right_parent = parent;
    }
    
    else //if(parent->left == node)
    {
        parent->left = buildfrom_arr(arr, 0 , size);
        Node<T>* left_parent = find_parent(root, parent->left->element);
        left_parent = parent;
    }
    
    delete [] arr;
}

template<class T>
Node<T>* ScapegoatTree<T>::buildfrom_arr(Node<T>** arr, int i, int n) {
    
    if(n == 0)
    {
        return NULL;
    }
    
    int m = n/2;
    
    if(n%2 == 0)
    {
        m--;
    }
    
    arr[i+m]->left = buildfrom_arr(arr, i , m);
    
    if(arr[i+m]->left != NULL)
    {
        Node<T>* parent = find_parent(arr[i+m]->left, arr[i+m]->left->element);
        parent = arr[i+m];
    }
    
    arr[i+m]->right = buildfrom_arr(arr, i+m+1 , n-m-1);
    
    if(arr[i+m]->right != NULL)
    {
        Node<T>* parent = find_parent(arr[i+m]->right, arr[i+m]->right->element);
        parent = arr[i+m];
    }
    
    return arr[i+m];
}


/*---------------------------------------------------------------------------------------------*/

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    /* TODO */
    
    root = copy_node(obj.root);
    upperBound = obj.upperBound;
    
    
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    
    delete_node(root);
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    
    return (root == NULL);
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    return (get_height_parameter(root) - 1);
    
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    
    return (get_size_parameter(root));
    
}

static float const log32(int n)
{
    double const log23 = 2.4663034623764317;
    return (float)(log23 * log(n));
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    /* TODO */
    
    if(find(root,element))
    {
        return false;
    }
    
    insert_with_parameter(root, element);
    upperBound++;
    
     
    int depth = getHeight();
    //std::cout<< depth<< " " <<log32(upperBound)<< ' ';
    //std::cout<< get_height_parameter(find(root,element)) <<' '<< check;
    if(depth > log32(upperBound))
    {
        Node<T>* parent = find_parent(root, element);
        
        
        //Node<T>* grand = find_parent(root, parent->element);
        
        while((3*get_size_parameter(parent)) <= (2*get_size_parameter(find_parent(root, parent->element))))
        {
            parent = find_parent(root, parent->element);
        }
        //std::cout<< parent->element<<' '<<find_parent(root, parent->element)->element;
        rebuild(find_parent(root, parent->element));
        
        
    }
    return true;
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    /* TODO */
    
    if(!(find(root,element)))
    {
        return false;
    }
    if(root == NULL)
    {
        return false;
    }
    
    remove_with_parameter(root, element);
    
    int number_nodes = getSize();
    float check = (float)upperBound / (float)2;
    
    if(number_nodes < check)
    {
        balance();
        upperBound = number_nodes;
    }
    
    return true;
    
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    /* TODO */
    
    delete_node(root);
    root = NULL;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    /* TODO */
    return get_parameter(root, element);
    
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (isEmpty()) 
        {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        
        
    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) 
        {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        
        
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        
        if(node ==NULL)
        {
            return;
        }
        
        std::cout << "\t" << node->element;
        
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        
        
        
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
          return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) {
        /* TODO */
        
        if(node ==NULL)
        {
            return;
        }
        
        
        print(node->left, postorder);
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        
        std::cout << "\t" << node->element;
        
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    /* TODO */
    
    if(this != &rhs)
    {
        delete_node(root);
    
        root = copy_node(rhs.root);
        upperBound = rhs.upperBound;
    }
}

template<class T>
void ScapegoatTree<T>::balance() {
    /* TODO */
    
    rebuild(root);
    
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    /* TODO */
    T ans = element;
    Node<T>* result = ceiling_parameter(root, ans);
    
    if(result == NULL)
    {
        throw NoSuchItemException();
    }
    
    return result->element;
    
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    /* TODO */
    
    T ans = element;
    Node<T>* result = floor_parameter(root, ans);
    
    if(result == NULL)
    {
        throw NoSuchItemException();
    }
    
    return result->element;
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    /* TODO */
    
    return min_with_parameter(root);
    
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    /* TODO */
    
    return max_with_parameter(root);
    
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    /* TODO */
    
    T ans = element;
    Node<T>* result = getNext_parameter(root, ans);
    
    if(result == NULL)
    {
        throw NoSuchItemException();
    }
    
    return result->element;
}

