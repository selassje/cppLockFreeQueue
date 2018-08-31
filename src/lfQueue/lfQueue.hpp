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
            const T& back() const noexcept;


            virtual ~lfQueue() {}
        private:
            std::size_t m_Size = 0;

            struct node;
            using  pNode = std::unique_ptr<node>;
            struct node
            {
                T data;
                pNode next = nullptr;
                node(const T &t): data(t) {}
            };

            pNode m_Tail = nullptr;
    };

    template<typename T>
    void lfQueue<T>::push(const T &t) noexcept
    {
        pNode pNewNode = std::make_unique<node>(t);
        if (nullptr != m_Tail)
        {
            pNewNode->next = std::unique_ptr<node>(m_Tail.get());
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


}




#endif
