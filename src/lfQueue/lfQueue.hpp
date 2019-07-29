#ifndef LFQUEUE_HPP_INCLUDED
#define LFQUEUE_HPP_INCLUDED

#include<mutex>
#include<functional>
#include<optional>

namespace lfQueue
{
    template<typename T>
    class lfQueue
    {
        struct node;
        using  pNode = std::unique_ptr<node>;
        using  constOptRef = std::optional<const std::reference_wrapper<T>>;

        public: 
            std::size_t size() const {return m_Size;}
            void push(const T &t) noexcept;
            void push(T &&t) noexcept;
            template<typename... Args> void emplace(Args&&... args);
            bool pop() noexcept;
            auto back() const noexcept;
            auto front() const noexcept;
            void clear() noexcept;
            virtual ~lfQueue();
        private:
            std::size_t m_Size = 0;
            std::mutex  m_mutexEmplace;
            std::mutex  m_mutexPop;
            pNode m_Tail = nullptr;
            pNode m_Head = nullptr;
      
            struct node
            {
                T data;
                pNode next = nullptr;
                node* previous = nullptr;
                node(const T &t): data(t) {}
                node(T&& t) : data(std::move(t)) {}
                node() = default;
            };
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
        std::lock_guard<std::mutex> lock(m_mutexEmplace);
        std::lock_guard<std::mutex> lock2(m_mutexPop);

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
    auto lfQueue<T>::back() const noexcept
    {
        return m_Size > 0 ? constOptRef(m_Tail->data) : std::nullopt;
    }

    template<typename T>
    auto lfQueue<T>::front() const noexcept
    {
        return m_Size > 0 ? m_Size == 1 ? constOptRef(m_Tail->data) : constOptRef(m_Head->data)
                          : std::nullopt;
    }

    template<typename T>
    bool lfQueue<T>::pop() noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutexPop);
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
            return true;
        }
        return false;
    }

    template<typename T>
    void lfQueue<T>::clear() noexcept
    {
        m_Size = 0;
        m_Head.release();
        m_Tail.reset(nullptr);
    }
}
#endif
