#include "gtest/gtest.h"
#include "../lfQueue/lfQueue.hpp"

namespace lfQueue
{
    namespace tests
    {
        template<typename T>
        void basic_test(T&& a, T&& b)
        {
            lfQueue<int> queue;
            queue.push(a);
            EXPECT_EQ(queue.size(), 1);
            EXPECT_EQ(queue.front(), a);
            EXPECT_EQ(queue.back(), a);

            queue.push(b);
            EXPECT_EQ(queue.size(), 2);
            EXPECT_EQ(queue.back(), b);
            EXPECT_EQ(queue.front(), a);

            queue.pop();
            EXPECT_EQ(queue.size(), 1);
            EXPECT_EQ(queue.front(), b);
            EXPECT_EQ(queue.back(), b);

            queue.pop();
            EXPECT_EQ(queue.size(), 0);
        }

        TEST(lfQueue, test_lValue_push)
        {        
            int a = 3;
            int b = 5;
            basic_test(a,b);
        }

        TEST(lfQueue, test_rValue_push)
        {
            basic_test(3, 5);
        }
    }
}