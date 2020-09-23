//test driver file

#include <iostream>
#include <fstream>

#include "nodedata.h"
#include "BinTree.h"
using namespace std;

//random array size
const int ARRAYSIZE = 100;

//global functions called in main
void buildTree(BinTree& T,  ifstream&);
void initArray(NodeData* []);


int main() {

    //open file from an fstream object inFile
    cout << "Open file using ifstream ---------------------------------------------"<< endl;
    cout << endl;
    ifstream inFile("inputdata.txt");
    if(!inFile)
    {
        cout << "Error: file did not open." << endl;
        return 1;
    }
    cout << "   File Opened Successfully." << endl;

    //create nodes to test against incoming strings
    cout<< endl << endl;
    cout << "Create test Nodes ----------------------------------------------------" << endl;
    NodeData jjND("jj");
    NodeData ppND("pp");
    NodeData bbbND("bbb");
    NodeData catND("cat");
    NodeData oooND("ooo");
    NodeData dddND("ddd");
    NodeData eND("e");
    NodeData mND("m");
    NodeData dogND("dog");
    NodeData andND("and");
    NodeData notND("not");
    NodeData sssND("sss");
    NodeData ttttND("tttt");
    NodeData yND("y");
    cout<< endl;

    cout << "     Test nodes: " << jjND << " " << ppND << " " << bbbND << " "
        << catND << " " << oooND << " " << dddND << " " <<  eND << " " <<  mND << " " <<  dogND << endl;


    //Initialize one tree for each string, and corresponding nodes
    cout<< endl;
    cout << endl;
    cout << "Initialize BinTree, Nodes and Array and Test functions ----------------" << endl;
    cout << endl;
    cout << endl;
    BinTree T, T2, dup;
    NodeData* ndArray[ARRAYSIZE];
    initArray(ndArray);

    cout << "Initial Data: ";
    buildTree(T, inFile);
    cout<< endl;
    //cout << "Use Copy Constructor------------------------------------------------- ";
    BinTree first(T);

    dup = dup = T;
    //cout << endl;

    while(!inFile.eof())
    {
        cout << "Tree inOrder: " << T << endl;
        cout << endl;
        T.displaySideways();
        cout << endl;

        //test retrieve
        NodeData* p;
        bool located;
        located = T.retrieve(jjND, p);
        cout << "Retrieve node jj: " << (located ? "located" : "not located") << endl;
        located = T.retrieve(ppND, p);
        cout << "Retrieve node pp: " << (located ? "located" : "not located") << endl;
        located = T.retrieve(catND, p);
        cout << "Retrieve node cat: " << (located ? "located" : "not located") << endl;
        located = T.retrieve(dogND, p);
        cout << "Retrieve node dog: " << (located ? "located" : "not located") << endl;
        located = T.retrieve(mND, p);
        cout << "Retrieve node m: " << (located ? "located" : "not located") << endl;

        //test getHeight
        cout << "Height    --> and:  " << T.getHeight(andND) << endl;
        cout << "Height    --> not:  " << T.getHeight(notND) << endl;
        cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
        cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
        cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
        cout << "Height    --> y:  " << T.getHeight(yND) << endl;

        // test == and !=
        T2 = T;
        cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
        cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
        cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
        dup = T;

        T.bstreeToArray(ndArray);
        T.arrayToBSTree(ndArray);
        T.displaySideways();


        T.makeEmpty();                  // empty out the tree
        initArray(ndArray);             // empty out the array

        cout << "---------------------------------------------------------------"
             << endl;
        cout << "Initial data:" << "  ";
        buildTree(T, inFile);
        cout << endl;


    }
    T.displaySideways();
    cout << endl;

    //test retrieve
    NodeData* p;
    bool located;
    located = T.retrieve(jjND, p);
    cout << "Retrieve node jj: " << (located ? "located" : "not located") << endl;
    located = T.retrieve(ppND, p);
    cout << "Retrieve node pp: " << (located ? "located" : "not located") << endl;
    located = T.retrieve(catND, p);
    cout << "Retrieve node cat: " << (located ? "located" : "not located") << endl;
    located = T.retrieve(dogND, p);
    cout << "Retrieve node dog: " << (located ? "located" : "not located") << endl;
    located = T.retrieve(mND, p);
    cout << "Retrieve node m: " << (located ? "located" : "not located") << endl;

    //test getHeight
    cout << "Height    --> and:  " << T.getHeight(andND) << endl;
    cout << "Height    --> not:  " << T.getHeight(notND) << endl;
    cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
    cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
    cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
    cout << "Height    --> y:  " << T.getHeight(yND) << endl;

    // test == and !=
    T2 = T;
    cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
    cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
    cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
    dup = T;

    T.bstreeToArray(ndArray);
    T.arrayToBSTree(ndArray);


    return 0;
}

void buildTree(BinTree& T, ifstream& inFile)
{
    string s;

    for (;;)
    {   inFile >> s;
        cout << s << " ";

        if (s == "$$")
        {
            break;
        }
        //if (inFile.eof())
        //{
        //    break;
        //}
        NodeData* dataptr = new NodeData(s);
        //NodeData* curr;

        //BinTree T;
        bool dataInserted = T.insert(dataptr);
        if(!dataInserted)
        {
            delete dataptr;
        }
    }

}

void initArray(NodeData* ndArray[])
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        ndArray[i] = nullptr;
    }
}