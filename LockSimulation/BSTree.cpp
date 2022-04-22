
#include "BSTree.h"


/*
 * Find Element in the Tree
 * find a node by item_key and provide an updated parent node
 *   pointer and location node pointer
 */


void BST::find(int item_key, Bnode **prnt, Bnode **loc)
{
    Bnode *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *prnt = NULL;
        return;
    }
    if (item_key == root->key_value)
    {
        *loc = root;
        *prnt = NULL;
        return;
    }
    if (item_key < root->key_value)
        ptr = root->p_left;
    else
        ptr = root->p_right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (item_key == ptr->key_value)
        {
            *loc = ptr;
            *prnt = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item_key < ptr->key_value)
            ptr = ptr->p_left;
        else
            ptr = ptr->p_right;
    }
    *loc = NULL;
    *prnt = ptrsave;
}

/*
 * Inserting Element into the Tree
 */
void BST::insert(Bnode *tree, Bnode *newnode)
{
    if(root==NULL){
        root = newnode;
        return;
    }

    if(tree == root) {
        Bnode **parentNode = new Bnode *;
        Bnode **location = new Bnode *;
        find(newnode->key_value, parentNode, location);
        if (*location != NULL) {
            //Just return
            return;
        }
    }

    if(newnode->key_value < tree->key_value)
    {
        //if (see if something is already a child on the left)
        if(tree->p_left != NULL)
        {
            // if so, the recurse insert at this subtree
            insert(tree->p_left, newnode);
        }
        else
        {
            // otherwise the new node goes here as a leaf (ie no children)
            tree->p_left = newnode;
            return;
        }
    }
    else  // it must be to the right
    {
        //if (is there already a child on right?)
        if(tree->p_right != NULL)
        {
            // if so, the recurse insert at this subtree
            insert(tree->p_right, newnode);
        }
        else
        {
            // otherwise the new node goes here as a leaf (ie no children)
            tree->p_right = newnode;
            return;
        }
    }

}

/*
 * Delete Element from the tree
 */
void BST::remove(int item)
{
    Bnode *parent, *location;
    if (root == NULL)
    {
        cout<<"Tree empty"<<endl;
        return;
    }
    find(item, &parent, &location);
    if (location == NULL)
    {
        cout<<"Item not present in tree"<<endl;
        return;
    }
    //if (there is no child on left or right)
    if(location->p_left == NULL && location->p_right == NULL){
        case_0(parent, location);
    }
    else if(location->p_left != NULL && location->p_right == NULL){
        //if (there is one child on left only)
        case_1(parent, location);
    }
    else if(location->p_left == NULL && location->p_right != NULL){
        //if (there is one child on right only)
        case_1(parent, location);
    }
    else if(location->p_left != NULL && location->p_right != NULL){
        // if (there are childred on left and right)
        case_2(parent, location);
    }
    else{
        cout << "BST::Remove Reached impossible condition";
    }
}

/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(Bnode *prnt, Bnode *loc )
{
    //free(loc);

    if(loc == root){
        root = NULL;
    }
    else {
        free(loc);
        prnt->p_left = NULL;
        prnt->p_right = NULL;
    }

}

/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(Bnode *prnt, Bnode *loc)
{
    Bnode* child;
    if(loc->p_left != NULL && loc->p_right == NULL){
        child = loc->p_left;
    }
    else if (loc->p_right != NULL && loc -> p_left == NULL){
        child = loc->p_right;
    }
    else{
        cout << "BST::case_1 Error: Reached impossible position";
    }

    if(loc == root){
        root = child;
    }
    else if(prnt->p_left == loc){
        prnt->p_left = child;
    }
    else{
        prnt->p_right = child;
    }
    free(loc);
}

/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(Bnode *prnt, Bnode *loc)
{
    // temporary pointers for node we are manipulating
    Bnode* sPrnt = loc;
    Bnode* sLoc = loc->p_right;
    // Find successor: Step to the right child
    // Find the min of the subtree on parent's right
    while(sLoc->p_left != NULL){
        sPrnt = sLoc;
        sLoc = sLoc->p_left;
    }
    //if (found node has no children)
    if(sLoc->p_right == NULL){
        // Replace the target node with the successor node
        if(sPrnt->p_right == sLoc){
            sPrnt->p_right = NULL;
        }
        else {
            sPrnt->p_left = sLoc->p_right;
        }
    }
    else{
        // Temporarily remove the successor node by replacing it with
        // its right child, we will replace the node we are removing
        // with the successor we just removed.
        if(sPrnt->p_right == sLoc){
            sPrnt->p_right = sLoc->p_right;
            sLoc->p_right = NULL;
        }
        else {
            sPrnt->p_left = sLoc->p_right;
            sLoc->p_right = NULL;
        }
    }

    //if (we are at root)
    if(loc == root)
    {
        //then update root
        root = sLoc;
    }
    else
    {
        // Insert the successor node where the target node we
        //   are removing is located
        if(prnt->p_left == loc){
            prnt->p_left = sLoc;
        }
        else{
            prnt->p_right = sLoc;
        }

    }
    // then update the successor child pointers to reflect the old
    //     target's child pointers.
    sLoc->p_left = loc->p_left;
    sLoc->p_right = loc->p_right;
    free(loc);
}


/*
 * Display Tree Structure
 */
void BST::outputToConsole(Bnode *ptr, int level) {
    if (ptr != NULL) {
        outputToConsole(ptr->p_right, level + 1);
        cout << ptr->key_value << endl;
        outputToConsole(ptr->p_left, level + 1);
    }
}

void BST::outputAsString(Bnode *ptr, int level, string* str) {
    if (ptr != NULL) {
        outputAsString(ptr->p_right, level + 1, str);
        *str += to_string(ptr->key_value);
        *str += ",";
        outputAsString(ptr->p_left, level + 1, str);
    }
}

void BST::outputAsCSV(std::string filePath) {
    std::ofstream myFile(filePath);
    if (myFile.is_open())
    {
        string* str = new string;
        *str = "";
        outputAsString(root, 0, str);
        myFile << *str;
    }
    else{
        std::cout << "failed to write valid RFIDs to file" << std::endl;
    }
    myFile.close();
}