#include "gtest/gtest.h"
#include "../lfQueue/lfQueue.hpp"

namespace lfQueue
{
    namespace tests
    {
        template<typename T>
        void basic_push_pop_test(T&& a, T&& b)
        {
            lfQueue<int> queue;
            ASSERT_FALSE(queue.pop());

            queue.push(std::forward<T&&>(a));
            EXPECT_EQ(queue.size(), 1u);

            EXPECT_EQ(queue.front(), a);
            EXPECT_EQ(queue.back(), a);

            queue.push(std::forward<T&&>(b));
            EXPECT_EQ(queue.size(), 2u);
            EXPECT_EQ(queue.back(), b);
            EXPECT_EQ(queue.front(), a);

            ASSERT_TRUE(queue.pop());
            EXPECT_EQ(queue.size(), 1u);
            EXPECT_EQ(queue.front(), b);
            EXPECT_EQ(queue.back(), b);

            ASSERT_TRUE(queue.pop());
            EXPECT_EQ(queue.size(), 0u);       
        }

        TEST(lfQueue, test_lValue_push_pop)
        {        
            int a = 3;
            int b = 5;
            basic_push_pop_test(a,b);
        }

        TEST(lfQueue, test_rValue_push_pop)
        {
            basic_push_pop_test(3, 5);
        }

        class constructionCounter
        {
        public :
            constructionCounter() { ++m_userCount;}
            constructionCounter(const constructionCounter&) { ++m_copyCount; }
            constructionCounter(constructionCounter&&) noexcept { ++m_moveCount; }
       
            const constructionCounter& operator=(const constructionCounter& a)
            {
                m_userCount = a.m_userCount;
                m_copyCount = a.m_copyCount;
                m_moveCount = a.m_moveCount;
                return *this;
            }

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

        TEST(lfQueue, construction_count_push_test)
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
        }

        TEST(lfQueue, construction_count_emplace_test)
        {
            constructionCounter copyEmplace;
            constructionCounter::reset();
            ASSERT_TRUE(constructionCounter::test(0, 0, 0));
            lfQueue<constructionCounter> queue;
            
            queue.emplace();
            ASSERT_TRUE(constructionCounter::test(1, 0, 0));

            constructionCounter::reset();
            queue.emplace(copyEmplace);
            ASSERT_TRUE(constructionCounter::test(0, 1, 0));

            constructionCounter::reset();
            queue.emplace(constructionCounter{});
            ASSERT_TRUE(constructionCounter::test(1, 0, 1));
        }

        TEST(lfQueue, basic_clear_test)
        {
            const unsigned size = 10;
            lfQueue<int> queue;
            for (unsigned i = 0; i < size; ++i) queue.emplace(i);
            EXPECT_EQ(queue.size(), size);
            queue.clear();
            EXPECT_EQ(queue.size(), 0u);
            ASSERT_FALSE(queue.front());
        }

        template<typename T>
        void test_dynamic_destructor()
        {
            std::make_unique<lfQueue<T>>().reset();         
        }

        TEST(lfQueue, test_dynamic_destructors)
        {
            test_dynamic_destructor<int>();
            test_dynamic_destructor<constructionCounter>();
        }

    }
}