#pragma once
#include "../types.hpp"
#include <string_view>
#include <concepts>
#include <string>

namespace match {
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
        // reads a number of bytes depending the size of U and reads the slice of bytes and compares them to the slice of bytes in the view
        template <typename U = T>
        inline bool PeekBack(const U* slice, u64 offset = 0) const {
            return memcmp(slice, m_tail + offset, sizeof(U)) == 0;
        }

        template <typename U = T>
        inline U PushBack(i64 incOffset = 1, i64 peekOffset = 0) {
            this->IncTail(incOffset);
            return this->Back<U>(peekOffset);
        }

        // TODO: Rename this method to something more descriptive
        template <typename U = T>
        inline bool IncIfPeekBack(U* value, i64 offset = 1) {
            if (this->PeekBack<U>(value)) {
                this->IncTail(offset);
                return true;
            }
            return false;
        }
        // todo make front methods





        template <typename U = T>
        inline U Front(i64 offset = 0) const {
            return *reinterpret_cast<U*>(m_head + offset);
        }

        template <typename U = T>
        inline U PushFront(i64 incOffset = 1, i64 peekOffset = 0) {
            this->IncHead(incOffset);
            return this->Front<U>(peekOffset);
        }

        /*
        TODO: Test These.

        template <typename U = T>
        inline U PopFront(i64 decOffset = 1, i64 peekOffset = 0) {
            this->IncHead(-decOffset);
            return this->Front<U>(peekOffset -1);
        }

        template <typename U = T>
        inline U PopBack(i64 decOffset = 1, i64 peekOffset = 0) {
            this->IncTail(-decOffset);
            return this->Back<U>(peekOffset + 1);
        }
        */

        inline void SetHead(T* head) { this->m_head = head; }

        inline void SetTail(T* tail) { this->m_tail = tail; }




        inline bool IsEmpty() const {
            return this->m_head == this->m_tail;
        }

        inline bool IsPopulated() const {
            return this->m_tail > this->m_head;
        }

        template <typename U = T>
        inline SlideView<U> SubView(i64 start = 0, i64 end = 0) {
            return SlideView<T>(this->m_head + start, this->m_head + end);
        }

        inline u64 Size() const { return this->m_tail - this->m_head; }

        template <typename U = T>
        inline bool IsWindowInBounds(u64 n, const SlideView<U>& window) const {
            return window.m_tail + n > this->m_tail ;
        }

        template <typename U = std::make_signed_t<T>>
        inline operator std::basic_string_view<U>() const {
			return std::basic_string_view<U>((const U*)this->m_head, (const U*)this->m_tail);
		}

        inline T& operator*() { return *m_head; }

        inline char operator[](u64 index) { return m_head[index]; }

        inline bool operator==(const SlideView<T>& window) const {
            return this->m_head == window.m_head && this->m_tail == window.m_tail;
        }

        inline bool operator!=(const SlideView<T>& window) const {
            return m_head != window.m_head || m_tail != window.m_tail;
        }

        inline void SetHeadToTail() {
            this->m_head = this->m_tail;
        }

        inline void SetTailToHead() {
            this->m_tail = this->m_head;
        }

        inline void SkipTail(u64 n = 1) {

            this->IncTail(n);
            this->SetHeadToTail();
        }

        inline void SkipHead(u64 n = 1) {
            this->IncHead(n);
            this->SetTailToHead();
        }


        /// Gets the index of the pointer in the view
        inline u16 IndexOf(const T* ptr) const {
            return ptr - this->m_head;
        }

        // TODO: Rename these?

        inline bool IsSubViewInBounds(const SlideView<T>& subView) {
            return subView.GetTail() < this->m_tail;
        }

        inline bool IsSubViewAtEnd(const SlideView<T>& subView) {
            return this->m_tail == subView.GetTail();
        }

        template <typename U = T>
        inline const U* GetHead() const {
            return static_cast<U*>(this->m_head);
        }

        template <typename U = T>
        inline const T* GetTail() const {
            return static_cast<U*>(this->m_tail);
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