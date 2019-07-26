#ifndef LFQUEUE_HPP_INCLUDED
#define LFQUEUE_HPP_INCLUDED

#include<mutex>

namespace lfQueue
{
    template<typename T>
    class lfQueue
    {
        public: 
            std::size_t size() const {return m_Size;}
            void push(const T &t) noexcept;
            void push(T &&t) noexcept;
            template<typename... Args> void emplace(Args&&... args);
            void pop() noexcept;
            const T& back() const noexcept;
            const T& front() const noexcept;
            virtual ~lfQueue();
        private:
            std::size_t m_Size = 0;
            std::mutex  m_mutex;

            struct node;
            using  pNode = std::unique_ptr<node>;
            struct node
            {
                T data;
                pNode next = nullptr;
                node* previous = nullptr;
                node(const T &t): data(t) {}
                node(T&& t) : data(std::move(t)) {}
                node() = default;
            };

            pNode m_Tail = nullptr;
            pNode m_Head = nullptr;
    };

    template<typename T>
    lfQueue<T>::~lfQueue()
    { 
        m_Head.release();
    }
    
    template<typename T>
    void lfQueue<T>::push(const T& t) noexcept
    {
        emplace(t);
    }

    template<typename T>
    void lfQueue<T>::push(T&& t) noexcept
    {
        emplace(std::move(t));
    }

    template<typename T>
    template<typename... Args> 
    void lfQueue<T>::emplace(Args&& ... args)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        pNode pNewNode = std::make_unique<node>(std::forward<Args>(args)...);
        if (m_Size != 0)
        {
            pNewNode->next = std::unique_ptr<node>(m_Tail.get());
            m_Tail->previous = pNewNode.get();
            if (m_Size == 1)
            {
                m_Head = std::move(m_Tail);
            }
        }
        m_Tail.release();
        m_Tail = std::move(pNewNode);
        ++m_Size;
    }

    template<typename T>
    const T&  lfQueue<T>::back() const noexcept
    {
        return m_Tail->data;
    }

    template<typename T>
    const T&  lfQueue<T>::front() const noexcept
    {
        return m_Size == 1 ? m_Tail->data : m_Head->data;
    }

    template<typename T>
    void lfQueue<T>::pop() noexcept
    {
        if (m_Size > 0)
        {
            if (m_Size == 1)
            {
                m_Tail = nullptr;
            }
            else
            {
                auto prev = m_Head->previous;
                m_Head = nullptr;
                prev->next.release();
                if (m_Size != 2)
                {
                    m_Head = std::move(std::unique_ptr<node>(prev));
                }
            }
            --m_Size;
        }
    }
}
#endif
