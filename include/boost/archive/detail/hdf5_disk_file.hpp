/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_DETAIL_HDF5_DISK_FILE_HPP
#define BOOST_ARCHIVE_DETAIL_HDF5_DISK_FILE_HPP

#include <string>
#include <boost/archive/detail/hdf5_file.hpp>

namespace boost {
namespace archive {
namespace detail {

/*! \brief wrapper around HDF5 disk file
 *
 * Longer description
 *
 */

class hdf5_disk_file
        :
        public hdf5_file
{
public:
    /*! \brief Open an on-disk HDF5 file. May throw!
     *
     * File must exist already if opened in READ_ONLY mode. If file exists
     * and is opened in WRITE_ONLY, it will be truncated.
     */
    hdf5_disk_file(std::string const& filename, file_mode_t mode);

    //! Free resources on destruction.
    virtual ~hdf5_disk_file()
    {
        close_without_throwing();
    }

    //! Get the HDF5 file name.
    std::string const& get_filename() const;

private:
    std::string filename_;

    //! Close the file handle, flushing all buffers. May throw!
    virtual void close_impl();
};

} } } // end namespace boost::archive::detail

#endif // BOOST_ARCHIVE_DETAIL_HDF5_DISK_FILE_HPP
