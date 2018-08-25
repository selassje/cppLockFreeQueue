#ifndef LFQUEUE_HPP_INCLUDED
#define LFQUEUE_HPP_INCLUDED

namespace lfQueue
{
    template<typename T>
    class lfQueue
    {
        public:
            void push(const T &t) noexcept
            {
                auto pNewNode = std::make_unique<node>(t);
                if (nullptr == m_Head)
                {
                    m_Head = std::move(pNewNode);
                }
                else
                {
                    auto ptr = m_Head.get();
                    while (ptr->next != nullptr)
                    {
                        ptr = ptr->next.get();
                    }
                    ptr->next = std::move(pNewNode);
                }
                ++m_Size;
            }
            std::size_t size() const {return m_Size;}
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

            pNode m_Head = nullptr;
    };
}

#endif
