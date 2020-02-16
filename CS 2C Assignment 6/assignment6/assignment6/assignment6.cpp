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

 catalog-short4.txt
 550
 The same random books from the hash table
    # 27818  ---------------
    "Blackwood's Edinburgh Magazine, Volume 58, Number 358, August 1845"
    by Various
    re: AP


    # 28226  ---------------
    "The War in the Air; Vol. 1
 The Part played in the Great War by the Royal Air Force"
    by Raleigh, Walter Alexander, Sir, 1861-1922
    re: Great Britain. Royal Air Force


    # 25686  ---------------
    "The Iraq Study Group Report"
    by Iraq Study Group (U.S.)
    re: Iraq War, 2003-


    # 27133  ---------------
    "Histoire du Canada depuis sa découverte jusqu'à nos jours. Tome III"
    by Garneau, F.-X. (François-Xavier), 1809-1866
    re: Canada -- History -- To 1763 (New France)


    # 29487  ---------------
    "Forever"
    by Sheckley, Robert, 1928-2005
    re: Science fiction


    # 27623  ---------------
    "C'est la loi!"
    by Du Veuzit, Max, 1886-1952
    re: French drama -- 20th century


    # 352  ---------------
    "Buttered Side Down: Stories"
    by Ferber, Edna, 1885-1968
    re: Short stories


    # 25004  ---------------
    "A Confederate Girl's Diary"
    by Dawson, Sarah Morgan, 1842-1909
    re: Louisiana -- History -- Civil War, 1861-1865


    # 5701  ---------------
    "Sleepy-Time Tales: the Tale of Fatty Coon"
    by Bailey, Arthur Scott, 1877-1949
    re: United States -- History -- Civil War, 1861-1865 -- Personal narratives


    # 29604  ---------------
    "College Teaching
 Studies in Methods of Teaching in the College"
    by Klapper, Paul, 1885-1952
    re: Teaching


    # 25503  ---------------
    "Le Tour du Monde; Scandinavie
 Journal des voyages et des voyageurs; 2. sem. 1860"
    by Various
    re: Geography -- Pictorial works -- Periodicals


    # 28532  ---------------
    "Blackwood's Edinburgh Magazine, Volume 59, No. 363, January, 1846"
    by Various
    re: AP


    # 19188  ---------------
    "Poems"
    by Rossetti, Christina Georgina, 1830-1894
    re: Orléans, Philippe, duc d', 1674-1723 -- Fiction


    # 28065  ---------------
    "The Pecan and its Culture"
    by Hume, H. Harold (Hardrada Harold), 1875-1965
    re: Pecan


    # 26149  ---------------
    "Left Guard Gilbert"
    by Barbour, Ralph Henry, 1870-1944
    re: Football -- Juvenile fiction


    # 26552  ---------------
    "Fruits of Queensland"
    by Benson, Albert H.
    re: Fruit-culture -- Queensland


    # 29133  ---------------
    "Shipwreck in the Sky"
    by Binder, Eando
    re: Science fiction


    # 26847  ---------------
    "A Pessimist
 In Theory and Practice"
    by Bird, Frederic Mayer, 1838-1908
    re: PS


    # 29971  ---------------
    "Old Groans and New Songs
 Being Meditations on the Book of Ecclesiastes"
    by Jennings, Frederick Charles, 1847-1948
    re: Bible. O.T. Ecclesiastes -- Meditations


    # 27754  ---------------
    "The Flower Basket
 A Fairy Tale"
    by Unknown
    re: Fairy tales


    # 29030  ---------------
    "Wilson's Tales of the Borders and of Scotland, Volume VI"
    by Souvestre, Pierre, 1874-1914
    re: Scottish Borders (Scotland) -- Fiction


    # 25734  ---------------
    "Correspondance de Voltaire avec le roi de Prusse"
    by Voltaire, 1694-1778
    re: Frederick II, King of Prussia, 1712-1786 -- Correspondence


    # 27792  ---------------
    "The Arrow-Maker
 A Drama in Three Acts"
    by Austin, Mary Hunter, 1868-1934
    re: Indians of North America -- Drama


    # 25282  ---------------
    "Der Judenstaat. English"
    by Herzl, Theodor, 1860-1904
    re: Zionism


    # 25241  ---------------
    "Surpreza
 Entre-acto original"
    by Mascarenhas, Miguel J. T.
    re: Portuguese drama


 not found.  not found.  not found.  Program ended with exit code: 0
 */
