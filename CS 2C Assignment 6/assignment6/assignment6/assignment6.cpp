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
   EBookEntryReader bookInput("catalog-short-mac-1.txt");

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

 catalog-short-mac-1.txt
 4863
 The same random books from the hash table
    # 6633  ---------------
    "A Popular History of Ireland : from the Earliest Period to the
    Emancipation of the Catholics - Volume 2"
    by McGee, Thomas D'Arcy, 1825-1868
    re: Ireland -- History


    # 27682  ---------------
    "The Panchronicon"
    by MacKaye, Harold Steele, 1866-1928
    re: Science fiction


    # 27501  ---------------
    "McClure's Magazine, Vol. XXXI, No. 3, July 1908."
    by Various
    re: (no data found)


    # 29963  ---------------
    "Goodbye, Dead Man!"
    by Harris, Tom W.
    re: Science fiction


    # 3360  ---------------
    "Letters to His Son on the Art of Becoming a Man of the World and a
    Gentleman, 1766-71"
    by Chesterfield, Philip Dormer Stanhope, Earl of, 1694-1773
    re: Conduct of life


    # 27842  ---------------
    "The Economic Aspect of Geology"
    by Leith, C. K. (Charles Kenneth), 1875-1956
    re: Geology, Economic


    # 26702  ---------------
    "Studies in love and in terror"
    by Lowndes, Marie Belloc, 1868-1947
    re: Horror tales, English


    # 21182  ---------------
    "When We Two Parted"
    by Byron, George Gordon Byron, Baron, 1788-1824
    re: Poetry


    # 25610  ---------------
    "A Child's Garden of Verses"
    by Stevenson, Robert Louis, 1850-1894
    re: Children's poetry, English


    # 269  ---------------
    "Beasts and Super-Beasts"
    by Saki, 1870-1916
    re: Humorous stories


    # 5950  ---------------
    "The Fortunes of Nigel"
    by Scott, Walter, Sir, 1771-1832
    re: (no data found)


    # 10641  ---------------
    "Beacon Lights of History, Volume 10European Leaders"
    by Lord, John, 1810-1894
    re: (no data found)


    # 29683  ---------------
    "The Little Girl LostA Tale for Little Girls"
    by Raper, Eleanor
    re: Missing children -- Juvenile fiction


    # 25446  ---------------
    "Fernley House"
    by Richards, Laura Elizabeth Howe, 1850-1943
    re: PZ


    # 585  ---------------
    "Running a Thousand Miles for Freedom; or, the escape of William and
    Ellen Craft from slavery"
    by Craft, Ellen
    re: Fugitive slaves -- United States -- Biography


    # 26699  ---------------
    "The Woman and the Right to Vote"
    by Palma, Rafael, 1874-1939
    re: Women -- Suffrage -- Philippines


    # 29482  ---------------
    "Benjamin Franklin"
    by More, Paul Elmer, 1864-1937
    re: Franklin, Benjamin, 1706-1790


    # 3756  ---------------
    "Indiscretions of Archie"
    by Wodehouse, P. G. (Pelham Grenville), 1881-1975
    re: Humorous stories


    # 24751  ---------------
    "The Kitchen Cat and Other Stories"
    by Walton, Amy, 1848-1899
    re: Short stories


    # 28274  ---------------
    "The Beauties of Natureand the Wonders of the World We Live In"
    by Lubbock, John, Sir, 1834-1913
    re: Natural history


    # 28376  ---------------
    "The Wide, Wide World"
    by Warner, Susan, 1819-1885
    re: Christian life -- Fiction


    # 15266  ---------------
    "What Peace Means"
    by Van Dyke, Henry, 1852-1933
    re: Peace


    # 28301  ---------------
    "The Beloved Woman"
    by Norris, Kathleen Thompson, 1880-1966
    re: PS


    # 360  ---------------
    "What is Property?"
    by Proudhon, P.-J. (Pierre-Joseph), 1809-1865
    re: Law


    # 28771  ---------------
    "Child Maidelvoldand other ballads"
    by (no data found)
    re: PR


 not found.  not found.  not found.  Program ended with exit code: 0
 */
