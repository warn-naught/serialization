/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_HDF5_MEMORY_BUFFER_HPP
#define BOOST_ARCHIVE_HDF5_MEMORY_BUFFER_HPP

#include <boost/scoped_array.hpp>

namespace boost {
namespace archive {

//! simple abstraction for a dynamically allocated location of memory

class hdf5_memory_buffer
{
public:
    explicit hdf5_memory_buffer(size_t len);

    void * ptr() const
    {
        return buffer_.get();
    }

    size_t len() const
    {
        return len_;
    }

private:
    scoped_array<char> buffer_;
    size_t len_;
};

} } // end namespace boost::archive

#endif // BOOST_ARCHIVE_HDF5_MEMORY_BUFFER_HPP
