#pragma once
#include <limits>
#include <cmath>
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
        int mx = 0;
        char a[1000][1000];
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                a[i][j] = a1[i * y + j];
            }
        }
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (a[i][j] == '+') {
                    mx = max(mx, 1);
                    for (int i1 = i; i1 < x; i1++) {
                        for (int j1 = j; j1 < y; j1++) {
                            if (a[i1][j1] == '.') {
                                mx = max(std::min(i1 - i, j1 - j), mx);
                                i1 = 3;
                                break;
                            }
                            mx = max(std::min(i1 - i + 1, j1 - j + 1), mx);
                        }
                    }
                }
            }
        }
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

