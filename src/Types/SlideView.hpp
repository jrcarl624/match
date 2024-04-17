#pragma once
#include "../types.hpp"
#include <string_view>
#include <concepts>
#include <string>

namespace Match
{
    template <typename T>
    class SlideViewGeneric
    {
    public:
        SlideViewGeneric(T *start, T *end)
            : m_head(start), m_tail(end)
        {
        }
        SlideViewGeneric(const T *start, const T *end)
        {
            m_head = const_cast<T *>(start);
            m_tail = const_cast<T *>(end);
        }

        SlideViewGeneric(std::string_view view)
            : m_head((T *)view.data()), m_tail((T *)view.data() + view.size())
        {
        }

        SlideViewGeneric() {}

        inline void IncHead(uSize offset = 1) { this->m_head += offset; }
        inline void IncTail(uSize offset = 1) { this->m_tail += offset; }

        inline void DecHead(uSize offset = 1) { this->m_head -= offset; }
        inline void DecTail(uSize offset = 1) { this->m_tail -= offset; }

        template <std::integral U = T>
        inline U Back(i64 offset = 0) const
        {
            return *reinterpret_cast<U *>(m_tail + offset);
        }


        template <std::integral U = T>
        inline const U &BackRef(i64 offset = 0) const
        {
            return *reinterpret_cast<U *>(m_tail + offset);
        }

        template <std::integral U = T>
        inline U Front(i64 offset = 0) const
        {
            return *reinterpret_cast<U *>(m_head + offset);
        }

        template <std::integral U = T>
        inline const U &FrontRef(i64 offset = 0) const
        {
            return *reinterpret_cast<U *>(m_head + offset);
        }

        inline bool IsEmpty() const
        {
            return this->m_head == this->m_tail;
        }

        inline bool IsPopulated() const
        {
            return this->m_head != this->m_tail;
        }

        inline SlideViewGeneric<T> SubView(i64 start, i64 end)
        {
            return SlideViewGeneric<T>(this->m_head + start, this->m_head + end);
        }

        inline uSize Size() const { return this->m_tail - this->m_head; }

        inline bool IsWindowInBounds(uSize n, const SlideViewGeneric<T> &window) const
        {
            return this->m_tail + n <= window.m_tail;
        }

        template <typename U = T>
        inline SlideViewGeneric<U> Window(uSize n)
        {
            return SlideViewGeneric<U>(this->m_head, this->m_head + n);
        }

        std::basic_string_view<T> ToString() const
        {
            return std::basic_string_view<T>(this->m_head, this->m_tail - this->m_head);
        }

        inline std::basic_string_view<T> operator()()
        {
            return std::basic_string_view<T>(this->m_head, this->m_tail - this->m_head);
        }

        inline T &operator*() { return *m_head; }

        inline char operator[](uSize index) { return m_head[index]; }

        inline bool operator==(const SlideViewGeneric<T> &window) const
        {
            return this->m_head == window.m_head && this->m_tail == window.m_tail;
        }

        inline bool operator!=(const SlideViewGeneric<T> &window) const
        {
            return m_head != window.m_head || m_tail != window.m_tail;
        }

        inline void reset()
        {
            this->m_head = this->m_tail;
        }

        inline void Skip(uSize n = 1)
        {

            this->IncHead(n);
            this->reset();
        }

        /// Gets the index of the pointer in the view
        inline u16 IndexOf(const T *ptr) const
        {
            return ptr - this->m_head;
        }

        inline bool IsWindowExausted(const SlideViewGeneric<T> &window)
        {
            return this->m_tail != window.GetTail();
        }

       

        inline const T *GetHead() const
        {
            return this->m_head;
        }

        inline const T *GetTail() const
        {
            return this->m_tail;
        }

        // Begin and end of the view
        inline const T *begin() const { return this->m_head; }
        inline const T *end() const { return this->m_tail; }

    private:
        T *m_head = nullptr;
        T *m_tail = nullptr;
    };

    using SlideViewChar = SlideViewGeneric<char>;
    using SlideViewWChar = SlideViewGeneric<wchar_t>;
    using SlideViewChar32 = SlideViewGeneric<char32_t>;
}