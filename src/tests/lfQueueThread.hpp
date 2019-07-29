#ifndef  LF_QUEUE_THREAD
#define  LF_QUEUE_THREAD

#include <thread>
#include <memory>
#include <random>
#include "lfQueue.hpp"

namespace lfQueue
{
    namespace tests 
    {
        template<typename T>
        class lfQueueThread
        {
        protected:
            using _mylfQueue = lfQueue<T>;
        public:
            virtual ~lfQueueThread() = default;
            lfQueueThread(lfQueueThread&&) = default;
            lfQueueThread(_mylfQueue &_lfQueue) : m_queue{ _lfQueue } {}

            void run() noexcept
            {
                m_thread = std::thread(&lfQueueThread::task, this);
            }

            void join() { m_thread.join(); }

        protected:
            _mylfQueue& m_queue;
        private:
            virtual void task() = 0;
            std::thread m_thread;
        };

        template<typename T>
        using pLfQueueThread = std::unique_ptr<lfQueueThread<T>>;

        template<typename T>
        class lfQueueThreadAdd : public lfQueueThread<T>
        {
            using _base = lfQueueThread<T>;
        public:
            lfQueueThreadAdd(typename _base::_mylfQueue& _lfQueue, int itemsToAddCount) :
                _base(_lfQueue),
                m_itemsToAddCount(itemsToAddCount)
            {}

            lfQueueThreadAdd(lfQueueThreadAdd&&) = default;
            virtual ~lfQueueThreadAdd() = default;

        private:
            void task() noexcept override
            {
                std::default_random_engine generator;
                std::uniform_int_distribution<int> distribution(1, 10);

                for (int i = 0; i < m_itemsToAddCount; ++i)
                {
                    _base::m_queue.emplace(distribution(generator));
                }
            }
            const int m_itemsToAddCount;
        };
    }
}
#endif