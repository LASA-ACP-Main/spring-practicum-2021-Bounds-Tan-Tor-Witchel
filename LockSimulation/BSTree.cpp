/*
 * Binary Search Tree class
 * Do not alter the display() function, this will break the Repl.it 
 * tests
 */

 
#include <iostream>
#include <cstdlib>
#include "BSTree.h"

using namespace std;


 
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
    // if (we are at root)
    if(tree == NULL)
    {
        // Just create a single node for root to point to,
        //    with all the data in it.
        tree = newnode;
        root = newnode;
        return;
    }
    // if (there is already a node with our key value)
    if(newnode->key_value == tree->key_value)
    {
        //Just return
        return;
    }
    //if (the new node is less than the current node)
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
        if (tree->p_right != NULL)
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
    if (location->p_left == NULL && location->p_right == NULL)
    {
        case_0(parent, location);
    }
        
    //if (there is one child on left only)
    else if (location->p_left != NULL && location->p_right == NULL)
    {
        case_1(parent, location);
    }
        
    //if (there is one child on right only)
    else if (location->p_left == NULL && location->p_right != NULL)
    {
        case_1(parent, location);
    }

    // if (there are childred on left and right)
    else 
    {
        case_2(parent, location);
    }
        
    free(location);
}
 
/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(Bnode *prnt, Bnode *loc )
{
    //if (we are at the root)
    if (prnt == NULL && loc == root)
    {
        //update the root
        root = NULL;
    }
    else
    {
      // otherwise simply remove node
      if (prnt->p_left == loc) {
          prnt->p_left = NULL;
      }
      else
      {
          prnt->p_right = NULL;
      }
    }
}
 
/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(Bnode *prnt, Bnode *loc)
{
    Bnode *child;
    //if (the child is on the left?)
    if (loc->p_left != NULL)
    {
        //point left
        child  = loc->p_left;
    }
        
   // else  // must be the right side has child
    else
    {
        // point right
        child = loc->p_right;
    }
        
    //if (we are at the root handle specialy)
    if (prnt == NULL && loc == root)
    {
       // update the root
       root = child;
    }
    else
    {
        //if (the node is left child of parent)
        if (prnt->p_left == loc)
        {
            //promote the left
            prnt->p_left = child;
        }
            
        //else // the node is right of parent
        else
        {
            //promote right
            prnt->p_right = child;
        }
    }
}
 
/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(Bnode *prnt, Bnode *loc)
{
    Bnode* tmpP = loc;
    Bnode* tmp = loc->p_right;
    //find successor
    
    while (tmp->p_left != NULL) {
      tmpP = tmp;
      tmp = tmp->p_left;   
    }
    //parent points to successor
    if (loc->key_value < prnt->key_value) 
        prnt->p_left = tmp;
    else
        prnt->p_right = tmp;
   
        
    //set successor p_left to loc p_left
    tmp->p_left = loc->p_left;
    tmpP->p_left = tmp->p_right;
    //tmp->p_left = loc->p_left;    
    if (loc->p_right->key_value == tmp->key_value)
        tmp->p_right = loc->p_right->p_right;
    else
        tmp->p_right = loc->p_right;  
}
 

/*
 * Display Tree Structure
 */
void BST::display(Bnode *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->p_right, level+1);
        //cout<<endl;
        if (ptr == root)
            cout<<"Root->: ";
        else
        {
            // for (i = 0;i < level;i++)
            //     cout<<"       ";
	}
        cout<<ptr->key_value<<endl;
        display(ptr->p_left, level+1);
    }
}

