#include "task.h"

void ReverseList(std::list<int>& l) {
    std::list<int>::iterator it;

    std::list<int>::iterator it_ = l.end();
    it_--;
    for (it = l.begin(); it != l.end(); ++it) {
        std::swap(*it, *it_);
        it_--;
    }
}