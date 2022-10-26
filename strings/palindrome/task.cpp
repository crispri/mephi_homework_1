#include "task.h"
#include <string>
bool is_palindrome(const std::string& s) {
    string ans="";
    for(long unsigned int i=0;i<s.length();i++){

        if ((s[i]<='Z' and s[i]>='A') or(s[i]<='z' and s[i]>='a'))
            ans+=s[i];
    }
    int x=ans.length();
    for(int i=0;i<x/2;i++)
        if(ans[i]==ans[x-i-1] or abs(ans[x-i-1]-ans[i])==32)
            continue;
        else
            return false;
    return true;
}


