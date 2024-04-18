#pragma once
#include "../types.hpp"
#include <string_view>
#include <concepts>
#include <string>

namespace Match {
    template <typename T>
    class SlideView {
    public:
        SlideView(T* start, T* end)
            : m_head(start), m_tail(end) {
        }
        SlideView(const T* start, const T* end) {
            m_head = const_cast<T*>(start);
            m_tail = const_cast<T*>(end);
        }

        SlideView(std::string_view view)
            : m_head((T*)view.data()), m_tail((T*)view.data() + view.size()) {
        }

        SlideView() {}

        inline void IncHead(u64 offset = 1) { this->m_head += offset; }
        inline void IncTail(u64 offset = 1) { this->m_tail += offset; }

        inline void DecHead(u64 offset = 1) { this->m_head -= offset; }
        inline void DecTail(u64 offset = 1) { this->m_tail -= offset; }

        template <typename U = T>
        inline U Back(i64 offset = 0) const {
            return *reinterpret_cast<U*>(m_tail + offset);
        }

        template <typename U = T>
        inline U Push(i64 offset = 0) {
            this->IncTail(offset);
            return this->Back<U>(offset);
        }

        template <typename U = T>
        inline U Front(i64 offset = 0) const {
            return *reinterpret_cast<U*>(m_head + offset);
        }

        template <typename U = T>
        inline U Pop(i64 offset = 0) {
            this->IncHead(offset);
            return this->Front<U>(offset);
        }

        inline bool IsEmpty() const {
            return this->m_head == this->m_tail;
        }

        inline bool IsPopulated() const {
            return this->m_head != this->m_tail;
        }

        template <typename U = T>
        inline SlideView<U> SubView(i64 start, i64 end) {
            return SlideView<T>(this->m_head + start, this->m_head + end);
        }

        inline u64 Size() const { return this->m_tail - this->m_head; }

        template <typename U = T>
        inline bool IsWindowInBounds(u64 n, const SlideView<U>& window) const {
            return this->m_tail + n <= window.m_tail;
        }

        template <typename U = T>
        inline SlideView<U> Window(u64 n = 0) {
            return SlideView<U>(this->m_head, this->m_head + n);
        }
        template <typename U = T>
        std::basic_string_view<U> ToString() const {
            return std::basic_string_view<U>(this->m_head, this->m_tail - this->m_head);
        }
        template <typename U = T>

        inline std::basic_string_view<U> operator()() {
            return std::basic_string_view<U>(this->m_head, this->m_tail - this->m_head);
        }

        inline T& operator*() { return *m_head; }

        inline char operator[](u64 index) { return m_head[index]; }

        inline bool operator==(const SlideView<T>& window) const {
            return this->m_head == window.m_head && this->m_tail == window.m_tail;
        }

        inline bool operator!=(const SlideView<T>& window) const {
            return m_head != window.m_head || m_tail != window.m_tail;
        }

        inline void reset() {
            this->m_head = this->m_tail;
        }

        inline void Skip(u64 n = 1) {

            this->IncHead(n);
            this->reset();
        }

        /// Gets the index of the pointer in the view
        inline u16 IndexOf(const T* ptr) const {
            return ptr - this->m_head;
        }

        inline bool IsWindowExhausted(const SlideView<T>& window) {
            return this->m_tail != window.GetTail();
        }

        inline const T* GetHead() const {
            return this->m_head;
        }

        inline const T* GetTail() const {
            return this->m_tail;
        }

        // Begin and end of the view
        inline const T* begin() const { return this->m_head; }
        inline const T* end() const { return this->m_tail; }

        // implicitly cast to another view type
        template <typename U>
        operator SlideView<U>() const {
            return SlideView<U>(this->m_head, this->m_tail);
        }


    private:
        T* m_head = nullptr;
        T* m_tail = nullptr;
    };

    using SlideViewWChar = SlideView<wchar_t>;
    using SlideViewChar32 = SlideView<char32_t>;
}