#include <cstddef>
#include <algorithm>

struct State{
    int ref_count=0;
    size_t Size_=0;
    size_t Capacity_=2;
    char* Object = nullptr;
    ~State(){
        delete[] Object;
    };
};

class CowString {
public:
    // constrcutors
    explicit CowString()
    {
        State_=new State{1,0,2,new char[2]};
    }
    CowString ( CowString& cow):State_(cow.State_){
        State_->ref_count+=1;

    }
    ~CowString(){
        if(State_->ref_count==1){
            delete State_;
        }
        else
            State_->ref_count-=1;
    }

    // copy operator=
    void operator=( CowString& string){
        if(State_->ref_count>1){
            State_->ref_count-=1;
        }
        State_=string.State_;
        State_->ref_count+=1;
    }
    const char& At(size_t index) const{
        return *(State_->Object +index);
    };
    char& operator[](size_t index){
        if(State_->ref_count>1)
            Set();
        return *(State_->Object+index );
    };

    const char& Back() const{
        return *(State_->Object+State_->Size_-1);
    };
    void Set(){
        if (State_->ref_count>1){
            State* state =new State;
            //state->Object=State_->Object;
            state->Size_=State_->Size_;
            state->Capacity_=State_->Capacity_;
            state->ref_count=1;
            char* t=new char[State_->Capacity_];
            for(auto i=0;i<Size();i++){
                t[i]=State_->Object[i];
            }
            state->Object=t;
            //delete State;

            State_=state;

        }
    }
    void PushBack(char c){
        if(State_->ref_count>1)
            Set();
        if(Capacity()>=Size()+1)
            State_->Object[Size()]=c;
        else{
            Reserve(Size()*2);
            State_->Object[Size()]=c;
        }
        /*char* copyObject= State_->Object;
        for(auto i=0;i<Size();i++){
            copyObject[i]=State_->Object[i];
        }
        copyObject[Size()]=c;
            State_->Object= nullptr;
        State_->Object=copyObject;*/

        State_->Size_=Size()+1;

    };

    size_t Size() const{
        return State_->Size_;
    };
    size_t Capacity() const{
        return State_->Capacity_;
    };

    void Reserve(size_t capacity){

        char*t=new char [capacity];
        for(auto i=0;i<State_->Size_;i++){
            t[i]=State_->Object[i];
        }
        delete[] State_->Object;
        State_->Object=t;
        State_->Capacity_=capacity;
    };
    void Resize(size_t size){
        if(size>Capacity()){
            Reserve(size*2);}
        State_->Size_=size;
    };
private:

    State* State_;

};
