#include <list>
#include "deque"
#include "unordered_map"
#include "iostream"
#include "algorithm"
template <typename K, typename V>
class LruCache {
public:

    LruCache(size_t max_size):size_(max_size){};

    void Put(const K& key, const V& value){
        if(mp.find(key)==mp.end()){
            if(deq.size()<size_){
                deq.push_front(std::make_pair(key,value));
                mp[key]=deq.begin();}
            else {
                mp.erase(deq.back().first);
                deq.pop_back();
                deq.push_front(std::make_pair(key,value));
                mp[key]=deq.begin();
            }}
        else
        {
            deq.erase(mp[key]);
            mp.erase(key);
            deq.push_front(std::make_pair(key,value));
            mp[key]=deq.begin();
        }


        /*  if(deq.size()<size_ or std::find(deq.begin(), deq.end(), key)!=deq.end()){
              if(std::find(deq.begin(), deq.end(), key)==deq.end())
           deq.push_back(key);

          if (mp.find(key)==mp.end()){
          mp.insert(std::make_pair(key,value));}
          else
              mp[key]=value;



          }
          else{
              mp.erase(deq.front());
           deq.pop_front();
           deq.push_front(key);
           mp.insert(std::make_pair(key,value));
          }
          if(cnt<deq.size()){
              cnt+=1;}*/
    };

    bool Get(const K& key, V* value){
        auto it=mp.find(key);
        if((it)!=mp.end()){
            *value= it->second->second;
            deq.erase(it->second);
            mp.erase(key);
            deq.push_front(std::make_pair(key,*value));
            mp[key]=deq.begin();
            return true;
        }
        return false;
        /* for(auto it=deq.begin();it!=deq.end();it++){
             if((*it)== key){
                 *value=mp[key];
                 std::swap(*it,*(deq.begin()+cnt-1));
                 if (cnt<deq.size()){
                     cnt+=1;}

                 return true;

         }
       }
           return false;*/}


private:
    size_t size_;
    std::list<std::pair<K,V>> deq;
    using it= typename std::list<std::pair<K,V>>::iterator;
    std::unordered_map<K,it>mp;
    //int cnt=0;

};