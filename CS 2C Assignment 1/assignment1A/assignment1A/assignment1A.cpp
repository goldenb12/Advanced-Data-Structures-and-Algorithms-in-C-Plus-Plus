/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 1/14/2020
Instructor: Eric Reed
File Name: assignment1A.cpp

Program Description: Program an algorithm for the subset sum problem.
Need to use a data structure that can represent any subset of a given set, S,
and have a method capable of generating a new subset from existing subsets.
The algorithm should initialize the collection Col with one sublist
(empty sublist) and loop over all elements x in S.  It will loop over all
elements, L that are already members of Col if sum(L) + x <= t, add the
sublist L + x to Col or if sum(L) + x == t, break from both loops.
It can also be that of the sublists that end up in Col, we must find L',
with the largest sum().  Col is a vector of Sublist objects.
*/

#include <iostream>
#include <vector>
using namespace std;

// class Sublist definition
class Sublist
{
public:
   Sublist(vector<int> *orig = NULL)
      : sum(0), originalObjects (orig) { }
   Sublist addItem( int indexOfItemToAdd );
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<int> *originalObjects;
   vector<int> indices;
};

// Sublist addItem() member function definition
Sublist Sublist::addItem( int indexOfItemToAdd )
{
   Sublist newSublist(originalObjects);
   for (int i = 0; i < indices.size(); i++)
   {
      newSublist.indices.push_back(indices[i]);
   }
   newSublist.indices.push_back(indexOfItemToAdd);
   newSublist.sum = sum + (*originalObjects)[indexOfItemToAdd];
   return newSublist;
}

// Sublist showSublist() member function definition
void Sublist::showSublist() const
{
   if (indices.size() == 0)
   {
      cout << "Empty Sublist" << endl;
   }
   else
   {
      cout << "Sublist -----------------------------" << endl;
      cout << " sum : " << sum << endl;

      for (int i = 0; i < indices.size() - 1; i++)
      {
         cout << " array[" << indices[i] << "] = "
            << (*originalObjects)[indices[i]] << ",   ";
      }
      cout << " array[" << indices[indices.size() - 1] << "] = "
         << (*originalObjects)[indices[indices.size() - 1]] << endl;
   }
}

int main()
{
   int TARGET = 180;
   vector<int> dataSet;
   vector<Sublist> choices;
   int k, j, numSets, max, masterSum;

   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   choices.clear();
   cout << "Target time: " << TARGET << endl;

   // Initialize Sublist empty set
   Sublist empty(&dataSet);
   choices.push_back(empty);
   numSets = 1;
   max = 0;
   masterSum = 0;

   // Loop for finding masterSum from data set
   for (int i = 0; i < dataSet.size(); i++)
   {
      masterSum += dataSet[i];
   }

   // When TARGET is larger than masterSum
   if (TARGET > masterSum)
   {
      cout << "TARGET is larger than masterSum." << endl;
      exit(1);
   }
   else
   {
      // Loop implements subset sum algorithm
      for (int i = 0; i < dataSet.size(); i++)
      {
         for (j = 0; j < numSets; j++)
         {
            if (choices[j].getSum() + dataSet[i] <= TARGET)
            {
               choices.push_back(choices[j].addItem(i));
            }

            if (choices[j].getSum() + dataSet[i] == TARGET)
            {
               max = choices.size() - 1;
               break;
            }
         }
         numSets = choices.size();
      }

      // Sublist with max sum
      if (max == 0)
      {
         for (k = 0; k < choices.size(); k++)
         {
            if (choices[k].getSum() > choices[max].getSum())
            {
               max = k;
            }
         }
      }

      choices[max].showSublist();
   }

   return 0;
}

/*
 Output:
 Target time: 180
 Sublist -----------------------------
  sum : 179
  array[0] = 20,    array[1] = 12,    array[3] = 15,    array[4] = 25,
  array[5] = 19,    array[6] = 29,    array[7] = 18,    array[8] = 11,
  array[9] = 13,    array[10] = 17
 Program ended with exit code: 0

 Target time: 160
 Sublist -----------------------------
  sum : 160
  array[0] = 20,    array[2] = 22,    array[3] = 15,    array[4] = 25,
  array[5] = 19,    array[6] = 29,    array[9] = 13,    array[10] = 17
 Program ended with exit code: 0

 Target time: 201
 Sublist -----------------------------
  sum : 201
  array[0] = 20,    array[1] = 12,    array[2] = 22,    array[3] = 15,
  array[4] = 25,    array[5] = 19,    array[6] = 29,    array[7] = 18,
  array[8] = 11,    array[9] = 13,    array[10] = 17
 Program ended with exit code: 0

 Target time: 202
 TARGET is larger than masterSum.
 Program ended with exit code: 1

 Target time: 800
 TARGET is larger than masterSum.
 Program ended with exit code: 1

 */

