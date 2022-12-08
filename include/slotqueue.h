/************************************************************************
 *
 * FIFO queue size MaxSize
 *
 ************************************************************************/

#ifndef SLOTQUEUE_H
#define SLOTQUEUE_H

#include <list>

template <typename T, int MaxSize>
class SlotQueue : public std::list<T> {
public:
    void push(const T& value)
    {
        if (this->size() >= MaxSize)
        {
           this->pop_front();
        }
        std::list<T>::push_back(value);
    }
};

#endif
