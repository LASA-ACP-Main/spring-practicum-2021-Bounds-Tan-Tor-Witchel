#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#ifndef BSTREE_H
#define BSTREE_H

using namespace std;

/*
 * Node Declaration
 */
struct Bnode
{
    int key_value;
    struct Bnode *p_left;
    struct Bnode *p_right;
};

/*
 * Class Declaration
 */
class BST
{
public:
    Bnode* root;
    void find(int, Bnode **, Bnode **);
    void insert(Bnode *, Bnode *);
    void remove(int);
    void case_0(Bnode *,Bnode *);
    void case_1(Bnode *,Bnode *);
    void case_2(Bnode *,Bnode *);
    void outputToConsole(Bnode *, int);
    void outputAsCSV(std::string filePath);
    void outputAsString(Bnode*, int, string* str);
    BST()
    {
        root = NULL;
    }
};


#endif //BSTREE_H
