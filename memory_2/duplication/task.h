#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include "map"
using namespace std;
vector<shared_ptr<string>> DeDuplicate( vector<unique_ptr<string>>& in){;
    vector<shared_ptr<string>> out;
    map<string,shared_ptr<string>>mp;
    for(const auto& un_ptr : in){
        mp.insert({*un_ptr.get(), make_shared<string>(*un_ptr.get())});
    }

    for(const auto& un_ptr : in){
        auto it=mp.find(*un_ptr.get());
        out.push_back(it->second);
    }
    return out;}

vector<unique_ptr<string>> Duplicate(const vector<shared_ptr<string>>& in){
    vector<unique_ptr<string>> out;
    for(const auto& un_ptr : in){
        out.push_back(make_unique<string>(*un_ptr.get()));
    }

    return out;
};