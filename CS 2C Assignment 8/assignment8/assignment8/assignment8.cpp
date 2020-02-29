/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 3/3/2020
Instructor: Eric Reed
File Name: assignment8.cpp

Program Description: This program sees a version of quickSort, quickSortX(),
that takes, as a second parameter, int recLimit, a recursion limit.  It allows
for any positive int 2 or higher.  FHsort.h allows for use of the existing
mySwapFH() and median3() functions written there.  The quickSortX() templates
are written above main() so they can be seen along with the client in a single
file.  Recursion limits are seen from 2 to 300 in steps of 2: 2, 4, 6, 8 ...
They are run on different array sizes from 40000 to 240000.  Their results are
summarized in a table below main().  The results will be commented on,
describing the range that seems to be minimal (flat).
*/

#include <iostream>
#include <ctime> // used to time the algorithms
#include <climits> // used for INT_MAX
#include "FHvector.h"
#include "FHsort.h" // used for insertionSort(), mySwapFH(), and median3()
using namespace std;

#define ARRAY_SIZE 40000

// quickSortX() public driver
template <typename Comparable>
bool quickSortX(FHvector<Comparable> & a, int recLimit)
{
   if (recLimit < 2)
   {
      return false;
   }

   quickSortX(a, 0, a.size() - 1, recLimit);
   return true;
}

// quickSortX() inner function
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int recLimit)
{
   Comparable pivot;
   int i, j;

   if (left + recLimit <= right)
   {
      pivot = median3(a, left, right);
      for (i = left, j = right - 1;;)
      {
         while (a[++i] < pivot)
         {
            ;
         }
         while (pivot < a[--j])
         {
            ;
         }
         if (i < j)
         {
            mySwapFH(a[i], a[j]);
         }
         else
         {
            break;
         }
      }

      mySwapFH(a[i], a[right - 1]); // restore pivot

      // recursive calls on smaller sub-groups
      quickSortX(a, left, i - 1, recLimit);
      quickSortX(a, i + 1, right, recLimit);
   }
   else
   {
      // non-recursive escape value - insertionSort
      insertionSort(a, left, right);
   }
}

int main()
{
   int k, recLimit;
   int arrayOfInts[ARRAY_SIZE];
   FHvector<int> fhVectorOfInts;
   clock_t startTime, stopTime;

   // fill an array with random values
   for (k = 0; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand() % INT_MAX;
   }

   cout << "quickSorts called on ARRAY_SIZE " << ARRAY_SIZE
      << "\n\nElapsed Times for Recursion Limits of Size" << endl;

   for (recLimit = 2; recLimit <= 300; recLimit += 2)
   {
      // clear fhVectorOfInts and fill with random values from arrayOfInts
      fhVectorOfInts.clear();
      for (k = 0; k < ARRAY_SIZE; k++)
      {
         fhVectorOfInts.push_back(arrayOfInts[k]);
      }

      startTime = clock(); // ------------------ start

      quickSortX(fhVectorOfInts, recLimit); // time this

      stopTime = clock(); // ---------------------- stop
      cout << "(" << recLimit << "): "
         << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
         << " seconds." << endl;
   }

   cout << endl << endl;

   // statement that shows how quickSortX() was correctly written
   for (k = 0; k < ARRAY_SIZE; k += ARRAY_SIZE / 5)
   {
      cout << "randomized array #" << k << ": " << arrayOfInts[k] << ", ";
      cout << "quickSortX #" << k << ": " << fhVectorOfInts[k] << endl;
   }

   return 0;
}

/*
 Output:

 ARRAY_SIZE 40000
   recLimit Size    |   quickSort Time (seconds)
 -----------------------------------------------
    2 - 40          |      0.008 - 0.010
    42 - 68         |      0.010 - 0.014
    70 - 138        |      0.014 - 0.019
    140 - 210       |      0.020 - 0.025
    212 - 242       |      0.027 - 0.030
    244 - 290       |      0.030 - 0.034
    290 - 300       |      0.035 - 0.036

 quickSorts called on ARRAY_SIZE 40000

 Elapsed Times for Recursion Limits of Size
 (2): 0.009806 seconds.
 (4): 0.009978 seconds.
 (6): 0.009675 seconds.
 (8): 0.008945 seconds.
 (10): 0.008598 seconds.
 (12): 0.008193 seconds.
 (14): 0.008763 seconds.
 (16): 0.008972 seconds.
 (18): 0.008922 seconds.
 (20): 0.008334 seconds.
 (22): 0.008834 seconds.
 (24): 0.009162 seconds.
 (26): 0.010421 seconds.
 (28): 0.010244 seconds.
 (30): 0.008852 seconds.
 (32): 0.008933 seconds.
 (34): 0.009209 seconds.
 (36): 0.008998 seconds.
 (38): 0.009452 seconds.
 (40): 0.009952 seconds.
 (42): 0.010317 seconds.
 (44): 0.010432 seconds.
 (46): 0.010012 seconds.
 (48): 0.009912 seconds.
 (50): 0.010006 seconds.
 (52): 0.012442 seconds.
 (54): 0.011687 seconds.
 (56): 0.010972 seconds.
 (58): 0.013371 seconds.
 (60): 0.013254 seconds.
 (62): 0.010821 seconds.
 (64): 0.013896 seconds.
 (66): 0.014812 seconds.
 (68): 0.014489 seconds.
 (70): 0.01628 seconds.
 (72): 0.012262 seconds.
 (74): 0.011616 seconds.
 (76): 0.011706 seconds.
 (78): 0.01491 seconds.
 (80): 0.013798 seconds.
 (82): 0.014078 seconds.
 (84): 0.014577 seconds.
 (86): 0.012759 seconds.
 (88): 0.012765 seconds.
 (90): 0.013803 seconds.
 (92): 0.017915 seconds.
 (94): 0.016296 seconds.
 (96): 0.014092 seconds.
 (98): 0.014094 seconds.
 (100): 0.017646 seconds.
 (102): 0.014608 seconds.
 (104): 0.016376 seconds.
 (106): 0.015453 seconds.
 (108): 0.018309 seconds.
 (110): 0.014764 seconds.
 (112): 0.017414 seconds.
 (114): 0.017998 seconds.
 (116): 0.015499 seconds.
 (118): 0.015509 seconds.
 (120): 0.018783 seconds.
 (122): 0.018366 seconds.
 (124): 0.017432 seconds.
 (126): 0.019101 seconds.
 (128): 0.016602 seconds.
 (130): 0.018628 seconds.
 (132): 0.017457 seconds.
 (134): 0.0185 seconds.
 (136): 0.019131 seconds.
 (138): 0.018075 seconds.
 (140): 0.020524 seconds.
 (142): 0.017225 seconds.
 (144): 0.018005 seconds.
 (146): 0.018723 seconds.
 (148): 0.022811 seconds.
 (150): 0.019962 seconds.
 (152): 0.018445 seconds.
 (154): 0.020912 seconds.
 (156): 0.020082 seconds.
 (158): 0.022001 seconds.
 (160): 0.018874 seconds.
 (162): 0.023039 seconds.
 (164): 0.020128 seconds.
 (166): 0.02362 seconds.
 (168): 0.022227 seconds.
 (170): 0.020526 seconds.
 (172): 0.020482 seconds.
 (174): 0.022256 seconds.
 (176): 0.022424 seconds.
 (178): 0.021313 seconds.
 (180): 0.019648 seconds.
 (182): 0.022192 seconds.
 (184): 0.023139 seconds.
 (186): 0.020352 seconds.
 (188): 0.025332 seconds.
 (190): 0.023708 seconds.
 (192): 0.02226 seconds.
 (194): 0.023916 seconds.
 (196): 0.025669 seconds.
 (198): 0.024134 seconds.
 (200): 0.025097 seconds.
 (202): 0.025369 seconds.
 (204): 0.021453 seconds.
 (206): 0.025688 seconds.
 (208): 0.024098 seconds.
 (210): 0.022848 seconds.
 (212): 0.027272 seconds.
 (214): 0.028927 seconds.
 (216): 0.027003 seconds.
 (218): 0.025988 seconds.
 (220): 0.026078 seconds.
 (222): 0.025287 seconds.
 (224): 0.023288 seconds.
 (226): 0.026462 seconds.
 (228): 0.028169 seconds.
 (230): 0.025672 seconds.
 (232): 0.024382 seconds.
 (234): 0.027738 seconds.
 (236): 0.024626 seconds.
 (238): 0.027385 seconds.
 (240): 0.029085 seconds.
 (242): 0.028171 seconds.
 (244): 0.0306 seconds.
 (246): 0.027381 seconds.
 (248): 0.025521 seconds.
 (250): 0.032181 seconds.
 (252): 0.027151 seconds.
 (254): 0.028788 seconds.
 (256): 0.027998 seconds.
 (258): 0.030426 seconds.
 (260): 0.030381 seconds.
 (262): 0.027963 seconds.
 (264): 0.030124 seconds.
 (266): 0.033003 seconds.
 (268): 0.031886 seconds.
 (270): 0.030341 seconds.
 (272): 0.029511 seconds.
 (274): 0.029841 seconds.
 (276): 0.031199 seconds.
 (278): 0.031108 seconds.
 (280): 0.032416 seconds.
 (282): 0.034386 seconds.
 (284): 0.032435 seconds.
 (286): 0.034284 seconds.
 (288): 0.030867 seconds.
 (290): 0.035631 seconds.
 (292): 0.036894 seconds.
 (294): 0.036701 seconds.
 (296): 0.035404 seconds.
 (298): 0.033663 seconds.
 (300): 0.034585 seconds.


 randomized array #0: 16807, quickSortX #0: 8383
 randomized array #8000: 950756779, quickSortX #8000: 428531668
 randomized array #16000: 1506928713, quickSortX #16000: 860751224
 randomized array #24000: 912580311, quickSortX #24000: 1284038916
 randomized array #32000: 711851266, quickSortX #32000: 1713567634
 Program ended with exit code: 0

 ARRAY_SIZE 80000
   recLimit Size    |   quickSort Time (seconds)
 -----------------------------------------------
    2 - 34          |      0.016 - 0.022
    34 - 70         |      0.022 - 0.025
    72 - 92         |      0.025 - 0.029
    94 - 126        |      0.030 - 0.035
    128 - 148       |      0.035 - 0.039
    150 - 156       |      0.039 - 0.042
    158 - 202       |      0.042 - 0.049
    204 - 214       |      0.049 - 0.055
    216 - 276       |      0.055 - 0.064
    280 - 300       |      0.065 - 0.068

 quickSorts called on ARRAY_SIZE 80000

 Elapsed Times for Recursion Limits of Size
 (2): 0.022412 seconds.
 (4): 0.018995 seconds.
 (6): 0.017464 seconds.
 (8): 0.018195 seconds.
 (10): 0.016796 seconds.
 (12): 0.01777 seconds.
 (14): 0.017674 seconds.
 (16): 0.017078 seconds.
 (18): 0.016876 seconds.
 (20): 0.018897 seconds.
 (22): 0.021177 seconds.
 (24): 0.018415 seconds.
 (26): 0.021348 seconds.
 (28): 0.020906 seconds.
 (30): 0.019519 seconds.
 (32): 0.020155 seconds.
 (34): 0.022047 seconds.
 (36): 0.025733 seconds.
 (38): 0.020917 seconds.
 (40): 0.021027 seconds.
 (42): 0.020581 seconds.
 (44): 0.023007 seconds.
 (46): 0.021809 seconds.
 (48): 0.022352 seconds.
 (50): 0.021711 seconds.
 (52): 0.025038 seconds.
 (54): 0.022789 seconds.
 (56): 0.023072 seconds.
 (58): 0.023479 seconds.
 (60): 0.023257 seconds.
 (62): 0.025109 seconds.
 (64): 0.024462 seconds.
 (66): 0.023722 seconds.
 (68): 0.023978 seconds.
 (70): 0.025907 seconds.
 (72): 0.028353 seconds.
 (74): 0.026971 seconds.
 (76): 0.027644 seconds.
 (78): 0.029471 seconds.
 (80): 0.027785 seconds.
 (82): 0.026416 seconds.
 (84): 0.026333 seconds.
 (86): 0.027405 seconds.
 (88): 0.027636 seconds.
 (90): 0.028475 seconds.
 (92): 0.028956 seconds.
 (94): 0.031153 seconds.
 (96): 0.030796 seconds.
 (98): 0.031378 seconds.
 (100): 0.029553 seconds.
 (102): 0.031106 seconds.
 (104): 0.034197 seconds.
 (106): 0.031741 seconds.
 (108): 0.031434 seconds.
 (110): 0.035083 seconds.
 (112): 0.03345 seconds.
 (114): 0.034175 seconds.
 (116): 0.035237 seconds.
 (118): 0.032603 seconds.
 (120): 0.032662 seconds.
 (122): 0.033653 seconds.
 (124): 0.033633 seconds.
 (126): 0.0358 seconds.
 (128): 0.038942 seconds.
 (130): 0.036116 seconds.
 (132): 0.036067 seconds.
 (134): 0.035405 seconds.
 (136): 0.038459 seconds.
 (138): 0.034777 seconds.
 (140): 0.039091 seconds.
 (142): 0.03753 seconds.
 (144): 0.034577 seconds.
 (146): 0.037056 seconds.
 (148): 0.03912 seconds.
 (150): 0.042473 seconds.
 (152): 0.039884 seconds.
 (154): 0.038402 seconds.
 (156): 0.038476 seconds.
 (158): 0.043099 seconds.
 (160): 0.043421 seconds.
 (162): 0.043831 seconds.
 (164): 0.044223 seconds.
 (166): 0.044417 seconds.
 (168): 0.046436 seconds.
 (170): 0.04671 seconds.
 (172): 0.04473 seconds.
 (174): 0.044496 seconds.
 (176): 0.047465 seconds.
 (178): 0.044707 seconds.
 (180): 0.042155 seconds.
 (182): 0.045846 seconds.
 (184): 0.044419 seconds.
 (186): 0.042569 seconds.
 (188): 0.048605 seconds.
 (190): 0.046641 seconds.
 (192): 0.047873 seconds.
 (194): 0.047678 seconds.
 (196): 0.04845 seconds.
 (198): 0.048944 seconds.
 (200): 0.049311 seconds.
 (202): 0.049874 seconds.
 (204): 0.051127 seconds.
 (206): 0.051926 seconds.
 (208): 0.053211 seconds.
 (210): 0.05544 seconds.
 (212): 0.05325 seconds.
 (214): 0.049472 seconds.
 (216): 0.056538 seconds.
 (218): 0.058133 seconds.
 (220): 0.055525 seconds.
 (222): 0.057086 seconds.
 (224): 0.058129 seconds.
 (226): 0.056011 seconds.
 (228): 0.055446 seconds.
 (230): 0.057145 seconds.
 (232): 0.058791 seconds.
 (234): 0.052231 seconds.
 (236): 0.062307 seconds.
 (238): 0.054037 seconds.
 (240): 0.057708 seconds.
 (242): 0.0547 seconds.
 (244): 0.061426 seconds.
 (246): 0.056776 seconds.
 (248): 0.063679 seconds.
 (250): 0.052279 seconds.
 (252): 0.062824 seconds.
 (254): 0.063143 seconds.
 (256): 0.057584 seconds.
 (258): 0.064017 seconds.
 (260): 0.064911 seconds.
 (262): 0.057988 seconds.
 (264): 0.058213 seconds.
 (266): 0.058133 seconds.
 (268): 0.059542 seconds.
 (270): 0.058354 seconds.
 (272): 0.061792 seconds.
 (274): 0.063551 seconds.
 (276): 0.061727 seconds.
 (278): 0.065525 seconds.
 (280): 0.065097 seconds.
 (282): 0.063646 seconds.
 (284): 0.068477 seconds.
 (286): 0.065498 seconds.
 (288): 0.064252 seconds.
 (290): 0.068479 seconds.
 (292): 0.064673 seconds.
 (294): 0.064322 seconds.
 (296): 0.068889 seconds.
 (298): 0.064372 seconds.
 (300): 0.067886 seconds.


 randomized array #0: 16807, quickSortX #0: 8383
 randomized array #16000: 1506928713, quickSortX #16000: 430617059
 randomized array #32000: 711851266, quickSortX #32000: 865296529
 randomized array #48000: 1583402100, quickSortX #48000: 1285869684
 randomized array #64000: 664200686, quickSortX #64000: 1717496369
 Program ended with exit code: 0

 ARRAY_SIZE 120000
   recLimit Size    |   quickSort Time (seconds)
 -----------------------------------------------
    2 - 38          |      0.025 - 0.032
    40 - 58         |      0.034 - 0.037
    60 - 72         |      0.036 - 0.040
    74 - 90         |      0.040 - 0.046
    92 - 106        |      0.043 - 0.048
    108 - 122       |      0.049 - 0.056
    124 - 152       |      0.051 - 0.064
    154 - 178       |      0.059 - 0.069
    180 - 200       |      0.065 - 0.073
    202 - 222       |      0.070 - 0.079
    224 - 234       |      0.075 - 0.081
    236 - 256       |      0.077 - 0.086
    258 - 280       |      0.087 - 0.093
    282 - 300       |      0.090 - 0.098

 quickSorts called on ARRAY_SIZE 120000

 Elapsed Times for Recursion Limits of Size
 (2): 0.032439 seconds.
 (4): 0.028342 seconds.
 (6): 0.028558 seconds.
 (8): 0.026548 seconds.
 (10): 0.025991 seconds.
 (12): 0.029578 seconds.
 (14): 0.028606 seconds.
 (16): 0.026975 seconds.
 (18): 0.025989 seconds.
 (20): 0.029383 seconds.
 (22): 0.027863 seconds.
 (24): 0.026725 seconds.
 (26): 0.030325 seconds.
 (28): 0.032131 seconds.
 (30): 0.031475 seconds.
 (32): 0.031758 seconds.
 (34): 0.03042 seconds.
 (36): 0.032349 seconds.
 (38): 0.031222 seconds.
 (40): 0.036129 seconds.
 (42): 0.034071 seconds.
 (44): 0.034946 seconds.
 (46): 0.033391 seconds.
 (48): 0.031353 seconds.
 (50): 0.037563 seconds.
 (52): 0.034939 seconds.
 (54): 0.036293 seconds.
 (56): 0.034192 seconds.
 (58): 0.035679 seconds.
 (60): 0.040208 seconds.
 (62): 0.038408 seconds.
 (64): 0.037362 seconds.
 (66): 0.037394 seconds.
 (68): 0.036591 seconds.
 (70): 0.04091 seconds.
 (72): 0.040873 seconds.
 (74): 0.046466 seconds.
 (76): 0.040445 seconds.
 (78): 0.04566 seconds.
 (80): 0.042513 seconds.
 (82): 0.044668 seconds.
 (84): 0.040718 seconds.
 (86): 0.045756 seconds.
 (88): 0.042137 seconds.
 (90): 0.045048 seconds.
 (92): 0.04742 seconds.
 (94): 0.047172 seconds.
 (96): 0.047273 seconds.
 (98): 0.048003 seconds.
 (100): 0.043987 seconds.
 (102): 0.044447 seconds.
 (104): 0.04805 seconds.
 (106): 0.044856 seconds.
 (108): 0.050533 seconds.
 (110): 0.049027 seconds.
 (112): 0.052085 seconds.
 (114): 0.050731 seconds.
 (116): 0.05389 seconds.
 (118): 0.050705 seconds.
 (120): 0.050585 seconds.
 (122): 0.056131 seconds.
 (124): 0.051548 seconds.
 (126): 0.061029 seconds.
 (128): 0.052512 seconds.
 (130): 0.057542 seconds.
 (132): 0.054854 seconds.
 (134): 0.056842 seconds.
 (136): 0.055855 seconds.
 (138): 0.056864 seconds.
 (140): 0.057339 seconds.
 (142): 0.064105 seconds.
 (144): 0.056858 seconds.
 (146): 0.057472 seconds.
 (148): 0.055383 seconds.
 (150): 0.059979 seconds.
 (152): 0.057762 seconds.
 (154): 0.065391 seconds.
 (156): 0.061386 seconds.
 (158): 0.065065 seconds.
 (160): 0.064956 seconds.
 (162): 0.059316 seconds.
 (164): 0.060491 seconds.
 (166): 0.063261 seconds.
 (168): 0.065721 seconds.
 (170): 0.067161 seconds.
 (172): 0.063691 seconds.
 (174): 0.068506 seconds.
 (176): 0.069019 seconds.
 (178): 0.067108 seconds.
 (180): 0.073268 seconds.
 (182): 0.06725 seconds.
 (184): 0.074084 seconds.
 (186): 0.066518 seconds.
 (188): 0.071636 seconds.
 (190): 0.067988 seconds.
 (192): 0.073487 seconds.
 (194): 0.065964 seconds.
 (196): 0.07018 seconds.
 (198): 0.070798 seconds.
 (200): 0.07352 seconds.
 (202): 0.079165 seconds.
 (204): 0.07361 seconds.
 (206): 0.074292 seconds.
 (208): 0.070363 seconds.
 (210): 0.077506 seconds.
 (212): 0.074826 seconds.
 (214): 0.073041 seconds.
 (216): 0.075794 seconds.
 (218): 0.075337 seconds.
 (220): 0.077074 seconds.
 (222): 0.07761 seconds.
 (224): 0.081036 seconds.
 (226): 0.075095 seconds.
 (228): 0.078855 seconds.
 (230): 0.081801 seconds.
 (232): 0.076741 seconds.
 (234): 0.081498 seconds.
 (236): 0.083228 seconds.
 (238): 0.077906 seconds.
 (240): 0.083334 seconds.
 (242): 0.083612 seconds.
 (244): 0.083699 seconds.
 (246): 0.084438 seconds.
 (248): 0.082763 seconds.
 (250): 0.081469 seconds.
 (252): 0.086695 seconds.
 (254): 0.084445 seconds.
 (256): 0.083165 seconds.
 (258): 0.090428 seconds.
 (260): 0.088202 seconds.
 (262): 0.092166 seconds.
 (264): 0.092498 seconds.
 (266): 0.087226 seconds.
 (268): 0.08919 seconds.
 (270): 0.090416 seconds.
 (272): 0.090361 seconds.
 (274): 0.09159 seconds.
 (276): 0.093453 seconds.
 (278): 0.089078 seconds.
 (280): 0.093176 seconds.
 (282): 0.098665 seconds.
 (284): 0.097222 seconds.
 (286): 0.098256 seconds.
 (288): 0.090476 seconds.
 (290): 0.09672 seconds.
 (292): 0.095659 seconds.
 (294): 0.09524 seconds.
 (296): 0.098494 seconds.
 (298): 0.098884 seconds.
 (300): 0.092849 seconds.


 randomized array #0: 16807, quickSortX #0: 8383
 randomized array #24000: 912580311, quickSortX #24000: 429399441
 randomized array #48000: 1583402100, quickSortX #48000: 863696507
 randomized array #72000: 1144897517, quickSortX #72000: 1286744999
 randomized array #96000: 1750092994, quickSortX #96000: 1718131606
 Program ended with exit code: 0

 ARRAY_SIZE 160000
   recLimit Size    |   quickSort Time (seconds)
 -----------------------------------------------
    2 - 22          |      0.037 - 0.041
    24 - 58         |      0.039 - 0.051
    60 - 78         |      0.051 - 0.057
    80 - 106        |      0.054 - 0.065
    108 - 120       |      0.061 - 0.071
    122 - 142       |      0.067 - 0.080
    144 - 168       |      0.074 - 0.088
    170 - 202       |      0.085 - 0.097
    204 - 222       |      0.100 - 0.107
    224 - 246       |      0.107 - 0.114
    248 - 282       |      0.110 - 0.129
    284 - 300       |      0.126 - 0.140

 quickSorts called on ARRAY_SIZE 160000

 Elapsed Times for Recursion Limits of Size
 (2): 0.03779 seconds.
 (4): 0.03773 seconds.
 (6): 0.0379 seconds.
 (8): 0.04045 seconds.
 (10): 0.037696 seconds.
 (12): 0.03795 seconds.
 (14): 0.036977 seconds.
 (16): 0.038308 seconds.
 (18): 0.041934 seconds.
 (20): 0.039747 seconds.
 (22): 0.039078 seconds.
 (24): 0.047304 seconds.
 (26): 0.041452 seconds.
 (28): 0.040274 seconds.
 (30): 0.038645 seconds.
 (32): 0.042102 seconds.
 (34): 0.046157 seconds.
 (36): 0.042655 seconds.
 (38): 0.043249 seconds.
 (40): 0.044163 seconds.
 (42): 0.043052 seconds.
 (44): 0.04818 seconds.
 (46): 0.051054 seconds.
 (48): 0.048812 seconds.
 (50): 0.043917 seconds.
 (52): 0.047618 seconds.
 (54): 0.045126 seconds.
 (56): 0.048818 seconds.
 (58): 0.049181 seconds.
 (60): 0.053368 seconds.
 (62): 0.053486 seconds.
 (64): 0.052289 seconds.
 (66): 0.051371 seconds.
 (68): 0.051736 seconds.
 (70): 0.053302 seconds.
 (72): 0.057362 seconds.
 (74): 0.049783 seconds.
 (76): 0.056875 seconds.
 (78): 0.053231 seconds.
 (80): 0.063221 seconds.
 (82): 0.054774 seconds.
 (84): 0.055393 seconds.
 (86): 0.055514 seconds.
 (88): 0.059762 seconds.
 (90): 0.060852 seconds.
 (92): 0.06131 seconds.
 (94): 0.062476 seconds.
 (96): 0.065381 seconds.
 (98): 0.059435 seconds.
 (100): 0.064523 seconds.
 (102): 0.063467 seconds.
 (104): 0.063726 seconds.
 (106): 0.062813 seconds.
 (108): 0.068177 seconds.
 (110): 0.061393 seconds.
 (112): 0.069162 seconds.
 (114): 0.067178 seconds.
 (116): 0.069715 seconds.
 (118): 0.071634 seconds.
 (120): 0.068082 seconds.
 (122): 0.07614 seconds.
 (124): 0.067114 seconds.
 (126): 0.07433 seconds.
 (128): 0.080877 seconds.
 (130): 0.071911 seconds.
 (132): 0.074517 seconds.
 (134): 0.074921 seconds.
 (136): 0.072625 seconds.
 (138): 0.079301 seconds.
 (140): 0.077587 seconds.
 (142): 0.076956 seconds.
 (144): 0.086279 seconds.
 (146): 0.082048 seconds.
 (148): 0.074761 seconds.
 (150): 0.076738 seconds.
 (152): 0.081269 seconds.
 (154): 0.083427 seconds.
 (156): 0.082959 seconds.
 (158): 0.080291 seconds.
 (160): 0.084484 seconds.
 (162): 0.079358 seconds.
 (164): 0.088176 seconds.
 (166): 0.086571 seconds.
 (168): 0.085897 seconds.
 (170): 0.090414 seconds.
 (172): 0.090886 seconds.
 (174): 0.085823 seconds.
 (176): 0.093451 seconds.
 (178): 0.090684 seconds.
 (180): 0.092917 seconds.
 (182): 0.089122 seconds.
 (184): 0.09541 seconds.
 (186): 0.090657 seconds.
 (188): 0.093408 seconds.
 (190): 0.090563 seconds.
 (192): 0.092272 seconds.
 (194): 0.08957 seconds.
 (196): 0.096575 seconds.
 (198): 0.096451 seconds.
 (200): 0.09733 seconds.
 (202): 0.091976 seconds.
 (204): 0.104572 seconds.
 (206): 0.100316 seconds.
 (208): 0.104388 seconds.
 (210): 0.098559 seconds.
 (212): 0.104183 seconds.
 (214): 0.107699 seconds.
 (216): 0.100716 seconds.
 (218): 0.107954 seconds.
 (220): 0.099932 seconds.
 (222): 0.10634 seconds.
 (224): 0.110243 seconds.
 (226): 0.109056 seconds.
 (228): 0.107397 seconds.
 (230): 0.114732 seconds.
 (232): 0.10774 seconds.
 (234): 0.113346 seconds.
 (236): 0.113978 seconds.
 (238): 0.109675 seconds.
 (240): 0.112262 seconds.
 (242): 0.112865 seconds.
 (244): 0.114594 seconds.
 (246): 0.11141 seconds.
 (248): 0.120666 seconds.
 (250): 0.119774 seconds.
 (252): 0.110638 seconds.
 (254): 0.118345 seconds.
 (256): 0.110873 seconds.
 (258): 0.116433 seconds.
 (260): 0.121516 seconds.
 (262): 0.122871 seconds.
 (264): 0.122515 seconds.
 (266): 0.127413 seconds.
 (268): 0.119575 seconds.
 (270): 0.124738 seconds.
 (272): 0.120272 seconds.
 (274): 0.122494 seconds.
 (276): 0.123992 seconds.
 (278): 0.124438 seconds.
 (280): 0.129186 seconds.
 (282): 0.127942 seconds.
 (284): 0.131299 seconds.
 (286): 0.130642 seconds.
 (288): 0.12698 seconds.
 (290): 0.128384 seconds.
 (292): 0.12961 seconds.
 (294): 0.140866 seconds.
 (296): 0.133249 seconds.
 (298): 0.132004 seconds.
 (300): 0.132277 seconds.


 randomized array #0: 16807, quickSortX #0: 8383
 randomized array #32000: 711851266, quickSortX #32000: 428717089
 randomized array #64000: 664200686, quickSortX #64000: 862095726
 randomized array #96000: 1750092994, quickSortX #96000: 1286134495
 randomized array #128000: 1795038995, quickSortX #128000: 1718424616
 Program ended with exit code: 0

 ARRAY_SIZE 200000
   recLimit Size    |   quickSort Time (seconds)
 -----------------------------------------------
    2 - 42          |      0.043 - 0.057
    44 - 70         |      0.057 - 0.068
    72 - 96         |      0.067 - 0.078
    98 - 128        |      0.080 - 0.090
    130 - 142       |      0.091 - 0.099
    144 - 162       |      0.099 - 0.110
    164 - 192       |      0.103 - 0.119
    194 - 234       |      0.115 - 0.138
    236 - 272       |      0.139 - 0.154
    274 - 300       |      0.154 - 0.170

 quickSorts called on ARRAY_SIZE 200000

 Elapsed Times for Recursion Limits of Size
 (2): 0.049841 seconds.
 (4): 0.048753 seconds.
 (6): 0.053621 seconds.
 (8): 0.043858 seconds.
 (10): 0.047335 seconds.
 (12): 0.049684 seconds.
 (14): 0.048788 seconds.
 (16): 0.047376 seconds.
 (18): 0.050467 seconds.
 (20): 0.047283 seconds.
 (22): 0.050373 seconds.
 (24): 0.048449 seconds.
 (26): 0.050177 seconds.
 (28): 0.051865 seconds.
 (30): 0.056508 seconds.
 (32): 0.05206 seconds.
 (34): 0.053172 seconds.
 (36): 0.055775 seconds.
 (38): 0.057048 seconds.
 (40): 0.056765 seconds.
 (42): 0.056721 seconds.
 (44): 0.059266 seconds.
 (46): 0.063801 seconds.
 (48): 0.057385 seconds.
 (50): 0.060133 seconds.
 (52): 0.062517 seconds.
 (54): 0.06387 seconds.
 (56): 0.062576 seconds.
 (58): 0.065879 seconds.
 (60): 0.064617 seconds.
 (62): 0.063899 seconds.
 (64): 0.063047 seconds.
 (66): 0.067983 seconds.
 (68): 0.068381 seconds.
 (70): 0.068411 seconds.
 (72): 0.07207 seconds.
 (74): 0.067084 seconds.
 (76): 0.070075 seconds.
 (78): 0.07413 seconds.
 (80): 0.074686 seconds.
 (82): 0.071543 seconds.
 (84): 0.070458 seconds.
 (86): 0.07816 seconds.
 (88): 0.073897 seconds.
 (90): 0.071155 seconds.
 (92): 0.078201 seconds.
 (94): 0.077909 seconds.
 (96): 0.076538 seconds.
 (98): 0.083214 seconds.
 (100): 0.080651 seconds.
 (102): 0.080978 seconds.
 (104): 0.081253 seconds.
 (106): 0.082592 seconds.
 (108): 0.085428 seconds.
 (110): 0.085797 seconds.
 (112): 0.083463 seconds.
 (114): 0.089256 seconds.
 (116): 0.088071 seconds.
 (118): 0.090752 seconds.
 (120): 0.084956 seconds.
 (122): 0.084938 seconds.
 (124): 0.088463 seconds.
 (126): 0.088412 seconds.
 (128): 0.089023 seconds.
 (130): 0.099527 seconds.
 (132): 0.092898 seconds.
 (134): 0.093893 seconds.
 (136): 0.091853 seconds.
 (138): 0.094099 seconds.
 (140): 0.09411 seconds.
 (142): 0.096413 seconds.
 (144): 0.100638 seconds.
 (146): 0.099433 seconds.
 (148): 0.102451 seconds.
 (150): 0.103197 seconds.
 (152): 0.110252 seconds.
 (154): 0.108323 seconds.
 (156): 0.098725 seconds.
 (158): 0.107384 seconds.
 (160): 0.106933 seconds.
 (162): 0.105791 seconds.
 (164): 0.114356 seconds.
 (166): 0.112667 seconds.
 (168): 0.103427 seconds.
 (170): 0.106914 seconds.
 (172): 0.113769 seconds.
 (174): 0.114792 seconds.
 (176): 0.106998 seconds.
 (178): 0.115259 seconds.
 (180): 0.117034 seconds.
 (182): 0.118734 seconds.
 (184): 0.116338 seconds.
 (186): 0.119224 seconds.
 (188): 0.119302 seconds.
 (190): 0.112964 seconds.
 (192): 0.113484 seconds.
 (194): 0.1204 seconds.
 (196): 0.115641 seconds.
 (198): 0.12408 seconds.
 (200): 0.119082 seconds.
 (202): 0.126164 seconds.
 (204): 0.137948 seconds.
 (206): 0.123607 seconds.
 (208): 0.125426 seconds.
 (210): 0.129181 seconds.
 (212): 0.126655 seconds.
 (214): 0.128301 seconds.
 (216): 0.132856 seconds.
 (218): 0.13031 seconds.
 (220): 0.132567 seconds.
 (222): 0.12511 seconds.
 (224): 0.130553 seconds.
 (226): 0.137108 seconds.
 (228): 0.138957 seconds.
 (230): 0.137597 seconds.
 (232): 0.137466 seconds.
 (234): 0.137442 seconds.
 (236): 0.142692 seconds.
 (238): 0.14093 seconds.
 (240): 0.142488 seconds.
 (242): 0.139936 seconds.
 (244): 0.147607 seconds.
 (246): 0.149267 seconds.
 (248): 0.149749 seconds.
 (250): 0.143386 seconds.
 (252): 0.143129 seconds.
 (254): 0.15213 seconds.
 (256): 0.154268 seconds.
 (258): 0.147289 seconds.
 (260): 0.152877 seconds.
 (262): 0.152323 seconds.
 (264): 0.146112 seconds.
 (266): 0.146589 seconds.
 (268): 0.153776 seconds.
 (270): 0.151948 seconds.
 (272): 0.14985 seconds.
 (274): 0.15787 seconds.
 (276): 0.15537 seconds.
 (278): 0.15427 seconds.
 (280): 0.155393 seconds.
 (282): 0.166834 seconds.
 (284): 0.16465 seconds.
 (286): 0.16077 seconds.
 (288): 0.160911 seconds.
 (290): 0.166415 seconds.
 (292): 0.164108 seconds.
 (294): 0.16333 seconds.
 (296): 0.163208 seconds.
 (298): 0.166776 seconds.
 (300): 0.170281 seconds.


 randomized array #0: 16807, quickSortX #0: 8383
 randomized array #40000: 1209564112, quickSortX #40000: 428559331
 randomized array #80000: 1174518407, quickSortX #80000: 862254142
 randomized array #120000: 396178790, quickSortX #120000: 1288182217
 randomized array #160000: 41006454, quickSortX #160000: 1719392336
 Program ended with exit code: 0

 ARRAY_SIZE 240000
   recLimit Size    |   quickSort Time (seconds)
 -----------------------------------------------
    2 - 18          |      0.054 - 0.061
    20 - 50         |      0.062 - 0.071
    52 - 80         |      0.073 - 0.084
    82 - 104        |      0.086 - 0.099
    106 - 130       |      0.100 - 0.111
    132 - 176       |      0.112 - 0.136
    178 - 200       |      0.139 - 0.149
    202 - 228       |      0.148 - 0.159
    230 - 260       |      0.161 - 0.177
    262 - 276       |      0.179 - 0.186
    278 - 290       |      0.188 - 0.199
    290 - 300       |      0.194 - 0.206

 quickSorts called on ARRAY_SIZE 240000

 Elapsed Times for Recursion Limits of Size
 (2): 0.061205 seconds.
 (4): 0.054151 seconds.
 (6): 0.057824 seconds.
 (8): 0.05862 seconds.
 (10): 0.061485 seconds.
 (12): 0.059854 seconds.
 (14): 0.059155 seconds.
 (16): 0.059208 seconds.
 (18): 0.058077 seconds.
 (20): 0.062323 seconds.
 (22): 0.064 seconds.
 (24): 0.06652 seconds.
 (26): 0.063433 seconds.
 (28): 0.064259 seconds.
 (30): 0.064005 seconds.
 (32): 0.065333 seconds.
 (34): 0.07021 seconds.
 (36): 0.068802 seconds.
 (38): 0.064011 seconds.
 (40): 0.070011 seconds.
 (42): 0.07185 seconds.
 (44): 0.071828 seconds.
 (46): 0.068435 seconds.
 (48): 0.070534 seconds.
 (50): 0.07094 seconds.
 (52): 0.076771 seconds.
 (54): 0.073826 seconds.
 (56): 0.077582 seconds.
 (58): 0.075605 seconds.
 (60): 0.073387 seconds.
 (62): 0.082396 seconds.
 (64): 0.07618 seconds.
 (66): 0.081359 seconds.
 (68): 0.082992 seconds.
 (70): 0.082198 seconds.
 (72): 0.084494 seconds.
 (74): 0.084606 seconds.
 (76): 0.081966 seconds.
 (78): 0.082996 seconds.
 (80): 0.08479 seconds.
 (82): 0.086504 seconds.
 (84): 0.086475 seconds.
 (86): 0.096888 seconds.
 (88): 0.093801 seconds.
 (90): 0.088892 seconds.
 (92): 0.09161 seconds.
 (94): 0.094523 seconds.
 (96): 0.0888 seconds.
 (98): 0.09868 seconds.
 (100): 0.099609 seconds.
 (102): 0.093698 seconds.
 (104): 0.097291 seconds.
 (106): 0.100176 seconds.
 (108): 0.10449 seconds.
 (110): 0.103415 seconds.
 (112): 0.106021 seconds.
 (114): 0.105754 seconds.
 (116): 0.107341 seconds.
 (118): 0.101815 seconds.
 (120): 0.103673 seconds.
 (122): 0.111374 seconds.
 (124): 0.10962 seconds.
 (126): 0.106764 seconds.
 (128): 0.110858 seconds.
 (130): 0.10864 seconds.
 (132): 0.114097 seconds.
 (134): 0.113683 seconds.
 (136): 0.116477 seconds.
 (138): 0.116394 seconds.
 (140): 0.12239 seconds.
 (142): 0.112133 seconds.
 (144): 0.128956 seconds.
 (146): 0.121519 seconds.
 (148): 0.126468 seconds.
 (150): 0.129608 seconds.
 (152): 0.119242 seconds.
 (154): 0.125303 seconds.
 (156): 0.126184 seconds.
 (158): 0.136441 seconds.
 (160): 0.123447 seconds.
 (162): 0.13103 seconds.
 (164): 0.121848 seconds.
 (166): 0.132362 seconds.
 (168): 0.13029 seconds.
 (170): 0.13441 seconds.
 (172): 0.132311 seconds.
 (174): 0.134894 seconds.
 (176): 0.135788 seconds.
 (178): 0.144435 seconds.
 (180): 0.13949 seconds.
 (182): 0.14708 seconds.
 (184): 0.146527 seconds.
 (186): 0.141779 seconds.
 (188): 0.144224 seconds.
 (190): 0.144693 seconds.
 (192): 0.138967 seconds.
 (194): 0.14758 seconds.
 (196): 0.147171 seconds.
 (198): 0.149156 seconds.
 (200): 0.149166 seconds.
 (202): 0.151695 seconds.
 (204): 0.151652 seconds.
 (206): 0.148802 seconds.
 (208): 0.154177 seconds.
 (210): 0.15702 seconds.
 (212): 0.159021 seconds.
 (214): 0.149529 seconds.
 (216): 0.154085 seconds.
 (218): 0.155509 seconds.
 (220): 0.155815 seconds.
 (222): 0.158767 seconds.
 (224): 0.151038 seconds.
 (226): 0.158932 seconds.
 (228): 0.157591 seconds.
 (230): 0.161131 seconds.
 (232): 0.17058 seconds.
 (234): 0.164047 seconds.
 (236): 0.159589 seconds.
 (238): 0.174373 seconds.
 (240): 0.174031 seconds.
 (242): 0.172003 seconds.
 (244): 0.175217 seconds.
 (246): 0.170312 seconds.
 (248): 0.175387 seconds.
 (250): 0.173579 seconds.
 (252): 0.171376 seconds.
 (254): 0.175684 seconds.
 (256): 0.175235 seconds.
 (258): 0.175254 seconds.
 (260): 0.177617 seconds.
 (262): 0.185414 seconds.
 (264): 0.179315 seconds.
 (266): 0.184426 seconds.
 (268): 0.186809 seconds.
 (270): 0.183201 seconds.
 (272): 0.17671 seconds.
 (274): 0.184311 seconds.
 (276): 0.186856 seconds.
 (278): 0.196335 seconds.
 (280): 0.190365 seconds.
 (282): 0.188903 seconds.
 (284): 0.194108 seconds.
 (286): 0.194411 seconds.
 (288): 0.195905 seconds.
 (290): 0.199238 seconds.
 (292): 0.205289 seconds.
 (294): 0.194945 seconds.
 (296): 0.202808 seconds.
 (298): 0.206371 seconds.
 (300): 0.199508 seconds.


 randomized array #0: 16807, quickSortX #0: 8383
 randomized array #48000: 1583402100, quickSortX #48000: 429443132
 randomized array #96000: 1750092994, quickSortX #96000: 860997468
 randomized array #144000: 1919811042, quickSortX #144000: 1287172927
 randomized array #192000: 955748568, quickSortX #192000: 1718728097
 Program ended with exit code: 0

 Results Comments:

 As described in the module 9A.1.4 A Good End To Recursion, a recursion limit
 size between 5 and 25 saw the fastest sorting times for quickSort().
 In the data above, recursion limit sizes roughly between 5 - 10 saw the
 fastest sorting times for smaller ARRAY_SIZE values and recursion limit sizes
 roughly between 10 - 25 saw the fastest sorting times for larger ARRAY_SIZE
 values.  However, to generalize the data in its entirety, the recursion
 limit sizes that saw the fastest sorting times were between 5 - 25, as noted
 in the module.

 Using the macro, INT_MAX, and the header, <climits>, allowed for the program
 to represent specific numbers and be directly assigned to its corresponding
 variable without typing out the entire number.  This was useful in specifying
 that an integer variable can't store any value larger than this limit.

 Overall, a range that seemed to be minimal agreed with the description in the
 module described above.  Sorting times increased at a relative faster rate
 for the larger ARRAY_SIZE values in the program and were visibly not minimal
 for larger recursion limit sizes.  Similarly, sorting times increased at a
 relative faster rate for the smaller ARRAY_SIZE values and were visibly not
 minimal for larger recursion limit sizes, although, not as pronounced as with
 larger ARRAY_SIZE values.  If someone were to need greater clarification on
 which ranges were minimal, the data produced in this program could be plotted
 in a graph to be seen as a greater visualization tool.

 */
