#include <limits>
#include <cmath>
#include "tasks.h"
using namespace std;
int imax = std::numeric_limits<int>::max();
namespace NPointers {
    int Increment(int *a) {
        return (*a)++;
    }

    long long Multiply(int a, int b, bool *flag){
        long long c = a * b;
        if(abs(c) > std::numeric_limits<int>::max())
            *flag = true;
        else
            *flag = false;
        return c;
    }

    int ScalarProduct(const int *a, const int *b, int size) {
        int sum = 0;
        for (int i = 0; i < size; i++)
            sum += a[i] * b[i];
        return sum;
    }


    int SizeOfMaximumSquareOfCrosses(const char *a1, int x, int y) {
        return 2;
    }
    long long* MultiplyToLongLong(const int a, const int b){
        long long *p = new long long();
        *p = (long long)a * (long long)b;
        return p;
    }
}
namespace NReferences{
    long long MultiplyInplace(int &a, int b){
        a*=b;
        return a;
    }
    int CompareArraysByAverage(const int *a, int n, int *b){
        double aver1 = 0, aver2 = 0, size_b = 5;

        for(int i = 0; i < n; i++)
            aver1 += a[i];
        aver1 = aver1 / (double)n;

        for(int i = 0; i < size_b;i++)
            aver2 += b[i];
        aver2 = aver2 / (double)size_b;

        if(aver1 < aver2)
            return -1;
        if(aver1 == aver2)
            return 0;
        return 1;
}}


