/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 2/25/2020
Instructor: Eric Reed
File Name: assignment7.cpp

Program Description: This program includes a version of Shellsort, shellSortX(),
that takes, as input, a gap sequence.  To keep the overhead at a minimum, a raw
int array is used for the gap sequence.  Four gap sequences are investigated:
Shell's implied gap sequence, which is computed in shellSort1(); Shell's
explicit gap sequence in main(), which is passed explicitly to shellSortX();
Sedgewick's gap sequence, which uses the computational definition found in the
course's textbook and turns that definition into a sequence in the client using
loops and prints it out showing a good sequences, then using it in shellSortX();
and the best gap sequence that could be used is incorporated into the program.
Each gap sequence is run on six sizes of int arrays ranging from 10000 to
200000.  A table of the four sequences and six array sizes is created in the
program.  Questions regarding the program are proposed and answered at the
end of the main() file.
*/

#include <iostream>
#include <ctime> // for timing the algorithms
#include <cmath> // used to calculate gaps for pow() and ceil() functions
#include <cstdlib> // for the rand() function
#include "FHvector.h"
using namespace std;

#define ARRAY_SIZE 10000

// shellSort1() array for sorting Sedgewick's gap sequence
template <typename Comparable>
void shellSort1(Comparable array[], int arraySize)
{
   int k, pos, gap;
   Comparable tmp;

   for (gap = arraySize / 2; gap > 0; gap /= 2)
   {
      for (pos = gap; pos < arraySize; pos++)
      {
         tmp = array[pos];
         for (k = pos; k >= gap && tmp < array[k - gap]; k -= gap)
         {
            array[k] = array[k - gap];
         }
         array[k] = tmp;
      }
   }
}

// shellSort1() for using the shell's outer loop
template <typename Comparable>
void shellSort1(FHvector<Comparable> & a)
{
   int k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   // for statement for the outer gap loop
   for (gap = arraySize / 2; gap > 0; gap /= 2)
   {
      // for statement for the middle loop
      for (pos = gap; pos < arraySize; pos++)
      {
         tmp = a[pos];
         // for statement for the inner loop
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)
         {
            a[k] = a[k - gap];
         }
         a[k] = tmp;
      }
   }
}

// shellSortX() that takes an explicit gap sequence
template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, Comparable gapSequence[],
   int gapSeqSize)
{
   int i, k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   for (i = 0; gapSequence[i] <= arraySize / 2; i++)
   {
      gap = gapSequence[i];
   }

   // for statement for the outer gap loop
   for (gap; gap > 0; gap = gapSequence[--i])
   {
      // for statement for the middle loop
      for (pos = gap; pos < arraySize; pos++)
      {
         tmp = a[pos];
         // for statement for the inner loop
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)
         {
            a[k] = a[k - gap];
         }
         a[k] = tmp;
      }
   }
}

int main()
{
   int k, gapArraySize;
   int arrayOfInts[ARRAY_SIZE];
   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   FHvector<int> fhVectorOfInts3;
   FHvector<int> fhVectorOfInts4;

   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576};
   // computing Sedgewick's gap sequence
   int sedgewickArray[28];  // to be computed using formulas
   for (k = 0; k < 14; k++)
   {
      sedgewickArray[k] = 9 * (pow(4, k) - pow(2, k)) + 1;
   }
   for (k = 2; k < 16; k++)
   {
      sedgewickArray[k + 12] = pow(4, k) - 3 * (pow(2, k)) + 1;
   }

   // computing Tokuda's gap sequence
   int tokudaArray[26];
   for (k = 1; k < 27; k++)
   {
      tokudaArray[k - 1] = ceil((pow(9, k) - pow(4, k)) / (5 * pow(4, k - 1)));
   }

   cout << "Sedgewick's Gap Sequence:" << endl;
   gapArraySize = sizeof(sedgewickArray) / sizeof(*sedgewickArray);
   shellSort1(sedgewickArray, gapArraySize);
   for (k = 0; k < 28; k++)
   {
      cout << sedgewickArray[k] << endl;
   }
   cout << endl;

   cout << "Tokuda's Gap Sequence:" << endl;
   for (k = 0; k < 26; k++)
   {
      cout << tokudaArray[k] << endl;
   }
   cout << endl;

   // fill 4 vectors with identical random values so we can compare gaps
   for (k = 0; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand() % ARRAY_SIZE;
      fhVectorOfInts1.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
      fhVectorOfInts3.push_back(arrayOfInts[k]);
      fhVectorOfInts4.push_back(arrayOfInts[k]);
   }

   cout << "\nShell Sorts called on vectors of size " << ARRAY_SIZE << endl;

   // how to time algorithms
   clock_t startTime, stopTime;

   // implicit Shell gap sequence
   startTime = clock(); // ------------------ start

   shellSort1(fhVectorOfInts1); // time this

   stopTime = clock(); // ---------------------- stop
   cout << "\nImplied Shell Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // explicit Shell gap sequence
   gapArraySize = sizeof(gapArray) / sizeof(*gapArray);
   cout << "gap size: " << gapArraySize << endl;
   startTime = clock(); // ------------------ start

   shellSortX(fhVectorOfInts2, gapArray, gapArraySize); // time this

   stopTime = clock(); // ---------------------- stop
   cout << "Explicit Shell Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // Sedgewick's gap sequence
   gapArraySize = sizeof(sedgewickArray) / sizeof(*sedgewickArray);
   cout << "gap size: " << gapArraySize << endl;
   startTime = clock(); // ------------------ start

   shellSortX(fhVectorOfInts3, sedgewickArray, gapArraySize); // time this

   stopTime = clock(); // ---------------------- stop
   cout << "Sedgewick Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // Tokuda's gap sequence
   gapArraySize = sizeof(tokudaArray) / sizeof(*tokudaArray);
   cout << "gap size: " << gapArraySize << endl;
   startTime = clock(); // ------------------ start

   shellSortX(fhVectorOfInts4, tokudaArray, gapArraySize); // time this

   stopTime = clock(); // ---------------------- stop
   cout << "Tokuda Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // confirming that we got the correct results on all the arrays
   for (k = 0; k < ARRAY_SIZE; k += ARRAY_SIZE / 10)
   {
      cout << "implied shell gap #" << k << ": " << fhVectorOfInts1[k] << ", ";
      cout << "explicit shell gap #" << k << ": "
         << fhVectorOfInts2[k] << ",\n";
      cout << "Sedgewick gap #" << k << ": " << fhVectorOfInts3[k] << ", ";
      cout << "Tokuda gap #" << k << ": " << fhVectorOfInts4[k] << endl;
   }

   return 0;
}

/*
 Output:

 ARRAY_SIZE  |  Implied Gap   |  Explicit Gap  |  Sedgewick Gap  |  Tokuda Gap
 -----------------------------------------------------------------------------
    10000    |    0.0052 s    |    0.0127 s    |   0.0052 s      |   0.0039 s
    50000    |    0.0341 s    |    0.1142 s    |   0.0292 s      |   0.0290 s
    90000    |    0.0769 s    |    0.2851 s    |   0.0486 s      |   0.0449 s
    140000   |    0.1100 s    |    0.4006 s    |   0.0766 s      |   0.0831 s
    170000   |    0.1547 s    |    0.6531 s    |   0.1015 s      |   0.0952 s
    200000   |    0.1854 s    |    0.6985 s    |   0.1186 s      |   0.1225 s

 Why does Shell's gap sequence implied by shellSort1() give a different timing
 result than the explicit array described above and passed to shellSortX()?
 Which is faster and why?

 Shell's gap sequence implied by shellSort1() gives a different timing result
 than the explicit array passed to shellSortX() primarily due to how the sort
 compares odd and even ints.  When the array size is equal to a power of two,
 the sort does not compare odd and even elements until the final insertion loop.
 When the array size is not equal to a power of two, odd elements make sure
 that odd and even elements are compared before getting to the final insertion
 loop of gap size 1.  The main reason why implied and explicit gap values
 seen in the table above did not significantly deviate from one another
 (more than 1 second) is due to fact that vectors of sizes that were not equal
 to a power of two, were tested with random values.

 Shell's explicit gap sequence is composed of even elements that make
 comparisons for the worst case scenario, where the elements are mostly not
 sorted until the final insertion loop of gap size 1 (where the elements are
 finally sorted correctly).

 Sedgewick's gap sequence computation was found using the text and a Wikipedia
 Shellsort page.  Of the four gap sequences tested in this program, Tokuda's
 gap sequence gave the fastest and overall best results for the most part.
 As ARRAY_SIZE increased, there was a split between Sedgewick's gap sequence
 time result and Tokuda's time result.  Perhaps, this could have been a result
 of a random computing calculation.

 More along the lines of using other sources of text as well the same Wikipedia
 Shellsort page, I found that Tokuda's gap sequence and Ciura's gap sequence
 were shown to have the fastest and overall best results in addition to
 Sedgewick's gap sequence.  All three were essentially in the same time range,
 although they can differ depending on what computer is being used and how the
 algorithms are written.  Reading Ciura's 2001 paper, Ciura used 701 as the
 largest value in his sequence.  This value was difficult to use in this
 program because of the large ARRAY_SIZE values used in the program.  Results
 of Tokuda's gap sequence in this program were minutely faster than Sedgewick's
 gap sequence except for the few instances where ARRAY_SIZE increased.  Much to
 the explanation in the Wikipedia Shellsort page, Tokuda's gap sequence has use
 in practical applications.  Perhaps if I were to implement Ciura's gap
 sequence differently, I may have seen faster times and overall better results
 for Ciura's gap sequence compared to Tokuda's gap sequence.

 As a side note, I used int sedgewickArray[28] instead of int sedgewickArray[30]
 and k = 2 for the second for statement in that loop because it allowed for
 Sedgewick's gap sequence to have positive values rather than negative values,
 most likely a result of overflow.

 Shellsort results ranging from ARRAY_SIZE 10000 to 200000:

 Sedgewick's Gap Sequence:
 1
 5
 19
 41
 109
 209
 505
 929
 2161
 3905
 8929
 16001
 36289
 64769
 146305
 260609
 587521
 1045505
 2354689
 4188161
 9427969
 16764929
 37730305
 67084289
 150958081
 268386305
 603906049
 1073643521

 Tokuda's Gap Sequence:
 1
 4
 9
 20
 46
 103
 233
 525
 1182
 2660
 5985
 13467
 30301
 68178
 153401
 345152
 776591
 1747331
 3931496
 8845866
 19903198
 44782196
 100759940
 226709866
 510097200
 1147718700


 Shell Sorts called on vectors of size 10000

 Implied Shell Gap Elapsed Time: 0.005179 seconds.

 gap size: 21
 Explicit Shell Gap Elapsed Time: 0.012672 seconds.

 gap size: 28
 Sedgewick Gap Elapsed Time: 0.00523 seconds.

 gap size: 26
 Tokuda Gap Elapsed Time: 0.003868 seconds.

 implied shell gap #0: 0, explicit shell gap #0: 0,
 Sedgewick gap #0: 0, Tokuda gap #0: 0
 implied shell gap #1000: 963, explicit shell gap #1000: 963,
 Sedgewick gap #1000: 963, Tokuda gap #1000: 963
 implied shell gap #2000: 1990, explicit shell gap #2000: 1990,
 Sedgewick gap #2000: 1990, Tokuda gap #2000: 1990
 implied shell gap #3000: 3012, explicit shell gap #3000: 3012,
 Sedgewick gap #3000: 3012, Tokuda gap #3000: 3012
 implied shell gap #4000: 3998, explicit shell gap #4000: 3998,
 Sedgewick gap #4000: 3998, Tokuda gap #4000: 3998
 implied shell gap #5000: 4926, explicit shell gap #5000: 4926,
 Sedgewick gap #5000: 4926, Tokuda gap #5000: 4926
 implied shell gap #6000: 5950, explicit shell gap #6000: 5950,
 Sedgewick gap #6000: 5950, Tokuda gap #6000: 5950
 implied shell gap #7000: 6983, explicit shell gap #7000: 6983,
 Sedgewick gap #7000: 6983, Tokuda gap #7000: 6983
 implied shell gap #8000: 8007, explicit shell gap #8000: 8007,
 Sedgewick gap #8000: 8007, Tokuda gap #8000: 8007
 implied shell gap #9000: 9010, explicit shell gap #9000: 9010,
 Sedgewick gap #9000: 9010, Tokuda gap #9000: 9010
 Program ended with exit code: 0

 Sedgewick's Gap Sequence:
 1
 5
 19
 41
 109
 209
 505
 929
 2161
 3905
 8929
 16001
 36289
 64769
 146305
 260609
 587521
 1045505
 2354689
 4188161
 9427969
 16764929
 37730305
 67084289
 150958081
 268386305
 603906049
 1073643521

 Tokuda's Gap Sequence:
 1
 4
 9
 20
 46
 103
 233
 525
 1182
 2660
 5985
 13467
 30301
 68178
 153401
 345152
 776591
 1747331
 3931496
 8845866
 19903198
 44782196
 100759940
 226709866
 510097200
 1147718700


 Shell Sorts called on vectors of size 50000

 Implied Shell Gap Elapsed Time: 0.034093 seconds.

 gap size: 21
 Explicit Shell Gap Elapsed Time: 0.11416 seconds.

 gap size: 28
 Sedgewick Gap Elapsed Time: 0.029187 seconds.

 gap size: 26
 Tokuda Gap Elapsed Time: 0.029072 seconds.

 implied shell gap #0: 0, explicit shell gap #0: 0,
 Sedgewick gap #0: 0, Tokuda gap #0: 0
 implied shell gap #5000: 4977, explicit shell gap #5000: 4977,
 Sedgewick gap #5000: 4977, Tokuda gap #5000: 4977
 implied shell gap #10000: 9951, explicit shell gap #10000: 9951,
 Sedgewick gap #10000: 9951, Tokuda gap #10000: 9951
 implied shell gap #15000: 14909, explicit shell gap #15000: 14909,
 Sedgewick gap #15000: 14909, Tokuda gap #15000: 14909
 implied shell gap #20000: 19966, explicit shell gap #20000: 19966,
 Sedgewick gap #20000: 19966, Tokuda gap #20000: 19966
 implied shell gap #25000: 24981, explicit shell gap #25000: 24981,
 Sedgewick gap #25000: 24981, Tokuda gap #25000: 24981
 implied shell gap #30000: 29965, explicit shell gap #30000: 29965,
 Sedgewick gap #30000: 29965, Tokuda gap #30000: 29965
 implied shell gap #35000: 34984, explicit shell gap #35000: 34984,
 Sedgewick gap #35000: 34984, Tokuda gap #35000: 34984
 implied shell gap #40000: 39946, explicit shell gap #40000: 39946,
 Sedgewick gap #40000: 39946, Tokuda gap #40000: 39946
 implied shell gap #45000: 45027, explicit shell gap #45000: 45027,
 Sedgewick gap #45000: 45027, Tokuda gap #45000: 45027
 Program ended with exit code: 0

 Sedgewick's Gap Sequence:
 1
 5
 19
 41
 109
 209
 505
 929
 2161
 3905
 8929
 16001
 36289
 64769
 146305
 260609
 587521
 1045505
 2354689
 4188161
 9427969
 16764929
 37730305
 67084289
 150958081
 268386305
 603906049
 1073643521

 Tokuda's Gap Sequence:
 1
 4
 9
 20
 46
 103
 233
 525
 1182
 2660
 5985
 13467
 30301
 68178
 153401
 345152
 776591
 1747331
 3931496
 8845866
 19903198
 44782196
 100759940
 226709866
 510097200
 1147718700


 Shell Sorts called on vectors of size 90000

 Implied Shell Gap Elapsed Time: 0.076906 seconds.

 gap size: 21
 Explicit Shell Gap Elapsed Time: 0.285104 seconds.

 gap size: 28
 Sedgewick Gap Elapsed Time: 0.048585 seconds.

 gap size: 26
 Tokuda Gap Elapsed Time: 0.044912 seconds.

 implied shell gap #0: 0, explicit shell gap #0: 0,
 Sedgewick gap #0: 0, Tokuda gap #0: 0
 implied shell gap #9000: 9019, explicit shell gap #9000: 9019,
 Sedgewick gap #9000: 9019, Tokuda gap #9000: 9019
 implied shell gap #18000: 18094, explicit shell gap #18000: 18094,
 Sedgewick gap #18000: 18094, Tokuda gap #18000: 18094
 implied shell gap #27000: 26993, explicit shell gap #27000: 26993,
 Sedgewick gap #27000: 26993, Tokuda gap #27000: 26993
 implied shell gap #36000: 35807, explicit shell gap #36000: 35807,
 Sedgewick gap #36000: 35807, Tokuda gap #36000: 35807
 implied shell gap #45000: 44841, explicit shell gap #45000: 44841,
 Sedgewick gap #45000: 44841, Tokuda gap #45000: 44841
 implied shell gap #54000: 53781, explicit shell gap #54000: 53781,
 Sedgewick gap #54000: 53781, Tokuda gap #54000: 53781
 implied shell gap #63000: 62874, explicit shell gap #63000: 62874,
 Sedgewick gap #63000: 62874, Tokuda gap #63000: 62874
 implied shell gap #72000: 71881, explicit shell gap #72000: 71881,
 Sedgewick gap #72000: 71881, Tokuda gap #72000: 71881
 implied shell gap #81000: 80955, explicit shell gap #81000: 80955,
 Sedgewick gap #81000: 80955, Tokuda gap #81000: 80955
 Program ended with exit code: 0

 Sedgewick's Gap Sequence:
 1
 5
 19
 41
 109
 209
 505
 929
 2161
 3905
 8929
 16001
 36289
 64769
 146305
 260609
 587521
 1045505
 2354689
 4188161
 9427969
 16764929
 37730305
 67084289
 150958081
 268386305
 603906049
 1073643521

 Tokuda's Gap Sequence:
 1
 4
 9
 20
 46
 103
 233
 525
 1182
 2660
 5985
 13467
 30301
 68178
 153401
 345152
 776591
 1747331
 3931496
 8845866
 19903198
 44782196
 100759940
 226709866
 510097200
 1147718700


 Shell Sorts called on vectors of size 140000

 Implied Shell Gap Elapsed Time: 0.109966 seconds.

 gap size: 21
 Explicit Shell Gap Elapsed Time: 0.400571 seconds.

 gap size: 28
 Sedgewick Gap Elapsed Time: 0.076566 seconds.

 gap size: 26
 Tokuda Gap Elapsed Time: 0.083138 seconds.

 implied shell gap #0: 0, explicit shell gap #0: 0,
 Sedgewick gap #0: 0, Tokuda gap #0: 0
 implied shell gap #14000: 14009, explicit shell gap #14000: 14009,
 Sedgewick gap #14000: 14009, Tokuda gap #14000: 14009
 implied shell gap #28000: 28046, explicit shell gap #28000: 28046,
 Sedgewick gap #28000: 28046, Tokuda gap #28000: 28046
 implied shell gap #42000: 41936, explicit shell gap #42000: 41936,
 Sedgewick gap #42000: 41936, Tokuda gap #42000: 41936
 implied shell gap #56000: 56096, explicit shell gap #56000: 56096,
 Sedgewick gap #56000: 56096, Tokuda gap #56000: 56096
 implied shell gap #70000: 70291, explicit shell gap #70000: 70291,
 Sedgewick gap #70000: 70291, Tokuda gap #70000: 70291
 implied shell gap #84000: 84162, explicit shell gap #84000: 84162,
 Sedgewick gap #84000: 84162, Tokuda gap #84000: 84162
 implied shell gap #98000: 97846, explicit shell gap #98000: 97846,
 Sedgewick gap #98000: 97846, Tokuda gap #98000: 97846
 implied shell gap #112000: 111749, explicit shell gap #112000: 111749,
 Sedgewick gap #112000: 111749, Tokuda gap #112000: 111749
 implied shell gap #126000: 125653, explicit shell gap #126000: 125653,
 Sedgewick gap #126000: 125653, Tokuda gap #126000: 125653
 Program ended with exit code: 0

 Sedgewick's Gap Sequence:
 1
 5
 19
 41
 109
 209
 505
 929
 2161
 3905
 8929
 16001
 36289
 64769
 146305
 260609
 587521
 1045505
 2354689
 4188161
 9427969
 16764929
 37730305
 67084289
 150958081
 268386305
 603906049
 1073643521

 Tokuda's Gap Sequence:
 1
 4
 9
 20
 46
 103
 233
 525
 1182
 2660
 5985
 13467
 30301
 68178
 153401
 345152
 776591
 1747331
 3931496
 8845866
 19903198
 44782196
 100759940
 226709866
 510097200
 1147718700


 Shell Sorts called on vectors of size 170000

 Implied Shell Gap Elapsed Time: 0.154731 seconds.

 gap size: 21
 Explicit Shell Gap Elapsed Time: 0.653084 seconds.

 gap size: 28
 Sedgewick Gap Elapsed Time: 0.101491 seconds.

 gap size: 26
 Tokuda Gap Elapsed Time: 0.09522 seconds.

 implied shell gap #0: 0, explicit shell gap #0: 0,
 Sedgewick gap #0: 0, Tokuda gap #0: 0
 implied shell gap #17000: 17009, explicit shell gap #17000: 17009,
 Sedgewick gap #17000: 17009, Tokuda gap #17000: 17009
 implied shell gap #34000: 34165, explicit shell gap #34000: 34165,
 Sedgewick gap #34000: 34165, Tokuda gap #34000: 34165
 implied shell gap #51000: 51167, explicit shell gap #51000: 51167,
 Sedgewick gap #51000: 51167, Tokuda gap #51000: 51167
 implied shell gap #68000: 68117, explicit shell gap #68000: 68117,
 Sedgewick gap #68000: 68117, Tokuda gap #68000: 68117
 implied shell gap #85000: 84994, explicit shell gap #85000: 84994,
 Sedgewick gap #85000: 84994, Tokuda gap #85000: 84994
 implied shell gap #102000: 101969, explicit shell gap #102000: 101969,
 Sedgewick gap #102000: 101969, Tokuda gap #102000: 101969
 implied shell gap #119000: 118757, explicit shell gap #119000: 118757,
 Sedgewick gap #119000: 118757, Tokuda gap #119000: 118757
 implied shell gap #136000: 135924, explicit shell gap #136000: 135924,
 Sedgewick gap #136000: 135924, Tokuda gap #136000: 135924
 implied shell gap #153000: 152932, explicit shell gap #153000: 152932,
 Sedgewick gap #153000: 152932, Tokuda gap #153000: 152932
 Program ended with exit code: 0

 Sedgewick's Gap Sequence:
 1
 5
 19
 41
 109
 209
 505
 929
 2161
 3905
 8929
 16001
 36289
 64769
 146305
 260609
 587521
 1045505
 2354689
 4188161
 9427969
 16764929
 37730305
 67084289
 150958081
 268386305
 603906049
 1073643521

 Tokuda's Gap Sequence:
 1
 4
 9
 20
 46
 103
 233
 525
 1182
 2660
 5985
 13467
 30301
 68178
 153401
 345152
 776591
 1747331
 3931496
 8845866
 19903198
 44782196
 100759940
 226709866
 510097200
 1147718700


 Shell Sorts called on vectors of size 200000

 Implied Shell Gap Elapsed Time: 0.18542 seconds.

 gap size: 21
 Explicit Shell Gap Elapsed Time: 0.698482 seconds.

 gap size: 28
 Sedgewick Gap Elapsed Time: 0.118649 seconds.

 gap size: 26
 Tokuda Gap Elapsed Time: 0.122542 seconds.

 implied shell gap #0: 0, explicit shell gap #0: 0,
 Sedgewick gap #0: 0, Tokuda gap #0: 0
 implied shell gap #20000: 19958, explicit shell gap #20000: 19958,
 Sedgewick gap #20000: 19958, Tokuda gap #20000: 19958
 implied shell gap #40000: 39915, explicit shell gap #40000: 39915,
 Sedgewick gap #40000: 39915, Tokuda gap #40000: 39915
 implied shell gap #60000: 59902, explicit shell gap #60000: 59902,
 Sedgewick gap #60000: 59902, Tokuda gap #60000: 59902
 implied shell gap #80000: 79659, explicit shell gap #80000: 79659,
 Sedgewick gap #80000: 79659, Tokuda gap #80000: 79659
 implied shell gap #100000: 99793, explicit shell gap #100000: 99793,
 Sedgewick gap #100000: 99793, Tokuda gap #100000: 99793
 implied shell gap #120000: 119552, explicit shell gap #120000: 119552,
 Sedgewick gap #120000: 119552, Tokuda gap #120000: 119552
 implied shell gap #140000: 139576, explicit shell gap #140000: 139576,
 Sedgewick gap #140000: 139576, Tokuda gap #140000: 139576
 implied shell gap #160000: 159682, explicit shell gap #160000: 159682,
 Sedgewick gap #160000: 159682, Tokuda gap #160000: 159682
 implied shell gap #180000: 179761, explicit shell gap #180000: 179761,
 Sedgewick gap #180000: 179761, Tokuda gap #180000: 179761
 Program ended with exit code: 0

 */
