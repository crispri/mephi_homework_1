#pragma once
#include <limits>
#include <cmath>
using namespace std;
namespace NPointers {
    int Increment(int *a);

    int Multiply(int a, int b, bool *flag);
    int ScalarProduct(const int *a, const int *b, int size) ;
    int SizeOfMaximumSquareOfCrosses(const char *a1, int x, int y);
    long long *MultiplyToLongLong(const int a, const int b);
}
namespace NReferences{
    int MultiplyInplace(int &a, int b);
    int CompareArraysByAverage(const int* a,int size_a, int* b);}

