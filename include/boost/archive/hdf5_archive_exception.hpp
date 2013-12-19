/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_HDF5_ARCHIVE_EXCEPTION_HPP
#define BOOST_ARCHIVE_HDF5_ARCHIVE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/archive/archive_exception.hpp>

namespace boost {
namespace archive {

// exceptions thrown by hdf5 archives
class hdf5_archive_exception
    :
    public virtual boost::archive::archive_exception
{
public:
    typedef enum {
        hdf5_archive_identifier_access_error,
        hdf5_archive_file_create_error,
        hdf5_archive_file_access_error,
        hdf5_archive_file_close_error,
        hdf5_archive_bad_path_error,
        hdf5_archive_dataspace_create_error,
        hdf5_archive_dataspace_access_error,
        hdf5_archive_dataspace_close_error,
        hdf5_archive_datatype_create_error,
        hdf5_archive_datatype_access_error,
        hdf5_archive_datatype_close_error,
        hdf5_archive_datatype_set_size_error,
        hdf5_archive_datatype_set_charset_error,
        hdf5_archive_dataset_create_error,
        hdf5_archive_dataset_access_error,
        hdf5_archive_dataset_write_error,
        hdf5_archive_dataset_read_error,
        hdf5_archive_dataset_close_error,
        hdf5_archive_attribute_create_error,
        hdf5_archive_attribute_access_error,
        hdf5_archive_attribute_read_error,
        hdf5_archive_attribute_write_error,
        hdf5_archive_attribute_close_error,
        hdf5_archive_group_create_error,
        hdf5_archive_group_access_error,
        hdf5_archive_group_close_error,
        hdf5_archive_link_create_error,
        hdf5_archive_link_access_error,
        hdf5_archive_annotation_create_error,
        hdf5_archive_annotation_access_error,
        hdf5_archive_annotation_close_error
    } exception_code;


    hdf5_archive_exception
    (
        exception_code c,
        const char *e1 = NULL,
        const char *e2 = NULL
    );
};

} } // end namespace boost::archive

#endif // BOOST_ARCHIVE_HDF5_ARCHIVE_EXCEPTION_HPP
