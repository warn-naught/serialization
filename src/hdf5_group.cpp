/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <H5Gpublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_file.hpp>
#include <boost/archive/detail/hdf5_group.hpp>

//byWarn
#include <H5Ppublic.h>

namespace boost {
namespace archive {
namespace detail {

hdf5_group::hdf5_group
(
    hdf5_file& file,
    std::string const& path
)
    :
      path_(path)
{
    // Check if name exists in this file.
    htri_t status = H5Lexists(file.get_id(), path.c_str(), H5P_DEFAULT);

    // For some reason this does not work with the root group itself.
    if(path == "/")
        status = 1;

    if(status > 0) { // Full path exists.
        // Attempt to open it as a group.
        set_id(H5Gopen2(file.get_id(), path.c_str(), H5P_DEFAULT));
        if(get_id() < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_group_access_error,
                    path.c_str()
                )
            );
        }
    }
    else if(status == 0){ // Final link in path does not exist.
        // Create the group.
        set_id(H5Gcreate2(
                   file.get_id(),
                   path.c_str(),
                   H5P_DEFAULT,
                   H5P_DEFAULT,
                   H5P_DEFAULT
                )
        );
        if(get_id() < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_group_create_error,
                    path.c_str()
                )
            );
        }
    }
    else { // intermediate link does not exist, or other error
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_bad_path_error,
                path.c_str()
            )
        );
    }
}


hdf5_group::hdf5_group
(
    hdf5_file const& file,
    std::string const& path
)
    :
      path_(path)
{
    // Check if name exists in this file.
    htri_t status = H5Lexists(file.get_id(), path.c_str(), H5P_DEFAULT);

    // For some reason this does not work with the root group itself.
    if(path == "/")
        status = 1;
  
    if(status > 0) { // Full path exists.
        // Attempt to open it as a group.
        set_id(H5Gopen2(file.get_id(), path.c_str(), H5P_DEFAULT));
        if(get_id() < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_group_access_error,
                    path.c_str()
                )
            );
        }
    }
    else { // path does not exist, or other error
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_bad_path_error,
                path.c_str()
            )
        );
    }
}


void hdf5_group::close_impl()
{
    if(H5Gclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_group_close_error,
                path_.c_str()
            )
        );
    }
}

} } } // end namespace boost::archive::detail

