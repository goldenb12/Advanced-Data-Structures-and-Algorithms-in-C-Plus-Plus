/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 1/28/2020
Instructor: Eric Reed
File Name: assignment3A.cpp

Program Description: Creating a dynamic array implementation for large matrices,
where the "spine" of the matrix (vertical column along the left edge) is
comprised of a vector or an array of float pointers, each of which is
pointing to a different row.  Allocating such an array is possible because
it is one dimensional.  A full array of floats for each pointer to populate
a row is dynamically allocated in heap memory.  Each of these matrices that are
created are allocated in a loop, which makes rows to hold the floats (2-D
array).  A global scope method is created, which takes two input matrices and a
third return (reference) product matrix.  A fourth parameter is the size of the
matrices.  All matrices are square and of size M.  Before implementing this
matrix multiplication, the time complexity of this operation relative to M, is
determined.  A tight O() upper bound and a theta() estimate for mulitiplying
the two MxM matrices together is determined.  The matrix multiplication is
timed and generates a sparse matrix that is between 0.1% and 10% the size of
the non-zero matrix and then "square" the matrix using matrix multiplication.
A 15x15 square sub-portion of the matrix is first showed in the output, then
followed by the same portion of the squared matrix.  After timing the algorithm,
a series of questions are asked regarding the speed of the program.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define MAT_SIZE 101
typedef float* DynMat[MAT_SIZE];

// Matrix multiplication function to multiply matA and matB together
void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size);

// Displays a portion of the matrix
void matShowDyn(const DynMat & matA, int start, int size);

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;

   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      matDyn[r] = new float[MAT_SIZE];
      matDynAns[r] = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDyn[r][c] = 0;
         matDynAns[r][c] = 0;
      }
   }

   // generate small% non-default values between .1 and 1
   smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
   for (r = 0; r < smallPercent; r++)
   {
      srand(time(NULL));
      randRow = rand() % MAT_SIZE;
      randCol = rand() % MAT_SIZE;

      while (matDyn[randRow][randCol] != 0)
      {
         randRow = rand() % MAT_SIZE;
         randCol = rand() % MAT_SIZE;
      }
      matDyn[randRow][randCol] = double((rand() % 10) + 1) / 10;
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // clean up
   for (r = 0; r < MAT_SIZE; r++)
   {
      delete[] matDyn[r];
      delete[] matDynAns[r];
   }

   cout << endl;
}

void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size)
{
   double newVal;
   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         newVal = 0;
         for (int k = 0; k < size; k++)
         {
            newVal += matA[i][k] * matB[k][j];
         }
         matC[i][j] = newVal;
      }
   }
}

void matShowDyn(const DynMat & matA, int start, int size)
{
   cout << endl;
   for (int i = start; i < start + size; ++i)
   {
      for (int k = start; k < start + size; ++k)
      {
         cout << "  " << setw(2) << fixed << setprecision(2) << matA[i][k];
      }
      cout << endl;
   }
   cout << endl;
}

/*
 Output:
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.30  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.70  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.30  0.00  0.00  0.00  1.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.40  0.30  0.00  0.00  0.00  0.00  0.80  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.63
   0.09  0.00  0.00  0.00  0.30  0.00  0.00  0.00  0.00  0.00
   0.37  0.00  0.23  0.00  0.70  0.00  0.00  0.56  0.00  0.80
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.44  0.00  0.10  0.54  1.00  0.00  0.00  0.49  0.00  1.09
   0.00  0.00  0.17  0.00  0.33  0.00  0.00  0.00  0.00  0.30
   0.00  0.00  0.00  0.00  0.81  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.18  0.79  0.08  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.30  0.02  0.00  0.00  0.00  0.40  0.00  0.00  0.09


 Size = 101 Dyn Array Mult Elapsed Time: 0.01 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.80  0.00  0.00  0.00  0.70  0.00  0.00  0.00
   1.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  1.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.90  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.80  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.20  0.00  0.00  0.50  0.10  0.00


   0.00  0.00  0.00  0.72  0.00  0.45  0.40  1.91  0.00  0.00
   0.00  0.00  0.80  0.40  0.20  0.00  0.70  0.50  0.00  0.00
   0.84  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.04  0.30  0.00  0.32  0.00  0.00  0.00  0.00
   0.00  0.00  0.12  0.80  0.70  1.78  0.00  0.00  0.52  0.24
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.10  0.00  0.30
   0.00  0.00  0.00  0.00  0.00  0.80  0.00  0.49  0.00  0.00
   0.00  0.00  0.64  0.00  0.24  0.00  0.56  0.45  0.00  0.00
   0.07  0.00  0.00  0.20  0.14  0.00  0.60  0.00  0.49  0.48
   0.48  0.00  0.18  0.10  0.00  1.03  0.00  0.00  0.80  0.00


 Size = 202 Dyn Array Mult Elapsed Time: 0.04 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.50  0.00  0.10  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.80  0.00  0.00  0.00  0.70  0.00  0.00  0.90  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.90  0.00  0.00
   0.00  0.00  0.00  0.30  0.80  0.00  0.00  0.00  0.00  0.40
   0.00  0.00  0.10  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.70  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.60  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


   0.20  0.36  0.00  0.84  0.00  0.00  0.88  0.00  0.36  0.70
   0.07  0.04  0.00  0.24  0.80  0.00  0.00  0.63  0.00  0.25
   0.06  0.46  0.02  0.20  0.00  0.30  0.00  0.53  0.16  0.18
   0.00  0.52  0.00  0.00  0.00  0.00  0.00  0.44  0.20  0.00
   0.57  0.00  0.25  0.00  0.91  0.00  0.00  0.77  0.00  0.00
   0.00  0.10  0.09  0.00  0.00  0.56  0.42  0.44  0.00  0.18
   0.88  0.00  0.10  0.07  1.56  0.00  0.00  1.62  0.20  0.28
   1.48  0.00  0.80  0.00  0.62  0.41  0.00  0.84  0.79  1.02
   0.12  0.36  0.35  0.18  0.00  0.57  0.40  0.00  1.13  0.28
   0.19  0.00  0.00  0.00  0.00  0.02  0.00  0.06  0.00  0.10


 Size = 303 Dyn Array Mult Elapsed Time: 0.18 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.00  0.00  0.00  0.60  0.00  0.60  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.50  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  1.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.40  0.00
   0.00  0.00  0.00  0.00  0.40  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.70  0.00  0.00  0.00  0.00  0.00  0.00


   0.03  0.00  0.00  0.00  0.04  0.54  0.21  0.36  0.24  0.36
   0.00  0.20  0.00  0.48  0.35  0.48  0.45  0.32  0.25  0.00
   0.36  0.36  0.00  0.15  0.00  0.18  0.00  0.72  0.96  0.18
   0.00  0.00  0.30  0.09  0.36  0.49  0.00  0.00  0.00  0.00
   0.39  0.00  0.00  0.00  0.60  0.00  0.00  0.30  0.18  0.00
   0.36  0.36  0.70  0.20  0.00  0.00  0.00  0.44  0.18  1.22
   0.12  0.00  0.00  0.40  0.09  0.08  0.09  0.31  0.00  0.20
   0.00  0.99  0.00  0.00  0.24  0.27  0.42  0.46  0.00  0.32
   0.22  0.26  0.00  0.00  0.81  0.50  0.03  0.35  1.07  0.00
   0.18  0.00  0.51  0.00  0.30  0.00  0.00  0.14  0.10  1.00


 Size = 404 Dyn Array Mult Elapsed Time: 0.47 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.00  0.00  0.00  0.00  0.80  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  1.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.80  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


   0.00  0.00  0.56  0.67  1.48  0.15  0.94  0.10  1.24  0.78
   0.83  0.94  0.09  1.11  1.52  0.88  0.24  0.35  1.35  0.57
   2.06  0.92  0.04  1.44  1.21  0.10  0.06  0.33  0.67  0.35
   1.93  0.05  0.01  0.84  0.80  0.58  0.03  0.12  1.57  0.58
   0.50  0.54  0.10  1.13  1.66  1.01  0.20  1.26  1.49  0.00
   1.28  0.70  0.98  1.73  1.05  0.82  2.25  0.60  1.26  0.04
   0.00  1.06  0.45  0.30  1.12  2.61  0.48  1.49  1.89  0.00
   0.10  0.52  0.14  1.43  0.56  1.72  2.03  1.18  1.54  0.00
   0.34  0.00  0.66  0.87  1.62  0.66  1.61  0.00  2.33  1.51
   1.15  0.28  1.22  1.05  0.60  2.10  1.03  1.20  1.16  1.11


 Size = 1010 Dyn Array Mult Elapsed Time: 13.29 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.00  0.00  0.50  0.00  0.00  0.00  0.80  0.00
   0.00  0.00  0.00  0.00  0.50  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  1.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.90
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.30
   0.50  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


   2.01  3.06  5.70  1.53  1.05  5.38  0.00  1.61  2.58  0.94
   2.02  1.91  0.53  1.25  1.01  2.27  2.16  0.64  2.16  1.28
   2.16  2.93  1.59  0.42  1.08  0.93  0.94  0.89  1.28  0.40
   1.35  1.05  0.49  2.08  1.66  1.82  1.27  0.53  2.03  1.57
   0.83  2.16  2.23  0.74  0.65  1.03  1.38  1.00  1.08  1.66
   2.05  1.51  1.69  1.38  0.33  2.80  0.78  0.80  0.48  1.59
   0.55  1.48  1.06  0.92  1.24  2.25  1.15  0.51  1.61  2.18
   2.04  1.83  3.66  1.58  4.01  2.67  1.37  0.74  2.19  1.48
   0.00  0.12  1.21  0.16  1.36  2.87  0.36  0.60  1.98  1.04
   2.62  1.48  1.64  0.23  1.55  2.90  0.69  1.14  2.39  0.55


 Size = 2020 Dyn Array Mult Elapsed Time: 142.01 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.00  0.00  0.90  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.80  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


   2.01  2.40  3.44  3.49  1.03  1.09  1.70  2.34  0.25  0.52
   1.32  1.98  1.23  2.11  2.92  1.23  0.87  2.01  1.84  1.78
   2.09  1.16  1.59  1.66  2.83  1.90  1.51  2.75  2.67  1.93
   1.53  1.62  2.08  1.24  2.38  0.30  2.72  3.88  1.57  1.63
   1.61  3.59  4.08  2.96  2.87  1.95  2.70  1.79  2.14  1.49
   2.90  4.31  1.40  1.87  0.16  3.92  2.92  2.23  3.88  2.51
   3.24  2.28  2.34  0.22  3.33  1.77  2.14  4.28  2.52  1.68
   2.00  2.84  3.49  2.75  1.85  1.41  1.58  2.13  4.38  3.55
   0.96  1.20  1.87  1.17  1.11  1.80  1.36  1.40  1.66  2.91
   1.71  1.52  0.95  2.45  2.11  1.92  1.88  1.35  2.19  3.00


 Size = 3030 Dyn Array Mult Elapsed Time: 580.73 seconds.


 Program ended with exit code: 0

   0.00  0.00  0.00  0.00  0.80  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.70  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.20  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
   0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


   4.93  2.65  2.02  2.51  2.44  2.50  1.29  1.95  3.27  3.80
   2.88  4.08  2.36  4.21  3.20  4.47  5.12  1.62  3.32  1.62
   2.33  0.95  4.13  3.50  4.12  3.54  6.53  4.56  2.16  3.88
   5.13  3.48  6.44  5.11  1.64  2.19  2.91  2.04  4.46  0.91
   3.50  3.16  2.97  1.59  3.74  3.43  3.64  3.42  3.98  2.07
   2.31  3.15  2.08  1.78  2.44  4.52  3.43  2.05  3.07  2.48
   2.48  2.87  4.50  6.30  5.65  4.23  2.28  1.72  1.91  3.96
   4.64  4.31  4.82  4.14  3.25  2.42  1.92  1.55  2.41  1.35
   3.83  1.17  1.74  3.52  2.92  1.93  2.84  2.74  4.22  3.99
   5.26  3.77  1.15  5.57  4.37  6.63  2.70  3.88  1.16  2.59


 Size = 4040 Dyn Array Mult Elapsed Time: 1414.71 seconds.


 Program ended with exit code: 0

 ----------------------------- Questions -------------------------------------
 Time complexity of the operation relative to M: The matrix multiplication
 algorithm in this program will have a cubic time complexity, O(N^3).  Looking
 at the matrix multiplication function in the program,
 void matMultDyn(const DynMat & matA, const DynMat & matB,
 DynMat & matC, int size), there are 3 loops that loop from 0 to N - 1,
 where N (number of items) is equal to MAT_SIZE.  Since the operations inside
 the function do not depend on the number N, the operations have a constant time
 and do not contribute to Big O.  Since the 3 loops also do not vary in length,
 the algorithm will have an exact growth, theta(N^3).  Based on this, the
 minimum time complexity is equivalent to the maximum time complexity, where
 Big O = theta = Omega.

 1. What was the smallest M that gave a non-zero time?

    A MAT_SIZE of 101 gave the smallest non-zero time.  Compared to a MAT_SIZE
    of 100, which gave a zero time, a MAT_SIZE of 101 ran in 0.01 seconds.

 2. What happened when M was doubled, tripled, quadrupled, etc?  Show various
    M values and their times in a table.

    M (MAT_SIZE)  |  Time (seconds)
    -------------------------------
    101           |  0.01
    202           |  0.04
    303           |  0.18
    404           |  0.47
    1010          |  13.29
    2020          |  142.01
    3030          |  580.73
    4040          |  1414.71

 3. How large an M can be used before the program refuses to run (exception or
    run-time error due to memory overload) or it takes so long that waiting for
    a run takes too long to wait for?

    A run with a MAT_SIZE of 20200 was tried to see how long it took to run.
    After waiting for over 30 minutes, I decided to stop waiting and used a
    much larger MAT_SIZE to see when the program would crash.  When using a
    MAT_SIZE of 101000, the program crashed.

 4. How did the data agree or disagree with the original time complexity
    estimate?

    Based on the MAT_SIZE values above in the table, the values more or less
    follow a cubic growth.  While not exactly cubic, the values definitely grow
    much more in a cubic pattern rather than a constant, linear, or quadratic
    pattern.  While I could have incorporated more MAT_SIZE values, I believe
    the data falls more in line of a cubic growth, which makes sense due to the
    3 loops found in the matrix multiplication function.
 */
