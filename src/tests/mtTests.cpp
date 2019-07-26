#include "gtest/gtest.h"
#include "../lfQueue/lfQueue.hpp"
#include <thread>
#include <random>
#include <memory>

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

        TEST(lfQueue, test_mt_2_threads_add)
        {

            pLfQueueThread threads[] = {
                                         std::make_unique<lfQueueThreadAdd>(50),
                                         std::make_unique<lfQueueThreadAdd>(50)
                                       };

            threads[0]->run();
            threads[1]->run();

            threads[0]->join();
            threads[1]->join();

            EXPECT_EQ(queue.size(), 100u);
        }

    }
}