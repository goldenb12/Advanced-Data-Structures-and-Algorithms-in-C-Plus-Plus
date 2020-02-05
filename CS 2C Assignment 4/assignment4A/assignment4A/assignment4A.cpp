/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 2/4/2020
Instructor: Eric Reed
File Name: assignment4A.cpp

Program Description: Take a binary search tree implemented in the modules and
modify it to use lazy deletion instead of "hard deletion".  The file
FHlazySearchTree.h is copied and named FHlazySearchTree.h and the name of the
classes FHsearch_tree and FHs_treeNode are changed to FHlazySearchTree and
FHlazySearchTreeNode, respectively.  A bool deleted member is added to
FHlazySearchTreeNode and a new int mSizeHard member is added to the
FHlazySearchTree class.  mSizeHard tracks the number of "hard" nodes in the
class (both deleted and undeleted).  mSize is still there and only reflects the
number of undeleted nodes.  mSizeHard is known by the client for debugging
purposes.  It is given an accessor, sizeHard(), so the client can test the
class by displaying both the soft size and the hard size.  To implement lazy
deletion, remove() in the file is revised.  insert() and other methods are
adjusted in accordance with the new deletion technique.  This means that the
deleted member is inspected when traversing for the data and taking the
appropriate action is determined based on the value of the deleted member.
A public/private pair, void collectGarbage(), is added to allow the client to
truly remove all deleted nodes.  This is done by traversing the tree and doing
a hard remove on each deleted node.  This needs a private removeHard() utility
that works like the old remove() method does.  A couple of findMin() and
findMax() tests are done at various stages of the program to ensure that
exception handling is working in both tests.
*/

// CS 2C  Simple Search Tree Client - Lazy Deletion, int data
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
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
   FHlazySearchTree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);

   cout << "testing findMin() and findMax() on hard-empty tree:" << endl;
   try
   {
      cout << "Min: " << searchTree.findMin() << "\nMax: "
         << searchTree.findMax() << endl;
   }
   catch (FHlazySearchTree<int>::EmptyTreeException)
   {
      cout << "error - empty tree" << endl;
   }

   cout << "\ninitial size: " << searchTree.size() << endl;
   searchTree.insert(50);
   searchTree.insert(20);
   searchTree.insert(30);
   searchTree.insert(70);
   searchTree.insert(10);
   searchTree.insert(60);

   cout << "After populating -- traversal and sizes: \n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting garbage on new tree - should be no garbage." << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   // test assignment operator
   FHlazySearchTree<int> searchTree2 = searchTree;

   cout << "\n\nAttempting 1 removal: \n";
   if (searchTree.remove(20))
   {
      cout << "removed " << 20 << endl;
   }
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting Garbage - should clean 1 item. " << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting Garbage again - no change expected. " << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   // test soft insertion and deletion:

   cout << "Adding 'hard' 22 - should see new sizes. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "\nAfter soft removal. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Repeating soft removal. Should see no change. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Soft insertion. Hard size should not change. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "\n\nAttempting 100 removals: \n";
   for (k = 100; k > 0; k--)
   {
      if (searchTree.remove(k))
         cout << "removed " << k << endl;
   }
   searchTree.collectGarbage();

   cout << "\nsearchTree now:\n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   searchTree2.insert(500);
   searchTree2.insert(200);
   searchTree2.insert(300);
   searchTree2.insert(700);
   searchTree2.insert(100);
   searchTree2.insert(600);
   cout << "\nsearchTree2:\n";
   searchTree2.traverse(intPrinter);
   cout << "\ntree 2 size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.sizeHard() << endl;

   cout << "\ntesting findMin() and findMax() on partially-empty tree 2:"
      << endl;
   try
   {
      cout << "Min: " << searchTree2.findMin() << "\nMax: "
         << searchTree2.findMax() << endl;
   }
   catch (FHlazySearchTree<int>::EmptyTreeException)
   {
      cout << "error - empty tree" << endl;
   }

   searchTree2.remove(100); searchTree2.remove(200);
   searchTree2.remove(30); searchTree2.remove(50);
   searchTree2.remove(600); searchTree2.remove(700);
   cout << "\nsearchTree2 after remaining nodes removed:\n";
   searchTree2.traverse(intPrinter);
   cout << "\ntree 2 size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.sizeHard() << endl;

   cout << "\ntesting findMin() and findMax() on soft-empty tree 2:" << endl;
   try
   {
      cout << "Min: " << searchTree2.findMin() << "\nMax: "
         << searchTree2.findMax() << endl;
   }
   catch (FHlazySearchTree<int>::EmptyTreeException)
   {
      cout << "error - empty tree" << endl;
   }

   cout << "\nCompleting garbage collection on tree 2: \n";
   searchTree2.collectGarbage();
   cout << "\ntree 2 size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.sizeHard() << endl;

   return 0;
}

/*
 Output:
 testing findMin() and findMax() on hard-empty tree:
 Min: error - empty tree

 initial size: 0
 After populating -- traversal and sizes:
 10 20 30 50 60 70
 tree 1 size: 6  Hard size: 6
 Collecting garbage on new tree - should be no garbage.
 tree 1 size: 6  Hard size: 6


 Attempting 1 removal:
 removed 20
 tree 1 size: 5  Hard size: 6
 Collecting Garbage - should clean 1 item.
 tree 1 size: 5  Hard size: 5
 Collecting Garbage again - no change expected.
 tree 1 size: 5  Hard size: 5
 Adding 'hard' 22 - should see new sizes.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6

 After soft removal.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Repeating soft removal. Should see no change.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Soft insertion. Hard size should not change.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6


 Attempting 100 removals:
 removed 70
 removed 60
 removed 50
 removed 30
 removed 22
 removed 10

 searchTree now:

 tree 1 size: 0  Hard size: 0

 searchTree2:
 10 20 30 50 60 70 100 200 300 500 600 700
 tree 2 size: 12  Hard size: 12

 testing findMin() and findMax() on partially-empty tree 2:
 Min: 10
 Max: 700

 searchTree2 after remaining nodes removed:
 10 20 60 70 300 500
 tree 2 size: 6  Hard size: 12

 testing findMin() and findMax() on soft-empty tree 2:
 Min: 10
 Max: 500

 Completing garbage collection on tree 2:

 tree 2 size: 6  Hard size: 6
 Program ended with exit code: 0
*/
