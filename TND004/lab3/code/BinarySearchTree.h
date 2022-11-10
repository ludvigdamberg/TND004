#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h

public:
    class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

    BinarySearchTree() : root{ nullptr } {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree& rhs) : root{ clone(rhs.root) } {
    }

    explicit BinarySearchTree(const std::vector<Comparable>& V) : root{ nullptr } {

        Node* parent = nullptr;

        root = minimum_tree(V.begin(), V.end(), parent);
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree& operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable& findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable& findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable& x) const {
        return (contains(x, root) != nullptr);
    }

    Iterator contains_it(const Comparable& x) const {
        Node* found = contains(x, root);
        if (found) return Iterator(nullptr, found);
        else return end();
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream& out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        }
        else {
            preorder(root, out);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable& x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable& x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }

    Comparable get_parent(const Comparable& x) { //O(h)

        Comparable parent_comp{ 0 };

        Node* tmp = root; //start from root
        while (tmp != nullptr) //As long as tmp is not a nullptr
        {
            if (tmp->element > x) { //If the element is bigger than x
                tmp = tmp->left; //Go to the next smaller value to the left to find something closer to x

            }
            else if (tmp->element < x) { //If the element is smaller than x
                tmp = tmp->right; //Go to a bigger value to the right to find something closer to x
            }

            else { //The value is equal to x

                return (tmp->parent != nullptr) ? tmp->parent->element : parent_comp; //Check if it's the root and has no parent return parent comp if root

            }
        }
        return parent_comp;
    }

    //begin stores the smallest value or the binary tree.

    Iterator begin() const {
        if (isEmpty()) return end();
        else return Iterator(nullptr, findMin(root));
    }

    Iterator end() const {
        return Iterator(nullptr, nullptr);
    }

    Iterator find(const Comparable& x) {
        if (contains(x, root)) return Iterator(nullptr, contains(x, root));

        else return end();
    }

private:
    Node* root;

    Node* minimum_tree(typename std::vector<Comparable>::const_iterator first, typename std::vector<Comparable>::const_iterator last, Node* pt) {


        if (std::distance(first, last) != 0) {

            int mid = std::distance(first, last) / 2;

            Node* rt = new Node{ *(first + mid), nullptr, nullptr, pt };

            rt->left = minimum_tree(first, (first + mid), rt);

            rt->right = minimum_tree((first + mid + 1), last, rt);

            return rt;

        }
        else {
            return nullptr;
        }


    }

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node* insert(const Comparable& x, Node* t) {

        if (t == nullptr) {
            t = new Node{ x, nullptr, nullptr, nullptr };

        }
        else if (x < t->element) {
            t->left = insert(x, t->left);
            t->left->parent = t;

        }
        else if (t->element < x) {
            t->right = insert(x, t->right);
            t->right->parent = t;

        }
        else {
            ;  // Duplicate; do nothing
        }
        return t;
    }

    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node* remove(const Comparable& x, Node* t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element) {
            t->left = remove(x, t->left);

        }
        else if (t->element < x) {
            t->right = remove(x, t->right);

        }
        else if (t->left != nullptr && t->right != nullptr) {  // Two children

            t->element = findMin(t->right)->element; //find the successor
            t->right = remove(t->element, t->right); //remove the element

        }
        else {

            Node* oldNode = t;

            if (t->left != nullptr || t->right != nullptr) // Check if it only has one child
            {
                (t->left != nullptr) ? t->left->parent = t->parent : t->right->parent = t->parent; //set the childs parent to the removed nodes parent
            }

            t = (t->left != nullptr) ? t->left : t->right;

            delete oldNode;
        }
        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    Node* findMin(Node* t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    Node* findMax(Node* t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node* contains(const Comparable& x, Node* t) const {
        if (t == nullptr) {
            return t;
        }
        else if (x < t->element) {
            return contains(x, t->left);
        }
        else if (t->element < x) {
            return contains(x, t->right);
        }
        else {
            return t;  // Match
        }
    } // in the course book, this function returns a bool

    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }
        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node* makeEmpty(Node* t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node* t, std::ostream& out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

    void preorder(Node* t, std::ostream& out, int indent = 2) const {

        if (t != nullptr) {


            out << std::setw(indent) << t->element << '\n';

            preorder(t->left, out, indent + 2);

            preorder(t->right, out, indent + 2);
        }
    }

    /**
     * Private member function to clone subtree.
     */
    Node* clone(Node* t) const {
        if (t == nullptr) {
            return nullptr;
        }
        else {

            Node* tmp = new Node(t->element, clone(t->left), clone(t->right));

            if (tmp->left != nullptr) {
                tmp->left->parent = tmp;
            }

            if (tmp->right != nullptr) {
                tmp->right->parent = tmp;
            }
            return tmp;
        }
    }

    //Finds the next upcoming (sorted) value in the binary tree 

    Node* find_successor(Node* t) const {

        if (t == nullptr) return nullptr; //if the tree is empty

        if (t->right != nullptr) return findMin(t->right); //if the tree has nodes to the right find the min value in the right subtree

        //Climb back up until parent has a left node, then return parent
        while (t->parent != nullptr && t != t->parent->left) {
            t = t->parent;
        }

        return t = t->parent;

    }

    // Finds the previous (sorted) value in the binary tree by looking for the closest value to the right  
    // of the selected Node.

    Node* find_predecessor(Node* t) const {

        if (t == nullptr) return nullptr; //if the tree is empty

        if (t->left != nullptr) return findMax(t->left); //if the tree has nodes to the left find the max value in the right subtree

        //Climb back up until parent has a right node, then return parent
        while (t->parent != nullptr && t != t->parent->right) {
            t = t->parent;
        }

        return t = t->parent;

    }

};




// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"