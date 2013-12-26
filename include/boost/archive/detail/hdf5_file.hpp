/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_DETAIL_HDF5_FILE_HPP
#define BOOST_ARCHIVE_DETAIL_HDF5_FILE_HPP

#include <string>
#include <boost/archive/detail/hdf5_annotatable_object.hpp>

namespace boost {
namespace archive {
namespace detail {

/*! \brief wrapper around HDF5 file
 *
 * Longer description
 *
 */

class hdf5_file
        :
        public hdf5_annotatable_object
{
public:
    //! File opening modes
    enum file_mode_t
    {
        READ_ONLY,
        READ_WRITE
    };

    //! Open an HDF5 file. May throw!
    hdf5_file(hid_t id);

    //! Create a hard link to a given target object. May throw!
    //! All paths must be absolute paths from the file root group.
    void create_hdf5_hard_link
    (
        std::string const& source_path,
        std::string const& target_path
    );

    //! Create a soft link to a given target object. May throw!
    //! All paths must be absolute paths from the file root group.
    void create_hdf5_soft_link
    (
        std::string const& source_path,
        std::string const& target_path
    );

private:
    //! Close the file handle, flushing all buffers. May throw!
    virtual void close_impl() = 0;
};

} } } // end namespace boost::archive::detail

#endif // BOOST_ARCHIVE_DETAIL_HDF5_FILE_HPP


