#include "bst.hpp"
#include <iostream>

using namespace std;

//recursive helper function to insert new piece of mail into BST
void insertMailHelper(Mail* root, Mail* newMail)
{
    //if newMail key is less than root's key, go to left subtree
    if(newMail->key < root->key)
    {
        //if left subtree is empty, insert newMail as root's left child
        if(root->left == NULL)
        {
            root->left = newMail;
        }
        //if root's left subtree is not empty, call insertMailHelper recursively on left subtree
        else 
        {
            insertMailHelper(root->left, newMail);
        }

    }

   
    else 
    {
         //if newMail key is greater than or equal to root's key, go to right subtree
        if(newMail->key >= root->key)
        {
            //if right subtree is empty, insert newMail as root's right child
            if(root->right==NULL)
            {
                root->right = newMail;
            }
            //if root's right subtree is not empty, call insertMailHelper recursively on right subtree
            else
            {
                insertMailHelper(root->right, newMail);
            }
            
        }
    }

}




void MailTrackBST::insertMail(int key)
{
//create new mail node to add in
Mail* newMail = new Mail;
newMail->key = key;
newMail->left = NULL; 
newMail->right = NULL;

//if empty tree, set newMail as the root 
if(root==NULL)
{
    root = newMail;
    return;
}

//if the tree is not empty, call helper function
else
{
    //cout << "adding " << key << endl;
    insertMailHelper(root, newMail);
}


}


Mail* searchMailHelper(Mail* root, int key)
{
    //if you find the node, return 
    if(root->key == key)
    {
        return root;
    }
    //if current node's key is less than the key you're looking for, recur on right subtree
    if (root->key < key)
    {
        //recur on right subtree
        if (root->right != NULL)
        {
            return searchMailHelper(root->right, key);
        }
       //if right subtree is empty, return null
        else
        {
            return NULL;
        }
        
    }
    //if current node's key is greater than the key you're looking for, recur on left subtree
    else
    {
        //recur on left subtree
        if (root->left != NULL)
        {
            return searchMailHelper(root->left, key);
        }
        //if left subtree is empty, return null
        else 
        {
            return NULL;
        }

    }
}




//is the purpose of the search function to return the node with the given key?
Mail* MailTrackBST::searchMail(int key)
{
   // cout << "searching " << key << endl;
    Mail* search = searchMailHelper(root, key);

    return search;

}

//prints out bst nodes in ascending order
void printHelper(Mail* root)
{
    if(root != NULL)
    {
       //inorder traveral
        printHelper(root->left);
        cout << root->key << endl;
        printHelper(root->right);

    }
}



void MailTrackBST::printTracking()
{
   //if nothing in bst
    if(root==NULL)
    {
     cout << "Tree is Empty. Cannot print" << endl;
    }

    //otherwise use recursive helper function to traverse bst
   else
    {
      printHelper(root);
    }

}