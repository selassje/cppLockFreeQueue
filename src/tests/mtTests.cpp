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
        void mt_test_add_remove(const unsigned addThreadNum, 
                                const unsigned itemsToAddPerThread,
                                const unsigned removeThreadNum,
                                const unsigned itemsToRemovePerThread)

        {
            const size_t totalItemsToAdd = addThreadNum * itemsToAddPerThread;
            const size_t totalItemsToRemove = removeThreadNum * itemsToRemovePerThread;

            assert(totalItemsToAdd >= totalItemsToRemove);
            queue.clear();
           
            std::vector<pLfQueueThread<T>> threads;
            for (unsigned i = 0; i < addThreadNum; ++i)
            {
                threads.emplace_back(std::make_unique<lfQueueThreadAdd<T>>(queue, itemsToAddPerThread));
            }

            for (unsigned i = 0; i < removeThreadNum; ++i)
            {
                threads.emplace_back(std::make_unique<lfQueueThreadRemove<T>>(queue, itemsToRemovePerThread));
            }

            std::for_each(threads.begin(), threads.end(), [](const auto& t) {t->run(); });
            std::for_each(threads.begin(), threads.end(), [](const auto& t) {t->join(); });
            EXPECT_EQ(queue.size(), totalItemsToAdd - totalItemsToRemove);
        }

        template<typename T>
        void mt_test_add_only(const unsigned threadNum, const unsigned itemsToAddPerThread)
        {
            mt_test_add_remove<T>(threadNum, itemsToAddPerThread, 0u, 0u);
        }

        TEST(lfQueue, test_mt_add_primitive)
        {
            mt_test_add_only<int>(3, 50);
            mt_test_add_only<int>(5, 200);
        }

        TEST(lfQueue, test_mt_add_remove_primitive)
        {
            mt_test_add_remove<int>(3, 50, 2, 75);
            mt_test_add_remove<int>(3, 50, 2, 40);
            mt_test_add_remove<int>(100, 50, 100, 40);
        }

    }
}