#pragma once

#include <map>

using Edge = std::pair< size_t, size_t >;

struct EdgeW
{
    size_t v1 = 0;
    size_t v2 = 0;
    int32_t w = 0;
    bool operator < ( const EdgeW& rhs ) const
    {
        return std::make_tuple( v1, v2, w ) < std::make_tuple( rhs.v1, rhs.v2, rhs.w );
    }
};