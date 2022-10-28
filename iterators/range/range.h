#pragma once

#include <cmath>
#include "iostream"
#include "vector"
class TIterator {
private:
    int64_t step;
    int64_t current;
    int64_t end;
public:
    TIterator(int64_t step, int64_t current, int64_t end): step(step), current(current), end(end){};
    int64_t operator *() const{
        return current;
    }
    TIterator& operator++(){
        if(step> 0 && current + step > end){
            current = end;
            return *this;
        }
        else if(step < 0 && current + step < end){
            current = end;
            return *this;
        }
        current+=step;
        return *this;
    }
    TIterator operator++(int){
        TIterator copy = *this;
        operator++();
        return copy;
    }


    friend bool operator!=(const TIterator& it1, const TIterator& it2){
        if (it1.current == it2.current && it1.step == it2.step){

            return false;
        }
        return true;
    };
    friend bool operator==(const TIterator& it1, const TIterator& it2){
        if (it1 != it2) return false;
        return true;
    }

};

class Range {
private:
    int64_t start;
    int64_t finish;
    int64_t step;
public:
    explicit Range(int64_t n):
            start(0),
            finish(n),
            step(1){};
    Range(int64_t start, int64_t end):
            start(start),
            finish(end),
            step(1){};
    Range(int64_t start, int64_t end,int64_t step):
            start(start),
            finish(end),
            step(step){};

    const TIterator begin() const {
        return TIterator(step, start, finish);
    }
    const TIterator end() const {
        return TIterator(step, finish, finish);
    }

    int64_t Size() const {
        return ceil((finish-start)/double (step));
    }


};