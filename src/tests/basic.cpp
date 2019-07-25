#include "gtest/gtest.h"
#include "../lfQueue/lfQueue.hpp"

namespace lfQueue
{
    namespace tests
    {
        TEST(lfQueue, test_1)
        {
           
            lfQueue<int> queue;
            queue.push(3);
            EXPECT_EQ(queue.size(),1);
            EXPECT_EQ(queue.front(), 3);
            EXPECT_EQ(queue.back(),3);

            queue.push(5);
            EXPECT_EQ(queue.size(), 2);
            EXPECT_EQ(queue.back(), 5);
            EXPECT_EQ(queue.front(),3);

            queue.pop();
            EXPECT_EQ(queue.size(), 1);
            EXPECT_EQ(queue.front(), 5);
            EXPECT_EQ(queue.back(), 5);

            queue.pop();
            EXPECT_EQ(queue.size(), 0);
        }
    }
}