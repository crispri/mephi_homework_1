#include <sstream>
#include "chrono"
#include "iostream"
class Timer {
public:
    using s      = std::chrono::duration< int>;
    Timer(s m_StartTime ): m_StartTime(m_StartTime){};
    bool Expired() const{
        if (steadyClock.now() >= this->m_StartTime)
            return false;
        else
            return true;
    };
private:
    std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
    std::chrono::steady_clock steadyClock;
};

class TimeMeasurer {
public:
    using ms      = std::chrono::duration< int>;
    TimeMeasurer(std::stringstream& sstream):stream(sstream),m_start(std::chrono::steady_clock::now()){

    }

    ~TimeMeasurer(){
        auto life=std::chrono::steady_clock::now()-m_start;
        std::cout<<"Elapsed time: "<< std::chrono::duration_cast<std::chrono::milliseconds>(life).count();
    }
private:
    std::stringstream& stream;
    std::chrono::steady_clock::time_point m_start;
};


