/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 2/18/2020
Instructor: Eric Reed
File Name: assignment6.cpp

Program Description: This program will implement find() using ideas presented
in the course modules.  The class template, FHhashQPwFind, will be derived from
the base class, FHhashQP.  It will take a second type parameter, KeyType, as
seen in the modules.  The public method, const Object find(const KeyType & key)
is added in the program, and it returns the found object, or throws a
NotFoundException if it is not there (NotFoundException is added to the class).
The protected methods, int myHashKey(const KeyType & key) const, a modification
to myHash() which uses the key rather than the object to hash and
int findPosKey(const KeyType & key) const, a modification to findPos() which
uses the key than the object to get a position, are added to the program.
The program is tested on EBookEntry data by reading the data from the
catalog-short4.txt file, then adding each book to a hash table.  The program
also generates 25 random integers to use as special indices.  It displays 25
from the original vector followed by 25 find() calls, which report success or
failure.  It also tests find() on two or three keys that are not in the hash
table.  Everything in the program is done twice, once using the int eTextNum as
a key field, and a second time using a string key field like title or creator.
The accessors or mutators of EBookEntry helps with process.  One main instead
of two is provided with one set of key choices left in and the other commented
out.  From the new derived FHhashQPwithFind class methods, base class instance
members are referred to using the this->syntax, base class static constants
are referred to using full class qualifiers, and the typename key is always
used and is fully qualified in front of the declaration of any base class
nested template type.
*/

#include <iostream>
#include <vector>
#include "EBookEntry.h"
using namespace std;

#define NUM_RANDOM_INDICES 25

// prototyping of Hash functions and FHhashQPwFind include
int Hash(int key);
int Hash(const string & key);
int Hash(const EBookEntry & item);

#include "FHhashQPwFind.h"

// prototyping of getKey functions
int getKey(const EBookEntry & item);
//string getKey(const EBookEntry & item);

void displayOneEBook(EBookEntry book);

int main()
{
   EBookEntry book;
   vector<int> randomIndices;

   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   // FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   // read data from files
   EBookEntryReader bookInput("catalog-short4.txt");

   // test whether read was successful
   if (bookInput.readError())
   {
      cout << "couldn't open " << bookInput.getFileName() << " for input.\n";
      exit(1);
   }

   // we want two books to be identical in different ways:  ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   // EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl;

   // generate random indices
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      randomIndices.push_back( rand() % bookInput.getNumBooks() );
   }

   // insert all books into hash table
   for (int k = 0; k < bookInput.getNumBooks(); k++)
   {
       hashTable.insert(bookInput[k]);
   }

   // attempt to find on the selected key
   cout << "The same random books from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         book = hashTable.find(bookInput[ randomIndices[k] ].getETextNum() );
         // book = hashTable.find(bookInput [randomIndices[k] ].getCreator() );

         displayOneEBook(book);
      }
      catch (...)
      {
         cout << "not found.  ";
      }
      cout << endl;
   }

   // test known failures exceptions:
   try
   {
      book = hashTable.find(-3);
      // book = hashTable.find( "Jack Kerouac" );

      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "not found.  ";
   }

   // more failures
   try
   {
      book = hashTable.find(-1);

      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "not found.  ";
   }

   try
   {
      book = hashTable.find(107);

      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "not found.  ";
   }
}

// hasing function implementations
int Hash(int key)
{
   return key;
}

int Hash(const string & key)
{
   unsigned int k, retVal = 0;

   for (k = 0; k < key.length(); k++)
   {
      retVal = 37 * retVal + key[k];
   }

   return retVal;
}

int Hash(const EBookEntry & item)
{
   return Hash(item.getETextNum());
   // return Hash(item.getCreator());
}


// used for ID equality
int getKey(const EBookEntry & item)
{
   return item.getETextNum();
}

/*
// used for author equality
string getKey( const EBookEntry & item )
{
return item.getCreator() ;
}
*/

void displayOneEBook(EBookEntry book)
{
   cout << "   # " << book.getETextNum() << "  ---------------" << endl;
   cout << "   \"" << book.getTitle() << "\"" << endl;
   cout << "   by " << book.getCreator() << endl;
   cout << "   re: " << book.getSubject() << endl << endl;
}

/*
 Output:

 550
 The same random books from the hash table
 # 29420 ---------------
 "American Rural Highways"
 by Agg, T. R. (Thomas Radford), 1878-1947
 re: Roads -- United States


 # 29165 ---------------
 "The American Missionary — Volume 38, No. 01, January, 1884"
 by Various
 re: Congregational churches -- Missions -- Periodicals


 # 28476 ---------------
 Antiquaries, Genealogists, etc" for Literary Men, Artists,
 by Various
 re: Questions and answers -- Periodicals


 # 27041 ---------------
 "L'art roman dans le Sud-Manche"
 by Lebert, Marie
 re: London (England) -- History -- To 1500


 # 363 ---------------
 "The Oakdale Affair"
 by Burroughs, Edgar Rice, 1875-1950
 re: Fiction


 # 6640 ---------------
 "Märchen-Almanach auf das Jahr 1828"
 by Hauff, Wilhelm, 1802-1827
 re: Fairy tales -- Germany


 # 30094 ---------------
 The Great Race at Riverport School"
 by Chapman, Allen
 re: Marathon running -- Juvenile fiction


 # 16811 ---------------
 or, Kamilaroi Sayings (1856)"
 by Ridley, William, 1819-1878
 re: Kamilaroi language -- Terms and phrases


 # 26598 ---------------
 "Seasoning of Wood"
 by Wagner, J. B. (Joseph Bernard), 1870-
 re: Lumber -- Drying


 # 29932 ---------------
 "The Harbor"
 by Poole, Ernest, 1880-1950
 re: Fiction


 # 28757 ---------------
 "Divided Skates"
 by Raymond, Evelyn, 1843-1910
 re: Orphans -- Juvenile fiction


 # 15561 ---------------
 "The Boer in Peace and War"
 by Mann, Arthur M.
 re: Cook, James, 1728-1779


 # 26705 ---------------
 "The Caravan Route between Egypt and Syria"
 by Ludwig Salvator, Archduke of Austria, 1847-1915
 re: Palestine -- Description and travel


 # 25254 ---------------
 "Notes on Islam"
 by Hussain, Ahmed, Sir, 1863-
 re: Islam


 # 25202 ---------------
 "Bu Hong Lou Meng"
 by Langhuanshanqiao, 18th/19th cent.
 re: PL


 # 28394 ---------------
 "William Penn"
 by Hodges, George, 1856-1919
 re: Penn, William, 1644-1718


 # 29971 ---------------
 Being Meditations on the Book of Ecclesiastes"
 by Jennings, Frederick Charles, 1847-1948
 re: Bible. O.T. Ecclesiastes -- Meditations


 # 15533 ---------------
 "The Present Picture of New South Wales (1811)"
 by Mann, David Dickinson
 re: Feminist fiction


 # 6366 ---------------
 "The Principles of Aesthetics"
 by Parker, Dewitt H.
 re: Folklore


 # 30094 ---------------
 The Great Race at Riverport School"
 by Chapman, Allen
 re: Marathon running -- Juvenile fiction


 # 25833 ---------------
 "The Great Controversy Between Christ and Satan"
 by White, Ellen Gould Harmon, 1827-1915
 re: Seventh-Day Adventists -- Doctrines


 # 11024 ---------------
 Of de koffiveilingen der Nederlandsche Handelsmaatschappy"
 by Multatuli, 1820-1887
 re: Boyle, Robert, 1627-1691


 # 25761 ---------------
 "St. Bernard of Clairvaux's Life of St. Malachy of Armagh"
 by Bernard, of Clairvaux, Saint, 1091?-1153
 re: Malachy, Saint, 1094?-1148


 # 26245 ---------------
 "The History of the Peloponnesian War"
 by Thucydides, 455? BC-395 BC
 re: Greece -- History -- Peloponnesian War, 431-404 B.C.


 # 24959 ---------------
 "Working With the Working Woman"
 by Parker, Cornelia Stratton, 1885-
 re: United States -- Social conditions


 not found. not found. not found.

 550
 The same random books from the hash table
 # 29420 ---------------
 "American Rural Highways"
 by Agg, T. R. (Thomas Radford), 1878-1947
 re: Roads -- United States


 # 29165 ---------------
 "The American Missionary — Volume 38, No. 01, January, 1884"
 by Various
 re: Congregational churches -- Missions -- Periodicals


 # 28476 ---------------
 Antiquaries, Genealogists, etc" for Literary Men, Artists,
 by Various
 re: Questions and answers -- Periodicals


 # 27041 ---------------
 "L'art roman dans le Sud-Manche"
 by Lebert, Marie
 re: London (England) -- History -- To 1500


 # 363 ---------------
 "The Oakdale Affair"
 by Burroughs, Edgar Rice, 1875-1950
 re: Fiction


 # 6640 ---------------
 "Märchen-Almanach auf das Jahr 1828"
 by Hauff, Wilhelm, 1802-1827
 re: Fairy tales -- Germany


 # 30094 ---------------
 The Great Race at Riverport School"
 by Chapman, Allen
 re: Marathon running -- Juvenile fiction


 # 16811 ---------------
 or, Kamilaroi Sayings (1856)"
 by Ridley, William, 1819-1878
 re: Kamilaroi language -- Terms and phrases


 # 26598 ---------------
 "Seasoning of Wood"
 by Wagner, J. B. (Joseph Bernard), 1870-
 re: Lumber -- Drying


 # 29932 ---------------
 "The Harbor"
 by Poole, Ernest, 1880-1950
 re: Fiction


 # 28757 ---------------
 "Divided Skates"
 by Raymond, Evelyn, 1843-1910
 re: Orphans -- Juvenile fiction


 # 15561 ---------------
 "The Boer in Peace and War"
 by Mann, Arthur M.
 re: Cook, James, 1728-1779


 # 26705 ---------------
 "The Caravan Route between Egypt and Syria"
 by Ludwig Salvator, Archduke of Austria, 1847-1915
 re: Palestine -- Description and travel


 # 25254 ---------------
 "Notes on Islam"
 by Hussain, Ahmed, Sir, 1863-
 re: Islam


 # 25202 ---------------
 "Bu Hong Lou Meng"
 by Langhuanshanqiao, 18th/19th cent.
 re: PL


 # 28394 ---------------
 "William Penn"
 by Hodges, George, 1856-1919
 re: Penn, William, 1644-1718


 # 29971 ---------------
 Being Meditations on the Book of Ecclesiastes"
 by Jennings, Frederick Charles, 1847-1948
 re: Bible. O.T. Ecclesiastes -- Meditations


 # 15533 ---------------
 "The Present Picture of New South Wales (1811)"
 by Mann, David Dickinson
 re: Feminist fiction


 # 6366 ---------------
 "The Principles of Aesthetics"
 by Parker, Dewitt H.
 re: Folklore


 # 30094 ---------------
 The Great Race at Riverport School"
 by Chapman, Allen
 re: Marathon running -- Juvenile fiction


 # 25833 ---------------
 "The Great Controversy Between Christ and Satan"
 by White, Ellen Gould Harmon, 1827-1915
 re: Seventh-Day Adventists -- Doctrines


 # 11024 ---------------
 Of de koffiveilingen der Nederlandsche Handelsmaatschappy"
 by Multatuli, 1820-1887
 re: Boyle, Robert, 1627-1691


 # 25761 ---------------
 "St. Bernard of Clairvaux's Life of St. Malachy of Armagh"
 by Bernard, of Clairvaux, Saint, 1091?-1153
 re: Malachy, Saint, 1094?-1148


 # 26245 ---------------
 "The History of the Peloponnesian War"
 by Thucydides, 455? BC-395 BC
 re: Greece -- History -- Peloponnesian War, 431-404 B.C.


 # 24959 ---------------
 "Working With the Working Woman"
 by Parker, Cornelia Stratton, 1885-
 re: United States -- Social conditions


 not found. not found. not found.

 */
