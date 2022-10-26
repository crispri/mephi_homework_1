#include "task.h"

char* concat(const char* lhs, const char* rhs) {
    int i=0;
    int j=0;
    char* con = new char;
    while(lhs[i]!='\0'){
        con[i]=lhs[i];
        i+=1;
    }
    while(rhs[j]!='\0'){
        con[i+j]=rhs[j];
        j+=1;}


    return con;
}
