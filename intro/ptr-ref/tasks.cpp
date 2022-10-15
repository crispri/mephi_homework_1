#include <limits>
#include <cmath>
#include "tasks.h"
using namespace std;
int imax = std::numeric_limits<int>::max();
namespace NPointers {
    int Increment(int *a) {
        return (*a)++;
    }

    int Multiply(int a, int b, bool *flag) {
        if ((a * b) <= imax) {
            (*flag) = false;
            return (a * b);
        } else
            (*flag) = true;
        return 0;
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
    long long *MultiplyToLongLong(const int a, const int b) {
        long long *p = new long long(a * b);
        return p;
    }
}
namespace NReferences{
    int MultiplyInplace(int &a, int b){
        a*=b;
        return a;
    }
    int CompareArraysByAverage(const int* a,int size_a, int* b){
        int sum_a=0;
        for(int i=0;i<size_a;i++){
            sum_a+=a[i];
        }
        float srznach_a=sum_a/size_a;
        int sum_b=0;
        for(int i=0;i<sizeof(b);i++){
            sum_b+=b[i];
        }
        float srznach_b=sum_b/(sizeof b);
        if (srznach_a<srznach_b)
            return -1;
        else if(srznach_a==srznach_b)
            return 0;
        else
            return 1;
    }
}


