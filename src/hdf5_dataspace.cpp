/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <H5Spublic.h>
#include <H5Dpublic.h>
#include <H5Apublic.h>
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_dataspace.hpp>
#include <boost/archive/detail/hdf5_dataset.hpp>
#include <boost/archive/detail/hdf5_annotation.hpp>

namespace boost {
namespace archive {
namespace detail {

hdf5_dataspace::hdf5_dataspace(std::size_t size)
    :
      hdf5_object()
{
    if(size == 1) {
        set_id(H5Screate(H5S_SCALAR));
    }
    else {
        hsize_t dims = size;
        set_id(H5Screate_simple(1, &dims, NULL));

    }

    if(get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataspace_create_error
            )
        );
    }
}


hdf5_dataspace::hdf5_dataspace(hdf5_dataset const& dataset)
    :
      hdf5_object(H5Dget_space(dataset.get_id()))
{
    if(dataset.get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataset_access_error
            )
        );
    }
    if(get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataspace_access_error
            )
        );
    }
}


hdf5_dataspace::hdf5_dataspace(hdf5_annotation const& annotation)
    :
      hdf5_object(H5Aget_space(annotation.get_id()))
{
    if(annotation.get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_annotation_access_error
            )
        );
    }
    if(get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataspace_access_error
            )
        );
    }
}


void hdf5_dataspace::close_impl()
{
    if(H5Sclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_dataspace_close_error
            )
        );
    }
}

} } } // end namespace boost::archive::detail

