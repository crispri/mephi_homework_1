#include <iostream>
class Array {
public:
    Array(std::ostream& ostream);
    Array(const Array& array);
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue=0 );
    ~Array();



    size_t Size() const;
    size_t Capacity() const;
    void Reserve(size_t newCapacity);
    void Resize(size_t newSize);
    void PushBack(int value = 0);
    void PopBack();

    long long& operator [](const size_t& i);
    explicit operator bool() const;

    bool operator <(const Array& it) const;
    bool operator >(const Array& it) const;
    bool operator !=(const Array& it) const;
    bool operator ==(const Array& it) const;
    bool operator <=(const Array& it) const;
    bool operator >=(const Array& it) const;

    Array& operator <<(const int& value);
    Array& operator <<(const Array& it);

    friend std::ostream& operator <<(std::ostream& ostream, const Array& array);

private:
    long long* Elements_;
    long long Size_;
    long long Capacity_;
    std::ostream& Ostream_;
};
Array::Array(std::ostream& ostream): Ostream_(ostream){
    Elements_= new long long[2];
    Size_=0;
    Capacity_=2;
    Ostream_<<"Constructed. "<<*this<<"\n";
}
Array::Array(const Array& array):Ostream_(array.Ostream_){
    Size_=array.Size();
    Capacity_=array.Capacity();
    Elements_=new long long[Capacity()];
    for(size_t i=0;i<Size();i++){
        Elements_[i]=array.Elements_[i];
    }
    Ostream_<<"Constructed from another Array. "<<*this<<"\n";
}
Array::Array(size_t size, std::ostream& ostream , int defaultValue ):
        Ostream_(ostream){
    Size_=size;
    Capacity_=2*size;
    Elements_=new long long[Capacity_];
    for(size_t i=0;i<size;i++){
        Elements_[i]=defaultValue;
    }
    Ostream_<<"Constructed with default. "<<*this<<"\n";

}
Array::~Array(){
    delete[] Elements_;
    Ostream_<<"Destructed "<<Size_<<"\n";
}
size_t Array::Size() const{
    return Size_;
}
size_t Array::Capacity() const{
    return Capacity_;
}
void Array::Reserve(size_t newCapacity){
    if (newCapacity>Capacity()) {
        long long *Elem_ = new long long[newCapacity];
        for (size_t i = 0; i < Size(); i++) {
            Elem_[i] = Elements_[i];
        }
        delete[] Elements_;
        Capacity_=newCapacity;
        Elements_=Elem_;
    }
}
void Array::Resize(size_t newSize){
    if(newSize>Capacity()){
        Array::Reserve(newSize);
    }
    Size_=newSize;
}
void Array::PushBack(int value){
    if(Size()==Capacity()){
        Array::Reserve(Capacity_*2);
    }
    Elements_[Size_++]=value;
}
void Array::PopBack(){
    if(Size_>0)
        Size_--;
}
long long& Array::operator [](const size_t& i){
    return *(Elements_+i);
}

Array::operator bool() const{
    if (Size_==0){
        return false;
    }
    return true;

}
Array& Array::operator <<(const int& value){
    PushBack(value);
    return *this;
}
Array& Array::operator <<(const Array& other){
    for (size_t i=0;i<other.Size();i++)
        PushBack(other.Elements_[i]);
    return *this;
}
bool Array::operator <(const Array& it) const{
    for(size_t i=0;i<std::min(it.Size(), Size());i++){
        if (Elements_[i]>it.Elements_[i]){
            return false;
        }
        else if(Elements_[i]<it.Elements_[i])
            return true;
    }
    return false;
}
bool Array::operator >(const Array& it) const{
    for(size_t i=0;i<std::min(it.Size(), Size());i++){
        if (Elements_[i]<it.Elements_[i]){
            return false;
        }
        else if(Elements_[i]>it.Elements_[i])
            return true;
    }
    return false;
}
bool Array::operator !=(const Array& it) const{
    for(size_t i=0;i<std::min(it.Size(), Size());i++){
        if (Elements_[i]==it.Elements_[i]){
            return false;
        } else
            return true;

    } return true;
}
bool Array::operator ==(const Array& it) const{
    for(size_t i=0;i<std::min(it.Size(), Size());i++){
        if (Elements_[i]!=it.Elements_[i]){
            return false;
        }
        else
            return true;

    } return true;
}
bool Array::operator <=(const Array& it) const {
    for (size_t i = 0; i < std::min(it.Size(), Size()); i++) {
        if (Elements_[i] > it.Elements_[i]) {
            return false;
        }
        else if (Elements_[i]<=it.Elements_[i])
            return true;

    }return true;
}
bool Array::operator >=(const Array& it) const{
    for (size_t i = 0; i < std::min(it.Size(), Size()); i++) {
        if (Elements_[i] < it.Elements_[i]) {
            return false;
        }
        else
            return true;

    }return true;
}
std::ostream& operator <<(std::ostream& ostream, const Array& array) {

    ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size();
    if (array.Size() != 0) {
        ostream << ", elements are:";
        for (size_t i = 0; i < array.Size() - 1; i++) {
            ostream << " " << array.Elements_[i] << ",";
        }
        ostream << " " << array.Elements_[array.Size() - 1];
    }


    return ostream;
}