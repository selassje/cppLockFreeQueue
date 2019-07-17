#include <cstddef>
#include <memory>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include "../lfQueue/lfQueue.hpp"


namespace lfQueue
{
    namespace tests
    {
        bool basicTestCase1()
        {
           
            lfQueue<int> queue;
            queue.push(3);
            assert(queue.size() == 1);
            assert(queue.front() == 3);
            assert(queue.back() == 3);

            queue.push(5);
            assert(queue.size() == 2);
            assert(queue.back() == 5);
            assert(queue.front() == 3);

            queue.pop();
            assert(queue.size() == 1);
            assert(queue.front() == 5);
            assert(queue.back() == 5);

            queue.pop();
            assert(queue.size() == 0);

            return true;
        }
    }
};