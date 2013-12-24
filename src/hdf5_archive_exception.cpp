/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/hdf5_archive_exception.hpp>

namespace boost {
namespace archive {

hdf5_archive_exception::hdf5_archive_exception
(
    exception_code c,
    const char * e1,
    const char * e2
)
    :
    archive_exception
    (
        boost::archive::archive_exception::other_exception,
        e1,
        e2
    )
{
    switch(c){
    case hdf5_archive_identifier_access_error:
        append(0, "could not determine if identifier was valid");
        break;
    case hdf5_archive_file_create_error:
        append(0, "error while creating HDF5 file");
        break;
    case hdf5_archive_file_access_error:
        append(0, "error while accessing HDF5 file");
        break;
    case hdf5_archive_file_close_error:
        append(0, "error while closing HDF5 file");
        break;
    case hdf5_archive_bad_path_error:
        append(0, "error while following path");
        break;
    case hdf5_archive_dataspace_create_error:
        append(0, "error while creating HDF5 dataspace");
        break;
    case hdf5_archive_dataspace_access_error:
        append(0, "error while accessing HDF5 dataspace");
        break;
    case hdf5_archive_dataspace_close_error:
        append(0, "error while closing HDF5 dataspace");
        break;
    case hdf5_archive_dataset_create_error:
        append(0, "error while creating HDF5 dataset");
        break;
    case hdf5_archive_dataset_access_error:
        append(0, "error while accessing HDF5 dataset");
        break;
    case hdf5_archive_dataset_write_error:
        append(0, "error while writing to HDF5 dataset");
        break;
    case hdf5_archive_dataset_read_error:
        append(0, "error while reading from HDF5 dataset");
        break;
    case hdf5_archive_dataset_close_error:
        append(0, "error while closing HDF5 dataset");
        break;
    case hdf5_archive_attribute_create_error:
        append(0, "error while creating HDF5 attribute");
        break;
    case hdf5_archive_attribute_close_error:
        append(0, "error while closing HDF5 attribute");
        break;
    case hdf5_archive_attribute_access_error:
        append(0, "error while accessing HDF5 attribute");
        break;
    case hdf5_archive_attribute_read_error:
        append(0, "error while reading HDF5 attribute");
        break;
    case hdf5_archive_attribute_write_error:
        append(0, "error while writing HDF5 attribute");
        break;
    case hdf5_archive_datatype_create_error:
        append(0, "error while creating HDF5 datatype");
        break;
    case hdf5_archive_datatype_access_error:
        append(0, "error while opening HDF5 datatype");
        break;
    case hdf5_archive_datatype_set_size_error:
        append(0, "error while setting HDF5 datatype size");
        break;
    case hdf5_archive_datatype_set_charset_error:
        append(0, "error while setting HDF5 datatype character set");
        break;
    case hdf5_archive_datatype_close_error:
        append(0, "error while closing HDF5 datatype");
        break;
    case hdf5_archive_group_create_error:
        append(0, "error while creating HDF5 group");
        break;
    case hdf5_archive_group_access_error:
        append(0, "error while accessing HDF5 group");
        break;
    case hdf5_archive_group_close_error:
        append(0, "error while closing HDF5 group");
        break;
    case hdf5_archive_link_create_error:
        append(0, "error while creating HDF5 link");
        break;
    case hdf5_archive_link_access_error:
        append(0, "error while accessing HDF5 link");
        break;
    case hdf5_archive_annotation_create_error:
        append(0, "error while creating HDF5 annotation");
        break;
    case hdf5_archive_annotation_access_error:
        append(0, "error while accessing HDF5 annotation");
        break;
    case hdf5_archive_annotation_close_error:
        append(0, "error while closing HDF5 annotation");
        break;
    default:
        BOOST_ASSERT(false);
        append(0, "programming error in HDF5 archive");
        break;
    }
}

} } // end namespace boost::archive
