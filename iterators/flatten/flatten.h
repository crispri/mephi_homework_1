#pragma once
#include <vector>
template<class T >
class TFlattenedIterator{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;  // or also value_type*
    using reference         = T&;
    using TInnerIter = typename std::vector<std::vector<T>>::iterator;
    TFlattenedIterator(TInnerIter innerIter, std::vector<std::vector<T>>& flatten_vec,std::vector<int>& pref_sum, size_t conuter, size_t size):
            innerIter_(innerIter), flatten_vec(flatten_vec),  pref_sum(pref_sum), counter(conuter), size(size){}
    reference operator*() const{
        size_t l =1;
        size_t r = size;
        bool flag = false;
        size_t m =0;
        while(r>=l and !flag){
            m =(l+r)/2;
            if(pref_sum[m] == counter+1  and pref_sum[m-1]!=counter+1 ){
                r=m;
                flag=true;
            }
            else if(pref_sum[m] < counter+1 )
                l = m+1;
            else if(pref_sum[m] >=counter+1 )
                r= m -1 ;
        }
        if(!flag)
            return flatten_vec[r][counter - pref_sum[r]];
        else
            return flatten_vec[r-1][counter - pref_sum[r-1]];
    }

    reference operator[](const TFlattenedIterator<T>& index) const{
        size_t l =1;
        size_t r = size;
        bool flag = false;
        size_t m =0;
        while(r>=l and !flag){
            m =(l+r)/2;
            if(pref_sum[m] == index.counter+counter+1 and pref_sum[m-1]!=index.counter+counter+1){
                r=m;
                flag=true;
            }
            else if(pref_sum[m] <= index.counter+counter+1 )
                l = m+1;
            else if(pref_sum[m] >index.counter+counter+1)
                r= m -1 ;
        }
        if(!flag)
            return flatten_vec[r][index.counter+counter - pref_sum[r]];
        else
            return flatten_vec[r-1][index.counter+counter - pref_sum[r-1]];

    }
    reference operator[](size_t index) const{
        size_t l =1;
        size_t r = size;
        bool flag = false;
        size_t m =0;
        while(r>=l and !flag){
            m =(l+r)/2;
            if(pref_sum[m] == index+counter+1 and pref_sum[m-1]!=index+counter+1){
                r=m;
                flag=true;
            }
            else if(pref_sum[m] <= index+counter+1 )
                l = m+1;
            else if(pref_sum[m] >index+counter+1)
                r= m -1 ;
        }
        if(!flag)
            return flatten_vec[r][index+counter - pref_sum[r]];
        else
            return flatten_vec[r-1][index+counter - pref_sum[r-1]];
    }
    TFlattenedIterator<T>& operator++(){

        if(counter<pref_sum[size]){
            counter+=1;
            ++innerIter_;}
        else
            innerIter_= TInnerIter ();
        return *this;
    }
    TFlattenedIterator<T>& operator--(){
        counter-=1;
        -- innerIter_;
        return *this;
    }
    TFlattenedIterator<T> operator = (const TFlattenedIterator<T>& other)  {
        this->counter = other.counter;
        return *this;
    }
    TFlattenedIterator<T> operator+(size_t other) const {
        return TFlattenedIterator<T>(innerIter_,flatten_vec,pref_sum,counter+ other, size);
    }


    TFlattenedIterator<T> operator-(size_t other) const {
        return TFlattenedIterator<T>(innerIter_,flatten_vec,pref_sum,counter - other, size);
    }
    size_t operator-(const TFlattenedIterator<T>& other) const {
        return counter - other.counter;
    }
    bool operator == (const TFlattenedIterator<T>& other) const {
        return (counter == other.counter);
    }
    bool operator !=(const TFlattenedIterator<T>& other) const{
        return counter!= other.counter;
    }
    TFlattenedIterator<T>& operator+=(const TFlattenedIterator<T>& other){
        this->counter+=other.counter;
        return *this;
    }
    TFlattenedIterator<T>& operator-=(const TFlattenedIterator<T>& other){
        this->counter-=other.counter;
        return *this;
    }
    TFlattenedIterator<T>& operator+=(size_t other){
        this->counter+=other;
        return *this;
    }
    TFlattenedIterator<T>& operator-=(size_t other){
        this->counter-=other;
        return *this;
    }
    template<class A>
    friend bool operator<=(const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);

    template<class A>
    friend bool operator>=(const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);

    template<class A>
    friend bool operator >(const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);

    template<class A>
    friend bool operator <(const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);

    template<class A>
    friend  TFlattenedIterator<A> operator - ( const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);


    template<class A>
    friend  TFlattenedIterator<A> operator + ( const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);

    template<class A>
    friend  TFlattenedIterator<A> operator + ( size_t lhs, const TFlattenedIterator<A>& rhs);

    template<class A>
    friend bool operator == ( const TFlattenedIterator<A>& lhs, size_t rhs);

    template<class A>
    friend bool operator == (const TFlattenedIterator<A>& lhs, const TFlattenedIterator<A>& rhs);




private:
    TInnerIter innerIter_;
    std::vector<std::vector<T>>&flatten_vec;
    std::vector<int>& pref_sum;
    size_t counter;
    size_t size;

};
template<class T >
bool operator <=(const TFlattenedIterator<T>& lhs, const TFlattenedIterator<T>& rhs){
    return lhs.counter<=rhs.counter;
}

template<class T >
bool operator >=(const TFlattenedIterator<T>& lhs, const TFlattenedIterator<T>& rhs){
    return lhs.counter>=rhs.counter;
}

template<class T >
bool operator >(const TFlattenedIterator<T>& lhs, const TFlattenedIterator<T>& rhs){
    return lhs.counter>rhs.counter;
}

template<class T >
bool operator <(const TFlattenedIterator<T>& lhs, const TFlattenedIterator<T>& rhs){
    return lhs.counter<rhs.counter;
}

template<class T>
TFlattenedIterator<T> operator - ( const TFlattenedIterator<T>& lhs, const TFlattenedIterator<T>& rhs){
    return TFlattenedIterator<T>(lhs.innerIter_,lhs.flatten_vec,lhs.pref_sum, lhs.counter-rhs.counter, lhs.size);
}

template<class T> // + не эвивалентен += поэтому нужно создавать новый итератор и возвращать его
TFlattenedIterator<T> operator + ( const TFlattenedIterator<T>& lhs,  const  TFlattenedIterator<T>& rhs){
    return TFlattenedIterator<T>(lhs.innerIter_,lhs.flatten_vec, lhs.pref_sum, lhs.counter + rhs.counter, lhs.size);
}

template<class T> // + не эвивалентен += поэтому нужно создавать новый итератор и возвращать его
TFlattenedIterator<T> operator + ( size_t lhs,  const  TFlattenedIterator<T>& rhs){
    return TFlattenedIterator<T>(rhs.innerIter_,rhs.flatten_vec, rhs.pref_sum, lhs + rhs.counter, rhs.size);
}

template<class T>
bool operator == ( const TFlattenedIterator<T>& lhs, size_t rhs){
    return lhs.counter == rhs;
}
template<class T>
bool operator == (const TFlattenedIterator<T>& lhs, const TFlattenedIterator<T>& rhs){
    return lhs.counter == rhs.counter;
}

template<class T = int>
class FlattenedVector {
public:
    FlattenedVector(std::vector<std::vector<T>>& vec):input_(vec), counter(0){
        if(!input_.empty()){
            pref_sum.push_back(0);
            for(size_t i =0;i<input_.size();i++){
                pref_sum.emplace_back( pref_sum[i] +input_[i].size() );
            }}
        size = input_.size();
    }
    TFlattenedIterator<T> begin(){
        return TFlattenedIterator<T>(input_.begin(),input_,pref_sum,0,size);
    }
    TFlattenedIterator<T> end(){
        return TFlattenedIterator<T>(input_.end(), input_, pref_sum, input_.empty()? 0:pref_sum[size], size);
    }
private:
    std::vector<int> pref_sum;
    std::vector<std::vector<T>>& input_;
    size_t size;
    size_t counter;
};

