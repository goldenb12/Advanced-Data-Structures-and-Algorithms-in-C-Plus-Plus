/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 1/14/2020
Instructor: Eric Reed
File Name: assignment1B.cpp

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

// class Sublist definition
class Sublist
{
public:
   Sublist(vector<iTunesEntry> *orig = NULL)
      : sum(0), originalObjects (orig) { }
   Sublist addItem( int indexOfItemToAdd );
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<iTunesEntry> *originalObjects;
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
   const int TARGET = 3600;
   vector<iTunesEntry> dataSet;
   vector<Sublist> choices;
   int k, j, numSets, max, array_size, masterSum;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
         << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
   {
      dataSet.push_back(tunes_input[k]);
   }

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
      masterSum = masterSum + dataSet[i];
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

   // how we determine the time elapsed -------------------
   stopTime = clock();
   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   return 0;
}

/*
 Output:
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

 Algorithm Elapsed Time: 15.2868 seconds.

 Program ended with exit code: 0

 Target time: 500
 Sublist -----------------------------
  sum : 500
  array[19] = Ladies and Gentleman by The Rubyz(201),
  array[22] = Our Big Break by Veggie Tales(69),
  array[78] = I Blew Up The United States by Was (Not Was)(230)

 Algorithm Elapsed Time: 0.004821 seconds.

 Program ended with exit code: 0

 Target time: 1000
 Sublist -----------------------------
  sum : 1000
  array[4] = Monkey Wrench by Foo Fighters(230),
  array[7] = Everybody's In The Mood by Howlin' Wolf(178),
  array[8] = Well That's All Right by Howlin' Wolf(175),
  array[15] = Hobo Blues by John Lee Hooker(187),
  array[78] = I Blew Up The United States by Was (Not Was)(230)

 Algorithm Elapsed Time: 0.043535 seconds.

 Program ended with exit code: 0

 Target time: 100000
 TARGET is larger than masterSum.
 Program ended with exit code: 1

 */
