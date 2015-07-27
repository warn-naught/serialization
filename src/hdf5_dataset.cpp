/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <H5Dpublic.h>
#include <H5Spublic.h>
#include <H5Lpublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_file.hpp>
#include <boost/archive/detail/hdf5_datatype.hpp>
#include <boost/archive/detail/hdf5_dataspace.hpp>
#include <boost/archive/detail/hdf5_dataset.hpp>

//byWarn
typedef int hid_t;
#define H5P_DEFAULT     (hid_t)0

namespace boost {
namespace archive {
namespace detail {

hdf5_dataset::hdf5_dataset
(
    hdf5_file &file,
    std::string const& path,
    hdf5_datatype const& datatype,
    hdf5_dataspace const& dataspace
)
    :
      path_(path)
{
    // Check if name exists in this file.
    htri_t status = H5Lexists(file.get_id(), path.c_str(), H5P_DEFAULT);
    if(status > 0) { // Full path exists.
        // Attempt to open it as a dataset
        set_id(H5Dopen2(file.get_id(), path.c_str(), H5P_DEFAULT));
        if(get_id() < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_dataset_access_error,
                    path.c_str()
                )
            );
        }
    }
    else if(status == 0){ // Final link in path does not exist.
        // Create the dataset.
        set_id(H5Dcreate2(
                   file.get_id(),
                   path.c_str(),
                   datatype.get_id(),
                   dataspace.get_id(),
                   H5P_DEFAULT,
                   H5P_DEFAULT,
                   H5P_DEFAULT
                )
        );
        if(get_id() < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_dataset_create_error,
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


hdf5_dataset::hdf5_dataset(
    hdf5_file const& file,
    std::string const& path
)
    :
      path_(path)
{
    // Check if name exists in this file.
    htri_t status = H5Lexists(file.get_id(), path.c_str(), H5P_DEFAULT);
    if(status > 0) { // Full path exists.
        // Attempt to open it as a dataset
        set_id(H5Dopen2(file.get_id(), path.c_str(), H5P_DEFAULT));
        if(get_id() < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_dataset_access_error,
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


void hdf5_dataset::write(hdf5_datatype const& type, void const* buffer)
{
    herr_t status =
            H5Dwrite(
                get_id(),
                type.get_id(),
                H5S_ALL,
                H5S_ALL,
                H5P_DEFAULT,
                buffer
            );

    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataset_write_error
            )
        );
    }
}


void hdf5_dataset::read(hdf5_datatype const& type, void* buffer)
{
    herr_t status =
            H5Dread(
                get_id(),
                type.get_id(),
                H5S_ALL,
                H5S_ALL,
                H5P_DEFAULT,
                buffer
            );

    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataset_read_error
            )
        );
    }
}


void hdf5_dataset::close_impl()
{
    if(H5Dclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataset_close_error,
                path_.c_str()
            )
        );
    }
}


} } } // end namespace boost::archive::detail
