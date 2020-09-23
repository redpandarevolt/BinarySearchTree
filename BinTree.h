
// Created by marcela gomez on 2019-07-06.
// CSS 343 Summer 2019 Program 2 Binary Search Tree
// References: Olsen, Clark CSS 343 Notes 2, 3
//             Carrano, Chapters 15 -16
//

#ifndef BINARYSEARCHTREE_BINTREE_H
#define BINARYSEARCHTREE_BINTREE_H

#include "nodedata.h"
using namespace std;


class BinTree
{

    //Overloaded << operator, Displays contents of entire BST inorder
    friend ostream& operator<<(ostream &output, const BinTree &);


public:


    //default constructor, copy constructor and de-constructor
    BinTree();
    BinTree(const BinTree &);
    ~BinTree();

    bool isEmpty() const;
    void makeEmpty();
    bool insert(NodeData*);

    bool retrieve(const NodeData &, NodeData*&) const;
    int getHeight(const NodeData & target) const;

    void bstreeToArray(NodeData* []);
    void arrayToBSTree(NodeData* []);
    void displaySideways() const;

    //Overloaded operators: assignment and comparison
    BinTree& operator=(const BinTree&);
    bool operator==(const BinTree&) const;
    bool operator!=(const BinTree&) const;


private:

    struct Node
    {
        NodeData* data;
        Node* leftChild;
        Node* rightChild;
    };

    Node* root;

    //helper functions used to access private Node Data structure
    bool isEqual(Node *lhs , Node *rhs ) const;
    void inOrder(Node* treePtr) const;
    int maxDepth(const Node* node) const;
    bool findTargetHelper(Node* root, const NodeData &Target, Node *& targetResult) const;
    int nodeDepthHelper(Node* curr, const NodeData& target, int height) const;
    void copyTree(Node* rightTree, Node* &leftTree) const;
    void sideways(Node* , int) const;
    bool insertHelper(Node*& curr, NodeData* placeData);
    int getHeightHelper(Node *curr, const NodeData &target, int height) const;

    //int  getheightHelper(const NodeData & goal, Node *curr, int height) const;
    bool retrieveHelper(Node* curr, const NodeData& keyValue, NodeData *&received) const;
    int bstreeToArrayHelper(Node *curr, NodeData *array[]);
    void arrayToBSTreeHelper(Node* , NodeData* [], int ,int);
    void destroyTree(Node*& treePtr);

};


#endif //BINARYSEARCHTREE_BINTREE_H
