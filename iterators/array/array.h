#include <iostream>

template<typename T>
class Array {
private:
    T* Elements_;
    size_t Size_;
    size_t Capacity_;
    std::ostream& Ostream_;
public:
    Array(std::ostream& ostream):Ostream_(ostream){
        Elements_= new T[2];
        Size_=0;
        Capacity_=2;
         Ostream_<<"Constructed. "<<*this<<"\n";
    }


    Array(const Array<T>& array) :Ostream_(array.Ostream_){
        Size_=array.Size();
        Capacity_=array.Capacity();
        Elements_=new T[Capacity()];
        for(size_t i=0;i<Size();i++){
            Elements_[i]=array.Elements_[i];
        }
        Ostream_<<"Constructed from another Array. "<<*this<<"\n";
    }

    Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = T()): Ostream_(ostream){
        Size_=size;
        Capacity_=2*size;
        Elements_=new T[Capacity_];
        for(size_t i=0;i<size;i++){
            Elements_[i]=defaultValue;
        }
        Ostream_<<"Constructed with default. "<<*this<<"\n";

    }

    ~Array() {
        delete[] Elements_;
          Ostream_<<"Destructed "<<Size_<<"\n";
    }

    size_t Size() const {
        return Size_;
    }

    size_t Capacity() const {
        return Capacity_;
    }

    void Reserve(size_t newCapacity) {
        if (newCapacity>Capacity()) {
            T *Elem_ = new T[newCapacity];
            for (size_t i = 0; i < Size(); i++) {
                Elem_[i] = Elements_[i];
            }
            delete[] Elements_;
            Capacity_=newCapacity;
            Elements_=Elem_;
        }
    }

    void Resize(size_t newSize) {
        if(newSize>Capacity()){
            Reserve(newSize);
        }
        Size_=newSize;
    }

    void PushBack(T value ) {
        if(Size()==Capacity()){
            Array::Reserve(Capacity_*2);
        }
        Elements_[Size_++]=value;
    }

    void PopBack() {
        if(Size_>0)
            Size_--;
    }

    //const T& operator [](const size_t i) const {
    //}
    const T& operator [](const size_t i) const {
        return Elements_[i];
    }

    T& operator [](const size_t& i) {
        return *(Elements_+i);
    }

    explicit operator bool() const {
        if (Size_==0){
            return false;
        }
        return true;
    }

    bool operator <(const Array<T>& it) const {
        for(size_t i=0;i<std::min(it.Size(), Size());i++){
            if (Elements_[i]>it.Elements_[i]){
                return false;
            }
            else if(Elements_[i]<it.Elements_[i])
                return true;
        }
        return false;
    }

    bool operator >(const Array<T>& it) const {
        for(size_t i=0;i<std::min(it.Size(), Size());i++){
            if (Elements_[i]<it.Elements_[i]){
                return false;
            }
            else if(Elements_[i]>it.Elements_[i])
                return true;
        }
        return false;
    }

    //bool operator !=(const Array<T>& it) const {
    //}

    bool operator ==(const Array<T>& it) const {
        for(size_t i=0;i<std::min(it.Size(), Size());i++){
            if (Elements_[i]!=it.Elements_[i]){
                return false;
            }
            else
                return true;

        } return true;
    }

    //bool operator <=(const Array<T>& it) const {


//bool operator >=(const Array<T>& it) const {


    Array<T>& operator <<(const T& value) {
        PushBack(value);
        return *this;
    }

    Array<T>& operator <<(const Array<T>& it) {
        for (size_t i=0;i<it.Size();i++)
            PushBack(it.Elements_[i]);
        return *this;
    }

    bool Insert(size_t pos, const T& value) {

        if(pos>Size())
            return false;
        else{T* Elem_=new T [Size()+1];
            if(pos==0){
                Elem_[0]=value;
                for( size_t i=1;i<Size()+1;i++) {
                    Elem_[i] = Elements_[i - 1];
                }
                delete[] Elements_;
                Elements_=Elem_;
                Size_+=1;
                return true;
            }
            else if(pos==Size()){
                for(size_t i=0;i<Size();i++) {
                    Elem_[i] = Elements_[i];
                }
                Elem_[Size()]=value;
                delete[] Elements_;
                Elements_=Elem_;
                Size_+=1;
                return true;
            }
            else{
                for(size_t i=0;i<pos;i++){
                    Elem_[i]=Elements_[i];
                }
                Elem_[pos]=value;
                for(size_t i=pos+1;i<Size()+1;i++)
                    Elem_[i]=Elements_[i-1];
                delete[] Elements_;
                Elements_=Elem_;
                Size_+=1;
                return true;
            }}
    }

    bool Erase(size_t pos) {
        if(pos>Size())
            return false;
        else{
            T* Elem_=new T [Size()-1];
            for(size_t i=0;i<pos+1;i++){
                Elem_[i]=Elements_[i];
            }
            for(size_t i=pos+1;i<Size();i++)
                Elem_[i-1]=Elements_[i];
            delete[] Elements_;
            Elements_=Elem_;
            Size_-=1;
            return true;

        }
    }
    void Clear() {
        delete[] Elements_;
    }
    friend std::ostream& operator <<(std::ostream& ostream, const Array<T>& array){
        if(array.Size() == 0){
            ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << 0;
        }else if(array.Size() > 0){
            ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size()
                    << ", elements are: ";
            for (size_t i = 0; i < array.Size() - 1; ++i){
                ostream << *(array.Elements_ + i) << ", ";
            }
            ostream << *(array.Elements_ + array.Size() - 1);
        }
        return ostream;
    }



    T* begin()const{
        return Elements_;
    }
    T* end()const{
        return Elements_+Size();
    }


};





