//
// Created by marcela gomez on 2019-07-06.
// CSS 343 Summer 2019 Program 2 Binary Search Tree
// References: Olsen, Clark CSS 343 Notes 2, 3
//             Carrano, Chapters 15 -16
//

#include "BinTree.h"

using namespace std;


//==========================operator<< overload========================
//Description: takes in components that will be placed in tree
//Pre-condition: stream and bst are passed in as parameters
//Post-condition: tree is displayed in order
//=====================================================================
ostream& operator<<(std::ostream &output, const BinTree & bst)
{
    bst.inOrder(bst.root);
    output << endl;
    return output;
}


//==========================Default Constructor========================
//Description: Constructor, creates an empty Binary Search Tree
//Pre-condition: tree does not exist,  Post-condition: empty tree is made
//=====================================================================
BinTree::BinTree()
{
    this->root = nullptr;
}


//==========================Copy Constructor===========================
//Description: Copy contructor uses helper function to construct new tree
//Pre-condition: two roots not equal to null
//Post-condition: copy is made of tree
//=====================================================================
BinTree::BinTree(const BinTree& treePtr)
{
    this->root = nullptr;
    copyTree(treePtr.root, this->root);
}


//=========================Destructor==================================
//Description: destructor, calls makeEmpty
//Pre-condition:  tree nodes need to be cleared
//Post-condition:  all nodes are deleted
//=====================================================================
BinTree::~BinTree()
{
    this->makeEmpty();
}


//==========================isEmpty===================================
//Description: checks to see if a tree is empty
//Pre-condition: none
//Post-condition: makes assessment of tree returns bool
//====================================================================
bool BinTree::isEmpty() const
{
    if(this->root == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//=========================Insert=====================================
//Description: inserts node into Binary Search Tree
//Pre-condition: Node is successfully created
//Post-condition: Binary Search Tree is constructed without duplicates
//=====================================================================
bool BinTree::insert(NodeData* placeData)
{
    return insertHelper(this->root, placeData);
}


//=========================InsertHelper==============================
//Description: inserts node into Binary Search Tree
//Pre-condition: root and data are passed to the helper function
//Post-condition: BST constructed without duplicates returns bool
//=====================================================================
bool BinTree::insertHelper(Node*& curr, NodeData* placeData)
{
    //if the tree is empty, create a new node to hold data
    if(curr == nullptr)
    {
        curr = new Node;
        curr->data = placeData;
        curr->leftChild = nullptr;
        curr->rightChild = nullptr;
    }

    else if(*placeData < *curr->data)    //*dereference pointer to compare data
    {
        insertHelper(curr->leftChild, placeData); //smaller data goes left
    }
    else if (*placeData > *curr->data)   //compare data
    {
        insertHelper(curr->rightChild, placeData);    //larger goes right
    } else {
        return false;  //if they are equal, duplicate does not insert
    }
    return true;
}


//=========================Retrieve Method=============================
//Description: returns true when matching data is found in search
//Pre-condition: target pointer nodes as they are searches passed in
//Post-condition: Looks to see if found target pointer is not empty
//=====================================================================

bool BinTree::retrieve(const NodeData & target, NodeData*& foundTarget) const
{
    retrieveHelper(root, target, foundTarget);
    if(foundTarget != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//=========================RetrieveHelper==============================
//Description: returns true when matching data is found in search
//Pre-condition: target value is not null
//Post-condition: tree is traversed determine if target is located
//=====================================================================
bool BinTree::retrieveHelper(Node* curr, const NodeData& target, NodeData *& targetFound) const
{

    if (curr == nullptr)         //case 1: tree empty, target not found
    {
        targetFound = nullptr;
        return false;
    }
    else if (*curr->data == target)  //cast2: data equals target
    {
        targetFound = curr->data;
        return true;
    }
    else if (*curr->data > target)       //case3: target is smaller, go left
    {
        retrieveHelper(curr->leftChild, target, targetFound);
    }
    else if (*curr->data < target)       //cast4: target is bigger, go right
    {
        retrieveHelper(curr->rightChild, target, targetFound);
    }
    else
    {
        return false;
    }
}


//=======================Get Height With Helper=======================
//Description:  find the height of a given value in the tree, bst unknown
//Pre-condition
//Post-condition: height is found
//=====================================================================
int BinTree::getHeight(const NodeData& target) const
{
    Node* targetResult;

    bool targetLocation = findTargetHelper(this->root, target, targetResult);

    if(targetLocation)
    {
        nodeDepthHelper(targetResult, target, 0);
    }

}

bool BinTree::findTargetHelper(Node* curr, const NodeData& target, Node *& targetResult) const {

    if (curr == nullptr) {
        targetResult = nullptr;
        return false;
    }
    if (*curr->data == target) {
        targetResult = curr;
        return true;
    }

    bool leftResult = findTargetHelper(curr->leftChild, target, targetResult);

    if (leftResult)
    {
        return true;
    }

    bool rightResult = findTargetHelper(curr->rightChild, target, targetResult);
    if (rightResult)
    {
        return true;
    }

    return false;
}



int BinTree::nodeDepthHelper(Node* subtreePtr, const NodeData& target, int height) const
{

    if(subtreePtr == NULL)
    {
        return height;
    }
    /*if (*subtreePtr->data == target)
    {
        return height;
    }*/
    height = max(nodeDepthHelper(subtreePtr->leftChild, target, height +1),
                 nodeDepthHelper(subtreePtr->rightChild, target, height+ 1));

    return height;
}


/*int BinTree::getHeightHelper(Node *curr, const NodeData& target, int height)const
{

    int treeDepth = maxDepth(root);
    int node = nodeDepth(root, target, height);
    int targetHeight = treeDepth - node;

    return targetHeight;
}*/

//==========================bstreeToArray and Helper==================
//Description: takes tree and puts elements in an array
//Pre-condition: tree exists
//Post-condition: array constructed and tree is empty
//====================================================================
void BinTree::bstreeToArray(NodeData* arrayFromTree[])
{
    bstreeToArrayHelper(this->root, arrayFromTree);
    this-> makeEmpty();     //empties tree after array is filled
}


int BinTree::bstreeToArrayHelper(Node *curr, NodeData *array[])
{
    if(curr == nullptr )
    {
        return 0;
    }
    //in order visit to nodes, adding to array as it goes

    int Left = bstreeToArrayHelper(curr->leftChild, array);

    NodeData *tempArray;
    tempArray = curr->data;
    curr->data = nullptr;
    *(array + Left) = tempArray;
    tempArray = nullptr;

    int Right = bstreeToArrayHelper(curr->rightChild, array + Left + 1);

    return Left + Right + 1;

}


//====================arrayToBSTree and Helper Function==============
//Description: builds balanced tree from a sorted array of
//NodeData* leaving the array filled with Nulls.
//Pre-condition: array is sorted
//Post-condition: binary search tree is constructed
//====================================================================
void BinTree::arrayToBSTree(NodeData* array[])
{
    int n = 0;  //look up sizeOf and size() not working with NodeData??
    for(int i = 0 ; i < 100; i++)
    {
        if(array[i] != NULL)
        {
            n++;
        } else
        {
            array[i] = NULL;
        }

    }

    arrayToBSTreeHelper(root, array, 0, n-1);
}

void BinTree::arrayToBSTreeHelper(Node * ptr, NodeData* array[], int start ,int end)
{
    if(start > end)
    {
        ptr = NULL;
    }
    else
    {
        int mid = (start + end)/2;
        NodeData * treeRoot;
        treeRoot = array[mid];
        array[mid] = nullptr;

        insert(treeRoot);
        arrayToBSTreeHelper(ptr, array, start, mid - 1);
        arrayToBSTreeHelper(ptr, array, mid + 1, end);
    }

}

//Overloaded operators: assignment and comparison

//============================(operator=)===========================
//Description:
//Pre-condition
//Post-condition
//====================================================================
BinTree& BinTree::operator=(const BinTree& rhs)
{
    if(*this != rhs)
    {
        destroyTree(root);
        copyTree(rhs.root, this->root);
    }
    return *this;
}


//============================isEqual=================================
//Description:
//Pre-condition
//Post-condition
//====================================================================
bool BinTree::isEqual(Node* leftNode, Node* rightNode) const
{
    if((leftNode != nullptr && rightNode != nullptr) && (*leftNode->data == *rightNode->data))
    {
        return true;
    }
    if((leftNode == nullptr) || (rightNode == nullptr))
    {
        return false;
    }
    return ((*leftNode->data == *rightNode->data) && isEqual(leftNode->leftChild, rightNode->leftChild) &&
            isEqual(leftNode->rightChild, rightNode->rightChild));
}

//============================(operator==)============================
//Description: compares two nodes to determine if they are empty
//====================================================================
bool BinTree::operator==(const BinTree& rhs) const
{
    if (this->root == nullptr && rhs.root ==nullptr)
        return true;
    else
        return isEqual(this->root, rhs.root);
}


//==============================(operator!=)=============================
//Description: true when two trees are not the same
//Pre-condition
//Post-condition: returns true if unequal
//====================================================================
bool BinTree::operator!=(const BinTree& rhs) const
{
    return !(*this == rhs);
}



//Protected Helper functions==========================================

//==============================makeEmpty=============================
//recursive post order traversal to delete each node in the tree.
// Pre-condition: tree with nodes is passed in
//Post-condition: tree is destroyed and pointer deleted
//====================================================================
void BinTree::makeEmpty() //Make a copy of BST
{
    destroyTree(root);
}

void BinTree::destroyTree(Node*& treePtr)
{
    if(treePtr != nullptr)
    {
        destroyTree(treePtr->leftChild);
        destroyTree(treePtr->rightChild);

        delete treePtr->data;
        treePtr = nullptr;
        delete treePtr;
        treePtr = nullptr;
    }
}

//=============================inOrder=================================
//Description: displays node data inorder
//Pre-condition: nodes are correctly ordered in bst
//Post-condition: nodes are displayed in order
//=====================================================================
void BinTree::inOrder(Node* treePtr) const
{
    if(treePtr !=nullptr)
    {
        inOrder(treePtr->leftChild);
        cout << *treePtr->data << " ";
        inOrder(treePtr->rightChild);

    }
}


void BinTree::copyTree(Node* rightTree, Node* &leftTree) const
{
    if (rightTree != nullptr)
    {
        leftTree = new Node;
        NodeData *copy = new NodeData(*rightTree->data);

        leftTree->data = copy;
        leftTree->leftChild = nullptr;
        leftTree->rightChild = nullptr;

        copyTree(rightTree->leftChild, leftTree->leftChild);
        copyTree(rightTree->rightChild, leftTree->rightChild);
    }
    else
    {
        leftTree = nullptr;
    }
}


//==========================displaySideways===========================
//Description: Displays nodedate in a BST using helper function
//Pre-condition
//Post-condition: BST is made
//====================================================================
void BinTree::displaySideways() const
{
    sideways(root, 0);
}


//=================================Sideways===========================
//Description: BST display
//Pre-condition
//Post-condition BST is made
//====================================================================
void BinTree::sideways(Node* current, int level) const {
    if (current != nullptr) {
        level++;
        sideways(current->rightChild, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->leftChild, level);
    }
}

int BinTree::maxDepth(const Node* node) const
{
    if (node == NULL) {
        return 0;
    } else {
        int leftDepth = maxDepth(node->leftChild);
        int rightDepth = maxDepth(node->rightChild);

        if (leftDepth > rightDepth)
        {
            return (leftDepth + 1);
        }
        else return (rightDepth + 1);
    }
};
