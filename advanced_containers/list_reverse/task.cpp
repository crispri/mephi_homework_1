#include "task.h"

void ReverseList(std::list<int>& l) {
    std::list<int>::iterator it = l.begin();

    std::list<int>::iterator it_ = l.end();
    it_--;
    for (int i = 0; i < l.size() / 2; ++i) {
        std::swap(*it, *it_);
        it_--;
        it++;
    }
}