/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 2/11/2020
Instructor: Eric Reed
File Name: assignment5.cpp

Program Description: This program implements splay trees using top-down
splaying.  The template is derived from the base class, FHsearch_tree.
The FHavlTree template is provided in the course.  It is used as a model for
how to handle derived template syntax.  With this template, the node type
does not need to be changed, additional data member do not need to be added
to the tree, and some methods that required overriding in AVL trees due to the
height member (operator=, showHeight(), and the constructors) can be left
un-overriden, as their base class implementations will work for the splay
tree.  The purpose of this program is to derive the class template FHsplayTree
from FHsearch_tree.  The following public methods will be overriden: bool
insert(const Comparable &x); bool remove(const Comparable &x); and bool contains
(const Comparable &x) (which is an overload, since the const modifier on the
function is being lost and contains() modifies the tree due to a splay() call
deeper down, therefore not being able to be declared a const).  find() uses
splay() and it throws an exception if the item is not in the tree.  contains()
uses the public overriden/overloaded version of find().  const Comparable
&showRoot() is added as a public method and it returns the mRoot data, or an
automatic default object if there is no master root.  This helps for debugging
and proving that the class is splaying.  The following protected (private)
methods are added: void splay(FHs_treeNode<Comparable> * &root, const
Comparable & x); void rotateWithLeftChild(FHs_treeNode<Comparable> * &k2); and
void rotateWithRightChild(FHs_treeNode<Comparable> * &k2).  For implementation,
assume that the only operator overloaded by the base class is <.  No "header
nodes" and "null nodes" are used in the program.  When accessing base class
members from the derived class, this-> is used in front of them.  For example,
methods in FHsplayTree use syntax like: this->mRoot; this->mSize; this->mRoot
->data, etc.  When throwing a base class exception like NotFoundException,
the typename keyword is added so the base class exception can be fully
qualified.  leftTree and rightTree are not actual trees.  They are instead
node pointers.  They point to the root nodes of their respective growing trees
which are augmented one node-at-a-time as the algorithm progresses.  The main
that represents the 32-node int tree in the text is provided here.  Results from
this main are compared to the results with the diagrams in the text.  The
heights at the various stages should be the same as indicated by the diagram in
the text.
*/

// Assignment #5 Instructor Solution
// CS 2C, Foothill College, Michael Loceff

// Client / Splay Tree ----------------------------------------------

#include <iostream>
#include "FHsplayTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};

int main()
{
   int k;
   FHsplayTree<int> searchTree;
   //FHsearch_tree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);
   //cout << searchTree.showRoot() << endl;

   cout << "Initial size: " << searchTree.size() << endl;
   for (k = 1; k <= 32; k++)
   {
      searchTree.insert(k);
   }
   cout << "New size: " << searchTree.size() << endl;

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   // insert test
   // searchTree.insert(6);

   // remove test
   // searchTree.remove(3);

   for (k = -1; k < 10; k++)
   {
      // alt to find() - different error return
      // cout << (searchTree.contains(k) ? "Found\n" : "Not found\n");
      try
      {
         searchTree.find(k);
      }
      catch( ... )
      {
         cout << "oops ";
      }
      cout << "splay " << k << " --> root: " << searchTree.showRoot()
         << " height: " << searchTree.showHeight() << endl;
   }

   // FHsplayTree<int> searchTree2;
   // cout << "\nEmpty tree showRoot() test: " << endl;
   // cout << searchTree2.showRoot() << endl;

   return 0;
}

/*
 Output:
 Initial size: 0
 New size: 32

 Traversal:
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
    30 31 32

 oops splay -1 --> root: 1 height: 16
 oops splay 0 --> root: 1 height: 16
 splay 1 --> root: 1 height: 16
 splay 2 --> root: 2 height: 9
 splay 3 --> root: 3 height: 6
 splay 4 --> root: 4 height: 6
 splay 5 --> root: 5 height: 5
 splay 6 --> root: 6 height: 6
 splay 7 --> root: 7 height: 6
 splay 8 --> root: 8 height: 7
 splay 9 --> root: 9 height: 8
 Program ended with exit code: 0

 insert test:

 Initial size: 0
 New size: 32

 Traversal:
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
    30 31 32

 oops splay -1 --> root: 1 height: 16
 oops splay 0 --> root: 1 height: 16
 splay 1 --> root: 1 height: 16
 splay 2 --> root: 2 height: 17
 splay 3 --> root: 3 height: 16
 splay 4 --> root: 4 height: 16
 splay 5 --> root: 5 height: 15
 splay 6 --> root: 6 height: 14
 splay 7 --> root: 7 height: 8
 splay 8 --> root: 8 height: 7
 splay 9 --> root: 9 height: 8
 Program ended with exit code: 0

 remove test:

 Initial size: 0
 New size: 32

 Traversal:
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
    30 31 32

 oops splay -1 --> root: 1 height: 16
 oops splay 0 --> root: 1 height: 16
 splay 1 --> root: 1 height: 16
 splay 2 --> root: 2 height: 15
 oops splay 3 --> root: 4 height: 9
 splay 4 --> root: 4 height: 9
 splay 5 --> root: 5 height: 6
 splay 6 --> root: 6 height: 6
 splay 7 --> root: 7 height: 5
 splay 8 --> root: 8 height: 6
 splay 9 --> root: 9 height: 7
 Program ended with exit code: 0

 contain() test:

 Initial size: 0
 New size: 32

 Traversal:
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
    30 31 32

 Not found
 splay -1 --> root: 1 height: 16
 Not found
 splay 0 --> root: 1 height: 16
 Found
 splay 1 --> root: 1 height: 16
 Found
 splay 2 --> root: 2 height: 9
 Found
 splay 3 --> root: 3 height: 6
 Found
 splay 4 --> root: 4 height: 6
 Found
 splay 5 --> root: 5 height: 5
 Found
 splay 6 --> root: 6 height: 6
 Found
 splay 7 --> root: 7 height: 6
 Found
 splay 8 --> root: 8 height: 7
 Found
 splay 9 --> root: 9 height: 8
 Program ended with exit code: 0

 Empty tree showRoot() test:

 Initial size: 0
 New size: 32

 Traversal:
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
    30 31 32

 oops splay -1 --> root: 1 height: 16
 oops splay 0 --> root: 1 height: 16
 splay 1 --> root: 1 height: 16
 splay 2 --> root: 2 height: 9
 splay 3 --> root: 3 height: 6
 splay 4 --> root: 4 height: 6
 splay 5 --> root: 5 height: 5
 splay 6 --> root: 6 height: 6
 splay 7 --> root: 7 height: 6
 splay 8 --> root: 8 height: 7
 splay 9 --> root: 9 height: 8

 Empty tree showRoot() test:
 0
 Program ended with exit code: 0
 */
