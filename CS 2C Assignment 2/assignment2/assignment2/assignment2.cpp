/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 1/21/2020
Instructor: Eric Reed
File Name: assignment2.cpp

Program Description: Design a class template SparseMat which implements a sparse
matrix.  The base ADTs, FHvector and FHlist, will build the class.  One of the
primary instance methods is SparseMat(int r, int c, const Object &defaultVal),
a constructor that establishes a size
(row size and column size that are both greater than or equal to 1) and a
default value for all elements.  Another method is
const Object& get(int r, int c) const, an accessor that returns the object
stored in row r and column c.  It throws a user-defined exception if matrix
bounds (row and/or column) are violated.  Another method is
bool set(int r, int c, const Object &x), a mutator that places x in row r and
column c.  It returns false without an exception if bounds are violated.  If
x is the default value, it removes any existing node from the data
structure, since there's never a need to explicitly store the default value.
If there isn't a node present in the internal data representation, set(),adds
one if x is not default and store x in it.  Another method is void clear(),
which clears all the rows, effectively setting all values to the defaultVal
(but leaves the matrix size the same).  The final method is
void showSubSquare(int start, int size), a display method that shows a
sub-matrix anchored at (start, start) and whose size is size x size.  It shows
the rows from start to start + size - 1 and the columns from start to start
+ size - 1.  This is used for debugging, where we can't see the matrix all
at once.
*/

#include <iostream>
#include <cassert>
#include "FHlist.h"
#include "FHvector.h"
using namespace std;

// MatNode class declaration
template <class Object>
class MatNode
{
protected:
   int col;

public:
   Object data;
   // we need a default constructor for lists
   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
   int getCol() const { return col; }

   // not optimized yet for set() = defaultVal;  refer to forums
   const Object & operator=( const Object &x ) { return (data = x);}
};

// SparseMat class declaration
template <class Object>
class SparseMat
{
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;

public:
   SparseMat(int r, int c, const Object &defaultVal);
   const Object& get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);

   class OutOfBoundsException { };
};

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

// --------------- main ---------------
int main()
{
   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

   // test mutators
   mat.set(2, 5, 10);
   mat.set(2, 5, 35);   // should overwrite the 10
   mat.set(3, 9, 21);
   mat.set(MAT_SIZE, 1, 5);  // should fail silently
   mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
   mat.set(4, 4, -9);
   mat.set(4, 4, 0);   // should remove the -9 node entirely
   mat.set(MAT_SIZE-1, MAT_SIZE-1, 99);

   // test accessors and exceptions
   try
   {
      cout << mat.get(7, 8) << endl;
      cout << mat.get(2, 5) << endl;
      cout << mat.get(9, 9) << endl;
      cout << mat.get(-4, 7) << endl;  // should throw an exception
   }
   catch (...)
   {
      cout << "oops" << endl;
   }

   // show top left 15x15
   mat.showSubSquare(0, 15);

   cout << endl << endl << endl;

   // show bottom right 15x15
   mat.showSubSquare(MAT_SIZE - 15, 15);
}

// SparseMat instance methods
template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal)
{
   // assert function is used to check logically impossible situations
   assert(r >= 1 && c >= 1);
   rowSize = r;
   colSize = c;
   for (int i = 0; i < colSize; i++)
   {
      rows.push_back(MatRow());
   }
}

template <class Object>
const Object& SparseMat<Object>::get(int r, int c) const
{
   if (r >= rowSize || c >= colSize)
   {
      throw OutOfBoundsException();
   }

   typename MatRow::const_iterator iter;
   typename MatRow::const_iterator end = rows[r].end();

   for (iter = rows[r].begin(); iter != end; iter++)
   {
      if (c == (*iter).getCol())
      {
         return (*iter).data;
      }
   }
   return defaultVal;
}

template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
   if (r >= rowSize || c >= colSize)
   {
      return false;
   }

   typename MatRow::iterator iter;
   typename MatRow::iterator end = rows[r].end();

   for (iter = rows[r].begin(); iter != end; iter++)
   {
      if (c == (*iter).getCol())
      {
         if (x == defaultVal)
         {
            rows[r].erase(iter);
         }
         else
         {
            (*iter).data = x;
         }
         return true;
      }
   }

   MatNode<Object> newNode(c, x);
   rows[r].push_back(newNode);
   return true;
}

template <class Object>
void SparseMat<Object>::clear()
{
   for (int i = 0; i < rowSize; i++)
   {
      rows[i].clear();
   }
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
   for (int i = start; i < (start + size); i++)
   {
      for (int j = start; j < (start + size); j++)
      {
         cout.width(2);
         cout << get(i, j) << " ";
      }
      cout << endl;
   }
}

/*
 Output:
 0
 35
 21
 oops
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0 35  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0



  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0 99
 Program ended with exit code: 0
 */
