#include "gtest/gtest.h"
#include "lfQueueThread.hpp"
#include <vector>
#include <algorithm>

namespace lfQueue
{
    static lfQueue<int> queue{};

    namespace tests
    {
        template<typename T>
        void mt_test_add_only(const unsigned threadNum, const unsigned itemsToAddPerThread)
        {
            queue.clear();
            std::vector<pLfQueueThread<T>> threads;
            for (unsigned i = 0; i < threadNum; ++i)
            {
                threads.emplace_back(std::make_unique<lfQueueThreadAdd<T>>(queue, itemsToAddPerThread));
            }

            std::for_each(threads.begin(), threads.end(), [](const auto& t) {t->run(); });
            std::for_each(threads.begin(), threads.end(), [](const auto& t) {t->join(); });
            EXPECT_EQ(queue.size(), itemsToAddPerThread* threadNum);
        }

        TEST(lfQueue, test_mt_add_primitive)
        {
            mt_test_add_only<int>(3, 50);
            mt_test_add_only<int>(5, 200);
        }
    }
}