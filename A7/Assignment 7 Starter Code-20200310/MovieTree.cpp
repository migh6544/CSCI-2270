#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

// Helper Functions:
void dltNode(TreeNode *node)
{
    if (node == NULL)
        return;
    if (node->leftChild != nullptr)
    {
        dltNode(node->leftChild);
    }
    if (node->rightChild != nullptr)
    {
        dltNode(node->rightChild);
    }
    LLMovieNode *temp = node->head;
    LLMovieNode *temp2 = nullptr;
    while (temp != nullptr)
    {
        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    node->head = nullptr;
    delete node;
}

void printList(TreeNode *parentNode)
{
    if (parentNode != nullptr)
    {
        printList(parentNode->leftChild);
        LLMovieNode *temp = parentNode->head;
        cout << "Movies starting with letter: " << parentNode->titleChar << endl;
        while (temp != nullptr)
        {
            cout << " >> " << temp->title << " " << temp->rating << endl;
            temp = temp->next;
        }
        printList(parentNode->rightChild);
    }
}

TreeNode *PlugInTreeNode(TreeNode *node, TreeNode *parent)
{
    if (parent == nullptr)
    {
        return node;
    }
    if (node->titleChar > parent->titleChar)
    {
        parent->rightChild = PlugInTreeNode(node, parent->rightChild);
        if (parent->rightChild != nullptr)
        {
            parent->rightChild->parent = parent;
        }
    }
    else if (node->titleChar < parent->titleChar)
    {
        parent->leftChild = PlugInTreeNode(node, parent->leftChild);
        if (parent->leftChild != nullptr)
        {
            parent->leftChild->parent = parent;
        }
    }
    return parent;
}

TreeNode *searchHelp(char titleChar, TreeNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->titleChar == titleChar)
    {
        return node;
    }
    else
    {
        if (node->titleChar < titleChar)
        {
            return searchHelp(titleChar, node->rightChild);
        }
        if (node->titleChar > titleChar)
        {
            return searchHelp(titleChar, node->leftChild);
        }
    }
}

TreeNode *searchNode(char titleChar, TreeNode *node)
{
    TreeNode *temp = searchHelp(titleChar, node);
    return temp;
}

void insertInLL(TreeNode *node, LLMovieNode *movie)
{
    if (node->head == nullptr)
    {
        node->head = movie;
    }
    else if (node->head->title > movie->title)
    {
        movie->next = node->head;
        node->head = movie;
    }
    else
    {
        LLMovieNode *temp = node->head;
        while (temp->next != nullptr && temp->next->title < movie->title)
        {
            temp = temp->next;
        }
        movie->next = temp->next;
        temp->next = movie;
    }
}

TreeNode *finderHelp(TreeNode *node, TreeNode *otherNode)
{
    if (node->titleChar == otherNode->titleChar)
    {
        return node;
    }
    else
    {
        if (node->titleChar < otherNode->titleChar)
        {
            return finderHelp(otherNode->rightChild, otherNode);
        }
        if (node->titleChar > otherNode->titleChar)
        {
            return finderHelp(node->leftChild, otherNode);
        }
    }
}

TreeNode *findParentNode(TreeNode *node, TreeNode *parentNode)
{
    TreeNode *tempTN = finderHelp(parentNode, node);
    if (tempTN->rightChild == node || tempTN->leftChild == node)
    {
        return node;
    }
    else
    {
        return nullptr;
    }
}

TreeNode *getMaxNode(TreeNode *node)
{
    if (node->rightChild == nullptr)
    {
        return node;
    }
    return getMaxNode(node->rightChild);
}

TreeNode *getMinNode(TreeNode *node)
{
    if (node->leftChild == nullptr)
    {
        return node;
    }
    return getMinNode(node->leftChild);
}

void eraseNode(TreeNode *&node, TreeNode *&root)
{
    if (node->rightChild == nullptr && node->leftChild == nullptr)
    {
        TreeNode *parent = node->parent;
        char titleChar = node->titleChar;
        delete node;
        node = nullptr;
        if (parent && parent->titleChar > titleChar)
        {
            parent->leftChild = node;
        }
        else if (parent != nullptr)
        {
            parent->rightChild = node;
        }
        else if (parent == nullptr)
        {
            root = node;
        }
    }
    else if (node->rightChild == nullptr && node->leftChild != nullptr)
    {
        TreeNode *max;
        max = node;
        node->leftChild->parent = node->parent;
        node = node->leftChild;
        TreeNode *parent = node->parent;
        if (parent && parent->titleChar > node->titleChar)
        {
            parent->leftChild = node;
        }
        else if (parent != nullptr)
        {
            parent->rightChild = node;
        }
        else if (parent == nullptr)
        {
            root = node;
        }
        delete max;
        max = nullptr;
    }
    else if (node->rightChild != nullptr && node->leftChild == nullptr)
    {
        TreeNode *min;
        min = node;
        node->rightChild->parent = node->parent;
        node = node->rightChild;
        TreeNode *parent = node->parent;
        if (parent && parent->titleChar > node->titleChar)
        {
            parent->leftChild = node;
        }
        else if (parent)
        {
            parent->rightChild = node;
        }
        else if (parent == NULL) // set the root if the deletion is in root
            root = node;
        delete min;
        min = nullptr;
    }
    else
    {
        TreeNode *max = getMinNode(node->rightChild);
        node->titleChar = max->titleChar;
        node->head = max->head;
        TreeNode *maxP = max->parent;
        eraseNode(max, root);
        if (maxP != NULL)
        {
            maxP->leftChild = max;
            max = nullptr;
        }
    }
}

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
    root = nullptr;
}

MovieTree::~MovieTree()
{
    if (root)
        dltNode(root);
    root = nullptr;
}

void MovieTree::printMovieInventory()
{
    printList(root);
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    TreeNode *searchTN = searchChar(title[0]);
    if (searchTN == nullptr)
    {
        TreeNode *tempTN = new TreeNode;
        tempTN->titleChar = title[0];
        root = PlugInTreeNode(tempTN, root);
        searchTN = searchChar(title[0]);
    }
    LLMovieNode *tempLL = new LLMovieNode(ranking, title, year, rating);
    tempLL->next = NULL;
    insertInLL(searchTN, tempLL);
}

void MovieTree::deleteMovie(string title)
{
    TreeNode *searchTN;
    searchTN = searchNode(title[0], root);
    if (searchTN == nullptr)
    {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
    }
    else
    {
        LLMovieNode *pres = searchTN->head;
        LLMovieNode *prev = pres;
        while (pres != nullptr)
        {
            if (pres->title == title && pres == searchTN->head)
            {
                if (pres->next == nullptr)
                {
                    delete pres;
                    searchTN->head = nullptr;
                    eraseNode(searchTN, root);
                    break;
                }
                else
                {
                    searchTN->head = pres->next;
                    delete pres;
                    break;
                }
            }
            else if (pres->title == title)
            {
                prev->next = pres->next;
                delete pres;
                break;
            }
            else
            {
                prev = pres;
                pres = pres->next;
            }
        }
        if (pres = nullptr)
        {
            cout << "Movie: " << title << " not found, cannot delete." << endl;
        }
    }
}

void MovieTree::leftRotation(TreeNode *curr)
{
    if (curr && curr->rightChild != NULL)
    {
        TreeNode *node = curr->parent;
        TreeNode *temp = curr->rightChild;
        if (node == NULL)
        {
            root = temp;
        }
        temp->parent = node;
        curr->parent = temp;
        curr->rightChild = temp->leftChild;
        temp->leftChild = curr;
        if (node)
        {
            if (node->leftChild == curr)
            {
                node->leftChild = temp;
            }
            else
            {
                node->rightChild = temp;
            }
        }
    }
    return;
}

//------ Given Methods--------//
void _grader_inorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    _grader_inorderTraversal(root->leftChild);
    cout << root->titleChar << " ";
    _grader_inorderTraversal(root->rightChild);
}

void MovieTree::inorderTraversal()
{
    _grader_inorderTraversal(root);
    cout << endl;
}

TreeNode *searchCharHelper(TreeNode *curr, char key)
{
    if (curr == NULL)
        return curr;
    else if (curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode *MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}