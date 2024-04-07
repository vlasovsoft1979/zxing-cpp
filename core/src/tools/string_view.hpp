#pragma once

#if __cplusplus >= 201703L

#include <string_view>

#else

#include <stddef.h>
#include <string>
#include <stdexcept>

namespace std {

template <class CharT, class Traits = std::char_traits<CharT>>
class basic_string_view
{
public:
    typedef Traits traits_type;
    typedef CharT value_type;
    typedef CharT* pointer;
    typedef const CharT* const_pointer;
    typedef CharT& reference;
    typedef const CharT& const_reference;
    typedef const CharT* const_iterator;
    typedef const_iterator iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const_reverse_iterator reverse_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    static constexpr size_type npos = size_type(-1);

    basic_string_view() noexcept : data_(nullptr), len_(0) 
    {}
    basic_string_view(const_pointer str, size_type len)
        : data_(str), len_(len) 
    {}
    basic_string_view(const_pointer str)
        : data_(str), len_(internal_strlen(str)) 
    {}
    basic_string_view(const std::basic_string<CharT, Traits>& str)
        : data_(str.data()), len_(str.size()) 
    {}

    size_type size() const { return len_; }
	size_type length() const { return len_; }
    const_pointer data() const { return data_; }
    bool empty() const { return len_ == 0; }

    void remove_prefix(size_type n) {
        data_ = data_ + n;
        len_ -= n;
    }
    
    void remove_suffix(size_type n) 
    { 
        len_ -= n; 
    }

    friend inline bool operator==(basic_string_view a, basic_string_view b)
    {
        return a.compare(b) == 0;
    }

    // Iterator support.
    constexpr const_iterator begin() const noexcept { return data_; }
    constexpr const_iterator cbegin() const noexcept { return begin(); }
    constexpr const_iterator end() const noexcept { return data_ + len_; }
    constexpr const_iterator cend() const noexcept { return end(); }

    // Element access.
    const_reference operator[](size_type pos) const {
        return data_[pos];
    }
    const_reference at(size_type pos) const 
    {
        if (pos > len_) 
        {
            throw std::out_of_range("Out of range");
        }
        return this->operator[](pos);
    }
    constexpr const_reference front() const { return data_[0]; }
    constexpr const_reference back() const { return data_[len_ - 1]; }

    size_type find(basic_string_view s, size_type pos = 0) const noexcept {
        if (empty() && s.empty() && pos == 0) {
            return 0;
        }
        if (pos > len_ || s.len_ > (len_ - pos)) {
            return npos;
        }
        while (pos + s.len_ <= len_) {
            if (traits_type::compare(data_ + pos, s.data_, s.len_) == 0) {
                return pos;
            }

            pos++;
        }

        return npos;
    }
    size_type find(value_type c, size_type pos = 0) const noexcept {
        return find(basic_string_view(&c, 1), pos);
    }
    size_type find(const_pointer s, size_type pos, size_type n) const {
        return find(basic_string_view(s, n), pos);
    }
    size_type find(const_pointer s, size_type pos = 0) const {
        return find(basic_string_view(s), pos);
    }

    basic_string_view substr(size_type pos = 0, size_type count = npos) const {
        if (pos > len_) {
            throw std::out_of_range("Out of range");
        }

        const size_type rcount = std::min(count, len_ - pos);
        if (rcount > 0) {
            return basic_string_view(data_ + pos, rcount);
        }
        return basic_string_view();
    }

    int compare(basic_string_view s) const noexcept {
        const size_t rlen = std::min(len_, s.len_);
        const int comparison = traits_type::compare(data_, s.data_, rlen);
        if (comparison != 0) return comparison;
        if (len_ == s.len_) return 0;
        return len_ < s.len_ ? -1 : 1;
    }

    int compare( size_type pos1, size_type count1, basic_string_view v ) const
    {
        return substr(pos1, count1).compare(v);
    }

private:
    static size_type internal_strlen(const_pointer str) {
        return str ? traits_type::length(str) : 0;
    }

private:
    const_pointer data_;
    size_type len_;
};

typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;

inline std::string& operator += (std::string& str, const std::string_view& sv)
{
    str.insert(str.end(), sv.cbegin(), sv.cend());
    return str;
}

}

#endif
