/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_DETAIL_HDF5_MEMORY_FILE_HPP
#define BOOST_ARCHIVE_DETAIL_HDF5_MEMORY_FILE_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/archive/hdf5_memory_buffer.hpp>
#include <boost/archive/detail/hdf5_file.hpp>

namespace boost {
namespace archive {
namespace detail {

/*! \brief wrapper around in-memory HDF5 file
 *
 * Longer description
 *
 */

class hdf5_memory_file
        :
        public hdf5_file
{
public:
    //! \brief Open an HDF5 memory file. May throw!
    hdf5_memory_file(shared_ptr<hdf5_memory_buffer> buffer, file_mode_t mode);

    //! Free resources on destruction.
    virtual ~hdf5_memory_file()
    {
        close_without_throwing();
    }

private:
    shared_ptr<hdf5_memory_buffer> buffer_;

    //! Close the file handle, flushing all buffers. May throw!
    virtual void close_impl();
};

} } } // end namespace boost::archive::detail

#endif // BOOST_ARCHIVE_DETAIL_HDF5_MEMORY_FILE_HPP


