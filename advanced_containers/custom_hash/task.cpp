 #include "task.h"

void PopulateHashMap(
    unordered_map<SuperKey, string>& hashMap,
    const vector<pair<SuperKey, string>>& toAdd
) {
     for(auto i:toAdd){
         hashMap[i.first]=i.second;
     }
}
