#pragma once

#include <algorithm>

#if __cplusplus < 201703L

namespace std {

template< class T >
const T& clamp( const T& v, const T& lo, const T& hi )
{
    return std::min(hi, std::max(v, lo));
}

}

#endif