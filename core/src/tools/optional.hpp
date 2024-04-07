#pragma once

#if __cplusplus >= 201703L

#include <optional>

#else 

namespace std {

template<class T> struct optional 
{
    union { char dummy_; T val_; };
    bool engaged_;
    optional() : dummy_(0), engaged_(false) {}
    optional(const T& t) : val_(t), engaged_(true) {}
    ~optional() {
        if (engaged_) val_.~T();
    }
    explicit operator bool() const
    {
        return engaged_;
    }
    T& operator*() {
        return val_;
    }
    const T& operator*() const {
        return val_;
    }
    T* operator->() {
        return &val_;
    }
    const T* operator->() const {
        return &val_;
    }
};

}

#endif
