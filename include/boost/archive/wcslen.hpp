#ifndef BOOST_ARCHIVE_WCSLEN_HPP
#define BOOST_ARCHIVE_WCSLEN_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// wcslen.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#ifndef BOOST_NO_CWCHAR

#include <cwchar>
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::wcslen; }
#endif

#else

namespace std {
inline size_t wcslen(const wchar_t * ws)
{
    const wchar_t * eows = ws;
    while(* eows != 0)
        ++eows;
    return eows - ws;
}
} // namespace std

#endif //BOOST_NO_CWCHAR

#endif //BOOST_ARCHIVE_WCSLEN_HPP
