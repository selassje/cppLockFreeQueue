#include "gtest/gtest.h"
#include "../lfQueue/lfQueue.hpp"
#include <thread>
#include <random>
#include <memory>
#include <vector>
#include <algorithm>

namespace lfQueue
{
    namespace tests
    {
        static lfQueue<int> queue;

        class lfQueueThread
        {
            public:
                virtual ~lfQueueThread() = default;
                lfQueueThread(lfQueueThread&&) = default;
                lfQueueThread() = default;

                void run() noexcept 
                {
                    m_thread = std::thread(&lfQueueThread::task, this);
                }

                void join() { m_thread.join();}
            private:
                virtual void task() = 0;
                std::thread m_thread;
        };

        class lfQueueThreadAdd : public lfQueueThread
        {
            public:
                lfQueueThreadAdd(int itemsToAddCount) : m_itemsToAddCount(itemsToAddCount){}
                lfQueueThreadAdd(lfQueueThreadAdd&&) = default;
                virtual ~lfQueueThreadAdd() = default;

            private:
                void task() noexcept override
                {
                    std::default_random_engine generator;
                    std::uniform_int_distribution<int> distribution(1, 10);

                    for (int i = 0; i < m_itemsToAddCount; ++i)
                    {
                        queue.emplace(distribution(generator));
                    }
                }

                const int m_itemsToAddCount;
        };
        
        using pLfQueueThread = std::unique_ptr<lfQueueThread>;

        void mt_test_add_only(const unsigned threadNum, const unsigned itemsToAddPerThread)
        {
            queue.clear();
            std::vector<pLfQueueThread> threads;
            for (unsigned i = 0; i < threadNum; ++i)
            {
                threads.emplace_back(std::make_unique<lfQueueThreadAdd>(itemsToAddPerThread));
            }

            std::for_each(threads.begin(), threads.end(), [](const auto& t) {t->run(); });
            std::for_each(threads.begin(), threads.end(), [](const auto& t) {t->join(); });
            EXPECT_EQ(queue.size(), itemsToAddPerThread* threadNum);
        }

        TEST(lfQueue, test_mt_add)
        {
            mt_test_add_only(3, 50);
            mt_test_add_only(5, 200);
        }

    }
}