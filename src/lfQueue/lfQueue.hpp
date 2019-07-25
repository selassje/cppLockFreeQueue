#ifndef LFQUEUE_HPP_INCLUDED
#define LFQUEUE_HPP_INCLUDED

namespace lfQueue
{
    template<typename T>
    class lfQueue
    {
        public: 
            std::size_t size() const {return m_Size;}
            void push(const T &t) noexcept;
            void push(const T &&t) noexcept;
            void pop() noexcept;
            const T& back() const noexcept;
            const T& front() const noexcept;
            virtual ~lfQueue() {};
        private:
            std::size_t m_Size = 0;

            struct node;
            using  pNode = std::unique_ptr<node>;
            struct node
            {
                T data;
                pNode next = nullptr;
                node* previous = nullptr;
                node(const T &t): data(t) {}
                node() = default;
            };

            void push_internal(pNode& newNode) noexcept;


            pNode m_Tail = nullptr;
            pNode m_Head = nullptr;
    };

    template<typename T>
    void lfQueue<T>::push_internal(pNode &pNewNode) noexcept
    {
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
    void lfQueue<T>::push(const T& t) noexcept
    {
        pNode pNewNode = std::make_unique<node>(t);
        push_internal(pNewNode);
    }

    template<typename T>
    void lfQueue<T>::push(const T&& t) noexcept
    {
        pNode pNewNode = std::make_unique<node>(t);
        push_internal(pNewNode);
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
