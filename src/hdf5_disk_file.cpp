/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <H5Fpublic.h>
#include <H5Lpublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_disk_file.hpp>

namespace boost {
namespace archive {
namespace detail {

hdf5_disk_file::hdf5_disk_file(const std::string &filename, file_mode_t mode) :
    hdf5_file(
        mode == READ_ONLY ?
            H5Fopen(
                filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT
            )
            :
            H5Fcreate(
                filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT
            )
    ),
    filename_(filename)
{
    if(filename.empty() || get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                mode == READ_ONLY ?
                hdf5_archive_exception::hdf5_archive_file_access_error
                :
                hdf5_archive_exception::hdf5_archive_file_create_error,
                filename.c_str()
            )
        );
    }
}


std::string const& hdf5_disk_file::get_filename() const
{
    return filename_;
}


void hdf5_disk_file::close_impl()
{
    if(H5Fclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_file_close_error,
                filename_.c_str()
            )
        );
    }
}


} } } // end namespace boost::archive::detail
