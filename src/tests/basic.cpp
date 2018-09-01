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

            queue.push(4);
            assert(queue.size() == 2);
            assert(queue.back() == 4);
            assert(queue.front() == 3);

            queue.pop();
            assert(queue.size() == 1);
            assert(queue.front() == 4);
            assert(queue.back() == 4);

            queue.pop();
            assert(queue.size() == 0);


            return true;
        }
    }
};