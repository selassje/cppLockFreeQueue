#include "gtest/gtest.h"
#include "../lfQueue/lfQueue.hpp"

namespace lfQueue
{
    namespace tests
    {
        template<typename T>
        void basic_push_test(T&& a, T&& b)
        {
            lfQueue<int> queue;
            queue.push(std::forward<T&&>(a));
            EXPECT_EQ(queue.size(), 1);
            EXPECT_EQ(queue.front(), a);
            EXPECT_EQ(queue.back(), a);

            queue.push(std::forward<T&&>(b));
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
            basic_push_test(a,b);
        }

        TEST(lfQueue, test_rValue_push)
        {
            basic_push_test(3, 5);
        }

        class constructionCounter
        {
        public :
            constructionCounter() { ++m_userCount;}
            constructionCounter(const constructionCounter&) { ++m_copyCount; }
            constructionCounter(constructionCounter&&) noexcept { ++m_moveCount; }
       
            static void reset() { m_moveCount = 0; m_copyCount = 0; m_userCount = 0; }
            static bool test(int u, int c, int m) { return m_userCount == u && m_copyCount == c && m_moveCount == m; }

        private :
            static int m_userCount;
            static int m_moveCount;
            static int m_copyCount;
        };

        int constructionCounter::m_moveCount = 0;
        int constructionCounter::m_copyCount = 0;
        int constructionCounter::m_userCount = 0;

        TEST(lfQueue, construction_count_test)
        {
            ASSERT_TRUE(constructionCounter::test(0, 0, 0));
            lfQueue<constructionCounter> queue;
            constructionCounter copyPush;
            queue.push(copyPush);
            ASSERT_TRUE(constructionCounter::test(1, 1, 0));
            constructionCounter::reset();

            ASSERT_TRUE(constructionCounter::test(0, 0, 0));
            queue.push({});
            ASSERT_TRUE(constructionCounter::test(1, 0, 1));

            constructionCounter::reset();
            queue.emplace();
            ASSERT_TRUE(constructionCounter::test(1, 0, 0));
        }

    }
}