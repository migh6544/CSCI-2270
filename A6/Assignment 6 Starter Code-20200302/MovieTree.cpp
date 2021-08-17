#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

// Helper functions:
void printBSTree(MovieNode* node)
{
  if (node->left != nullptr)
  {
    printBSTree(node->left);
  }
  cout << "Movie: " << node->title << " " << node->rating << endl;
  if (node->right != nullptr)
  {
    printBSTree(node->right);
  }
}

void freeNode(MovieNode* node, MovieNode* parentNode)
{
  if (node->title <= parentNode->title && parentNode->left == nullptr)
  {
    parentNode->left = node;
  }
  else if (node->title <= parentNode->title && parentNode->left != nullptr)
  {
    freeNode(node, parentNode->left);
  }
  if (node->title >= parentNode->title && parentNode->right == nullptr)
  {
    parentNode->right = node;
  }
  else if (node->title >= parentNode->title && parentNode->right != nullptr)
  {
    freeNode(node, parentNode->right);
  }
}

MovieNode *findTitle(MovieNode *node, string movieTitle)
{
  bool foundMovie = false;
  MovieNode *parentNode = node;
  while (!foundMovie)
  {
    if (movieTitle == parentNode->title)
    {
      foundMovie = true;
      return parentNode;
    }
    if (parentNode->left == nullptr && parentNode->right == nullptr)
    {
      foundMovie = true;
      return nullptr;
    }
    if (parentNode->title >= movieTitle)
    {
      parentNode = parentNode->left;
    }
    else if (parentNode->title <= movieTitle)
    {
      parentNode = parentNode->right;
    }
  }
  return nullptr;
}

void queryMovie(MovieNode *parentNode, float rating, int year)
{
  if (parentNode->rating >= rating && parentNode->year >= year)
  {
    cout << parentNode->title << "(" << parentNode->year << ") " << parentNode->rating << endl;
  }
  if (parentNode->left != nullptr)
  {
    queryMovie(parentNode->left, rating, year);
  }
  if (parentNode->right != nullptr)
  {
    queryMovie(parentNode->right, rating, year);
  }
}

void aveRating(MovieNode *parentNode, MovieNode *aveRate)
{
  aveRate->year++;
  aveRate->rating += parentNode->rating;
  if (parentNode->left != nullptr)
  {
    aveRating(parentNode->left, aveRate);
  }
  if (parentNode->right != nullptr)
  {
    aveRating(parentNode->right, aveRate);
  }
}

void levelCount(MovieNode* ParentNode, int level)
{
  if (ParentNode == nullptr) return;
  if (level == 0) 
  {
    cout << "Movie: " << ParentNode->title << " " << ParentNode->rating << endl;
    return;
  }
  levelCount(ParentNode->left, level - 1);
  levelCount(ParentNode->right, level - 1);
}

// MovieNode: node struct that will be stored in the MovieTree BST
MovieTree::MovieTree()
{
  root = nullptr;
}

MovieTree::~MovieTree()
{
  root =nullptr;
}

void MovieTree::printMovieInventory()
{
  if (root != nullptr)
  {
    printBSTree(root);
  }
  else
  {
    cout << "Tree is Empty. Cannot print" << endl;
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
  MovieNode *temp = new MovieNode(ranking, title, year, rating);
  if (root == nullptr)
  {
    root = temp;
  }
  else
  {
    freeNode(temp, root);
  }
}

void MovieTree::findMovie(string title)
{
  MovieNode *theMovie = findTitle(root, title);
  if (theMovie != nullptr)
  {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << theMovie->ranking << endl;
    cout << "Title  :" << theMovie->title << endl;
    cout << "Year   :" << theMovie->year << endl;
    cout << "rating :" << theMovie->rating << endl;
  }
  else
  {
    cout << "Movie not found." << endl;
  }
}

void MovieTree::queryMovies(float rating, int year)
{
  if (root != nullptr)
  {
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    queryMovie(root, rating, year);
  }
  else
  {
    cout << "Tree is Empty. Cannot query Movies" << endl;
  }
}

void MovieTree::averageRating()
{
  if (root != nullptr)
  {
    MovieNode *average = new MovieNode(0, "", 0, 0);
    aveRating(root, average);
    int count = average->year;
    float rate = average->rating;
    rate = rate / count;
    cout << "Average rating:" << rate << endl;
  }
  else
  {
    cout << "Average rating:0.0" << endl;
  }
}

void MovieTree::printLevelNodes(int level)
{
  levelCount(root, level);
}