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
            queue.push(4);
            assert(queue.size() == 2);
            assert(queue.back() == 4);
            return true;
        }
    }
};