#pragma once
#include "../types.hpp"
#include <string_view>
#include <concepts>
#include <string>

namespace Match
{
    template<typename T>
    class SlideViewGeneric
    {
    public:
        SlideViewGeneric(T* start, T* end)
            : m_start(start), m_end(end)
        {
        }
        SlideViewGeneric(std::string_view view)
            : m_start((T*)view.data()), m_end((T*)view.data() + view.size())
        {
        }

        SlideViewGeneric() {}

        inline void IncHead(uSize offset = 1){ m_start += offset;}
        inline void IncTail(uSize offset = 1){ m_end += offset;}

        inline void DecHead(uSize offset = 1){ m_start -= offset;}
        inline void DecTail(uSize offset = 1){ m_end -= offset;}

        template<std::integral U = u8>
        inline const U& Peak(i64 offset = 0) const
        {
            return *reinterpret_cast<U*>(m_start + offset);
        }

        inline bool IsEmpty() const
        {
            return m_start == m_end;
        }

        inline SlideViewGeneric<T> SubView(i64 start, i64 end)
        {
            return SlideViewGeneric<T>(m_start + start, m_start + end);
        }

        inline uSize Size(){return m_end - m_start;}
        inline SlideViewGeneric<T>& operator++()
        {
            m_start++;
            m_end++;
            return *this;
        }

        inline SlideViewGeneric<T>& operator--()
        {
            m_start--;
            m_end--;
            return *this;
        }

        inline SlideViewGeneric<T>& operator+=(uSize offset)
        {
            m_start += offset;
            m_end += offset;
            return *this;
        }

        inline SlideViewGeneric<T>& operator-=(uSize offset)
        {
            m_start -= offset;
            m_end -= offset;
            return *this;
        }

        inline T& operator*(){return *m_start;}

        inline char operator [](uSize index){return m_start[index];}

        inline bool operator ==(const SlideViewGeneric<T>& other) const
        {
            return m_start == other.m_start && m_end == other.m_end;
        }

        inline bool operator !=(const SlideViewGeneric<T>& other) const
        {
            return m_start != other.m_start || m_end != other.m_end;
        }

    private:
        T* m_start = nullptr;
        T* m_end = nullptr;
    };

    using SlideViewChar = SlideViewGeneric<u8>;
    using SlideViewWChar = SlideViewGeneric<wchar_t>;
    using SlideViewChar32 = SlideViewGeneric<char32_t>;
}