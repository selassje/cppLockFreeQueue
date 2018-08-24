#ifndef LFQUEUE_HPP_INCLUDED
#define LFQUEUE_HPP_INCLUDED

namespace lfQueue
{

template<typename T>
class lfQueue
{
public:
    void push(const T &t) {}
    std::size_t size() const {return 0;}

};
}

#endif
