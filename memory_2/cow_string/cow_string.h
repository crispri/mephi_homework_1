#include <cstddef>
#include <algorithm>

struct State{
    int ref_count;
    size_t Size_;
    size_t Capacity_;
    char* Object;
    State(){
        Object=new char[2];
        Capacity_=2;
        Size_=0;
        ref_count=1;
    }
    ~State(){
        delete[] Object;
    };
};

class CowString {
public:
    // constrcutors
   CowString()
    {
        //State_=new State{1,0,2,new char[2]};
        State_=new State();
        }
    CowString (const CowString& cow):State_(cow.State_){
        State_->ref_count+=1;

    }
    ~CowString(){
        if(State_->ref_count==1){
            delete State_;
            State_= nullptr;
        }
        else
            State_->ref_count-=1;
    }

    // copy operator=
    void operator=( const CowString& string){
        if(State_->ref_count>1){
            State_->ref_count-=1;
        }
        State_=string.State_;
        State_->ref_count+=1;
    }
    const char& At(size_t index) const{
        return State_->Object[index];
    };
    char& operator[](size_t index){
        if(State_->ref_count>1){
            State_->ref_count-=1;
            Set();}
        return State_->Object[index];
    };

    const char& Back() const{
        return State_->Object[Size()-1];
    };
    /*void Set(){
        if (State_->ref_count>1){
            State* state =new State();
            //state->Object=State_->Object;
            state->Size_=State_->Size_;
            state->Capacity_=State_->Capacity_;
            state->ref_count=1;
            char* t=new char[State_->Capacity_];
            for(size_t i=0;i<Size();i++){
                t[i]=State_->Object[i];
            }
            delete[] state->Object;
            state->Object=t;

            State_=state;

        }*/

    void Set(){
        /* if (State_->ref_count>1){
             State* state =new State();
             //state->Object=State_->Object;
             state->Size_=State_->Size_;
             state->Capacity_=State_->Capacity_;
             state->ref_count=1;
             char* t=new char[State_->Capacity_];
             for(size_t i=0;i<Size();i++){
                 t[i]=State_->Object[i];
             }
             delete[] state->Object;
             state->Object=t;

             State_=state;

         }*/
        State* state = new State();
        state->ref_count=1;
        state->Size_=State_->Size_;
        state->Capacity_=State_->Capacity_;
        char* t=new char[State_->Capacity_];
        for(size_t i=0;i<Size();i++){
            t[i]=State_->Object[i];
        }
        delete[] state->Object;
        state->Object=t;
        t= nullptr;
        State_=state;
    }
    void PushBack(char c){
        if(State_->ref_count>1)
            Set();
      if(Size()==Capacity()){
          Reserve(Size()*2);
      }
      State_->Object[Size()]=c;

        /*char* copyObject= State_->Object;
        for(auto i=0;i<Size();i++){
            copyObject[i]=State_->Object[i];
        }
        copyObject[Size()]=c;
            State_->Object= nullptr;
        State_->Object=copyObject;*/

        State_->Size_+=1;

    };

    size_t Size() const{
        return State_->Size_;
    };
    size_t Capacity() const{
        return State_->Capacity_;
    };

    void Reserve(size_t capacity){
        if(capacity<Size())
            State_->Size_=capacity;
        char*t=new char [capacity];
        for(size_t i=0;i<State_->Size_;i++){
            t[i]=State_->Object[i];
        }
        delete[] State_->Object;
        State_->Object=t;
        t= nullptr;
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
