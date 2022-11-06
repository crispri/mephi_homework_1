#include <sstream>
#include "chrono"
#include "iostream"
class Timer {
public:

    Timer(  std::chrono::seconds sec ): polzovatel(sec){
        m_StartTime=std::chrono::steady_clock::now();
    };
    bool Expired() const{
        while( std::chrono::steady_clock::now()-m_StartTime<=polzovatel){
            return false;
        }
        return true;
    };
private:
    std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
    std::chrono::seconds polzovatel;
};

class TimeMeasurer {
public:
    TimeMeasurer(std::stringstream& stream):stream(stream){
        m_start=(std::chrono::steady_clock::now());

    }

    ~TimeMeasurer(){
        stream<<"Elapsed time: "<< std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-m_start).count()<<std::endl;
    }
private:
    std::stringstream& stream;
    std::chrono::steady_clock::time_point m_start;
};




