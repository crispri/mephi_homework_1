#include "task.h"
bool isalpha(unsigned char c) {
    if ((c<='Z' and c>='A') or (c<='z' and c>='a'))
        return true;
    return false;
}
unsigned char tolower(unsigned char c) {
    if(c<='Z' and c>='A'){
        c+=32;
    }
    return c;
    
}
