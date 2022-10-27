#include "task.h"

using namespace std;

vector<int> HeapSort(const vector<int>& v) {
    priority_queue<int>q;
    for(auto i:v){
        q.push(i);
    }
    vector<int>f(v.size());
    for(int i=v.size()-1;i>=0;i--){
        f[i]=q.top();
        q.pop();
    }
    return f;
}
