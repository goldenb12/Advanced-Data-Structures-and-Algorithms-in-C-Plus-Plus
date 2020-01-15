/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 1/14/2020
Instructor: Eric Reed
File Name: assignment1C.cpp

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
#include <ctime>
#include "iTunes.h"
using namespace std;

// class Sublist definition with a class template
template <class T>
class Sublist
{
public:
   Sublist(vector<T> *orig = NULL)
      : sum(0), originalObjects (orig) { }
   Sublist addItem( int indexOfItemToAdd );
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<T> *originalObjects;
   vector<int> indices;
};

// << operator overload prototype
ostream& operator<<(ostream &out, const iTunesEntry &tune);

// + operator overload prototype
int operator+(int num, const iTunesEntry &tune);

// << operator overloading as a global scope function
ostream& operator<<(ostream &out, const iTunesEntry &tune)
{
   out << tune.getTitle() << " by " << tune.getArtist();
   out << "(" << tune.getTime() << ")";
   return out;
}

// + operator overloading as a global scope function
int operator+(int num, const iTunesEntry &tune)
{
   return num + tune.getTime();
}

// Sublist addItem() member function definition with a class template
template <class T>
Sublist<T> Sublist<T>::addItem( int indexOfItemToAdd )
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

// Sublist showSublist() member function definition with a class template
template <class T>
void Sublist<T>::showSublist() const
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
   const int TUNES_TARGET = 3600;
   const int INT_TARGET = 180;
   vector<int> intDataSet;
   vector<Sublist<int>> intChoices;
   vector<iTunesEntry> tunesDataSet;
   vector<Sublist<iTunesEntry>> tunesChoices;
   int k, j, numSets, max, array_size, masterSum;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
         << " for input.\n";
      exit(1);
   }

   cout << "iTunes Run -----------------------------" << endl;
   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
   {
      tunesDataSet.push_back(tunes_input[k]);
   }

   cout << "Target time: " << TUNES_TARGET << endl;

   // Initialize Sublist empty set with iTunesEntry
   Sublist<iTunesEntry> tunesEmpty(&tunesDataSet);
   tunesChoices.push_back(tunesEmpty);
   numSets = 1;
   max = 0;
   masterSum = 0;

   // Loop for finding masterSum from iTunes data set
   for (int i = 0; i < tunesDataSet.size(); i++)
   {
      masterSum = masterSum + tunesDataSet[i];
   }

   // When TUNES_TARGET is larger than masterSum
   if (TUNES_TARGET > masterSum)
   {
      cout << "TUNES_TARGET is larger than masterSum." << endl;
      exit(1);
   }
   else
   {
      // Loop implements subset sum algorithm
      for (int i = 0; i < tunesDataSet.size(); i++)
      {
         for (j = 0; j < numSets; j++)
         {
            if (tunesChoices[j].getSum() + tunesDataSet[i] <= TUNES_TARGET)
            {
               tunesChoices.push_back(tunesChoices[j].addItem(i));
            }

            if (tunesChoices[j].getSum() + tunesDataSet[i] == TUNES_TARGET)
            {
               max = tunesChoices.size() - 1;
               break;
            }
         }
      numSets = tunesChoices.size();
      }

      // Sublist with max sum
      if (max == 0)
      {
         for (k = 0; k < tunesChoices.size(); k++)
         {
            if (tunesChoices[k].getSum() > tunesChoices[max].getSum())
            {
               max = k;
            }
         }
      }

      tunesChoices[max].showSublist();
   }

   // how we determine the time elapsed -------------------
   stopTime = clock();
   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   cout << "Integer Run -----------------------------" << endl;
   // time the algorithm -------------------------
   startTime = clock();

   intDataSet.push_back(20); intDataSet.push_back(12); intDataSet.push_back(22);
   intDataSet.push_back(15); intDataSet.push_back(25);
   intDataSet.push_back(19); intDataSet.push_back(29);
   intDataSet.push_back(18);
   intDataSet.push_back(11); intDataSet.push_back(13); intDataSet.push_back(17);

   intChoices.clear();
   cout << "Target time: " << INT_TARGET << endl;

   // Initialize Sublist empty set with int
   Sublist<int> intEmpty(&intDataSet);
   intChoices.push_back(intEmpty);
   numSets = 1;
   max = 0;
   masterSum = 0;

   // Loop for finding masterSum from int data set
   for (int i = 0; i < intDataSet.size(); i++)
   {
      masterSum += intDataSet[i];
   }

   // When INT_TARGET is larger than masterSum
   if (INT_TARGET > masterSum)
   {
      cout << "INT_TARGET is larger than masterSum." << endl;
      exit(1);
   }
   else
   {
      // Loop implements subset sum algorithm
      for (int i = 0; i < intDataSet.size(); i++)
      {
         for (j = 0; j < numSets; j++)
         {
            if (intChoices[j].getSum() + intDataSet[i] <= INT_TARGET)
            {
               intChoices.push_back(intChoices[j].addItem(i));
            }

            if (intChoices[j].getSum() + intDataSet[i] == INT_TARGET)
            {
               max = intChoices.size() - 1;
               break;
            }
         }
         numSets = intChoices.size();
      }

      // Sublist with max sum
      if (max == 0)
      {
         for (k = 0; k < intChoices.size(); k++)
         {
            if (intChoices[k].getSum() > intChoices[max].getSum())
            {
               max = k;
            }
         }
      }

      intChoices[max].showSublist();
   }

   return 0;
}

/*
 Output:
 iTunes Run -----------------------------
 Target time: 3600
 Sublist -----------------------------
  sum : 3600
  array[1] = Quitter by Carrie Underwood(220),
  array[2] = Russian Roulette by Rihanna(228),
  array[3] = All My Life by Foo Fighters(263),
  array[4] = Monkey Wrench by Foo Fighters(230),
  array[5] = Pretending by Eric Clapton(283),
  array[6] = Bad Love by Eric Clapton(308),
  array[7] = Everybody's In The Mood by Howlin' Wolf(178),
  array[9] = Samson and Delilah by Reverend Gary Davis(216),
  array[10] = Twelve Sticks by Reverend Gary Davis(194),
  array[11] = Hot Cha by Roy Buchanan(208),
  array[12] = Green Onions by Roy Buchanan(443),
  array[13] = I'm Just a Prisoner by Janiva Magness(230),
  array[15] = Hobo Blues by John Lee Hooker(187),
  array[16] = I Can't Quit You Baby by John Lee Hooker(182),
  array[78] = I Blew Up The United States by Was (Not Was)(230)

 Algorithm Elapsed Time: 16.9438 seconds.

 Integer Run -----------------------------
 Target time: 180
 Sublist -----------------------------
  sum : 179
  array[0] = 20,    array[1] = 12,    array[3] = 15,    array[4] = 25,
  array[5] = 19,    array[6] = 29,    array[7] = 18,    array[8] = 11,
  array[9] = 13,    array[10] = 17
 Program ended with exit code: 0

 iTunes Run -----------------------------
 Target time: 2700
 Sublist -----------------------------
  sum : 2700
  array[0] = Cowboy Casanova by Carrie Underwood(236),
  array[1] = Quitter by Carrie Underwood(220),
  array[2] = Russian Roulette by Rihanna(228),
  array[3] = All My Life by Foo Fighters(263),
  array[4] = Monkey Wrench by Foo Fighters(230),
  array[6] = Bad Love by Eric Clapton(308),
  array[7] = Everybody's In The Mood by Howlin' Wolf(178),
  array[8] = Well That's All Right by Howlin' Wolf(175),
  array[10] = Twelve Sticks by Reverend Gary Davis(194),
  array[11] = Hot Cha by Roy Buchanan(208),
  array[13] = I'm Just a Prisoner by Janiva Magness(230),
  array[78] = I Blew Up The United States by Was (Not Was)(230)

 Algorithm Elapsed Time: 1.37229 seconds.

 Integer Run -----------------------------
 Target time: 160
 Sublist -----------------------------
  sum : 160
  array[0] = 20,    array[2] = 22,    array[3] = 15,    array[4] = 25,
  array[5] = 19,    array[6] = 29,    array[9] = 13,    array[10] = 17
 Program ended with exit code: 0

 iTunes Run -----------------------------
 Target time: 999
 Sublist -----------------------------
  sum : 999
  array[5] = Pretending by Eric Clapton(283),
  array[6] = Bad Love by Eric Clapton(308),
  array[7] = Everybody's In The Mood by Howlin' Wolf(178),
  array[78] = I Blew Up The United States by Was (Not Was)(230)

 Algorithm Elapsed Time: 0.037008 seconds.

 Integer Run -----------------------------
 Target time: 99
 Sublist -----------------------------
  sum : 99
  array[0] = 20,    array[2] = 22,    array[3] = 15,    array[4] = 25,
  array[10] = 17
 Program ended with exit code: 0

 iTunes Run -----------------------------
 Target time: 1000000
 TUNES_TARGET is larger than masterSum.
 Program ended with exit code: 1

 */
