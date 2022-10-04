#include "tasks.h"
#include <cmath>

namespace NOuter{
    namespace NInner{
        int DoSomething(int a,int b){
            cout<<a+b<<endl;
            return a+b;

        }
    }
    int DoSomething(int a, int b){
        cout<<a-b<<endl;
        return a-b;

    }
}
namespace NOverload{
    int ProcessTwoArgs(int lhs, int rhs){
        cout<<lhs+rhs<<endl;
        return lhs+rhs;
    }
    char ProcessTwoArgs(char lhs, char rhs){
        if (lhs>rhs){
            cout<<lhs<<endl;
            return lhs;}
        else{
            cout<<rhs<<endl;
            return rhs;}
    }
    int ProcessTwoArgs(int lhs, char rhs){
        cout<<lhs-int(rhs)<<endl;
        return lhs-int(rhs);

    }

}
namespace NOverflow {
    unsigned int WithOverflow(int lhs, int rhs){
        cout<<lhs+rhs<<endl;
        return lhs+rhs;
    }
    uint64_t WithOverflow(int64_t lhs, int64_t rhs){
        cout<<(lhs>rhs ? lhs-rhs:rhs-lhs)<<endl;
        return lhs>rhs ? lhs-rhs:rhs-lhs;
    }
}

namespace NLoop {
    int SumInRange(const int lhs, const int rhs){
        int sum=0;
        for (int i=lhs;i<rhs;i+=1){
            sum+=i;
        }
        cout<<sum<<endl;
        return sum;
    }
    int CountFixedBitsInRange(const int from, const int to, const int bitsCnt){
        int ans=0;
        for (int i=from;i<=to;i+=1){
            int counter=0;
            int j=i;
            while (j){
                if (j%2==1)
                    counter+=1;
                j/=2;
            }
            if (counter==bitsCnt)
                ans+=1;


        }
        cout<<ans<<endl;
        return ans;

    }
}

namespace NMath {
    double ComputeMathFormula(const double a){
        cout<<(-((sin(a) / 2 + cos(a)) * (sin(a) / 2 + cos(a)) + tan(a) * atan(a)))<<endl;
        return -((sin(a) / 2 + cos(a)) * (sin(a) / 2 + cos(a)) + tan(a) * atan(a));
    }
    bool IsPositive(int arg){
        if (arg>0){
            cout<<true<<endl;
            return true;}
        else{
            cout<<false<<endl;
            return false;}
    }
}

namespace NRecursion {
    int CalculateFibonacci(const int arg){
        int *a=new int [arg+1];
        a[1]=1;
        a[2]=1;
        for (int i=3;i<=arg;i+=1){
            a[i]=a[i-1]+a[i-2];
        }
        cout<<a[arg]<<endl;
        return a[arg];
    }
}
