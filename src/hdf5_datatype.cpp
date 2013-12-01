/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <H5Dpublic.h>
#include <H5Apublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_annotation.hpp>
#include <boost/archive/detail/hdf5_dataset.hpp>
#include <boost/archive/detail/hdf5_datatype.hpp>
#include <boost/archive/detail/hdf5_dataspace.hpp>

namespace boost {
namespace archive {
namespace detail {

hdf5_datatype::hdf5_datatype(H5T_class_t type_class)
    :
      hdf5_object(),
      type_class_(type_class)
{
    if(type_class == H5T_STRING) { // go for C-style string, special treatment
        set_id(H5Tcopy(H5T_C_S1));
    }
    else
        set_id(H5Tcreate(type_class, 1));

    if(get_id() < 0) { // error occurred
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_create_error
            )
        );
    }
}


hdf5_datatype::hdf5_datatype(hid_t type)
    :
      hdf5_object(type),
      type_class_(H5Tget_class(type))
{
    if(type_class_ == H5T_NO_CLASS) { // error occurred
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_access_error
            )
        );
    }

    set_id(H5Tcopy(type));
    if(get_id() < 0) { // error occurred
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_create_error
            )
        );
    }
}


hdf5_datatype::hdf5_datatype(hdf5_dataset const& dataset)
    :
      hdf5_object(H5Dget_type(dataset.get_id())),
      type_class_(H5Tget_class(get_id()))
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
                hdf5_archive_exception::hdf5_archive_datatype_access_error
            )
        );
    }
}


hdf5_datatype::hdf5_datatype(hdf5_annotation const& annotation)
    :
      hdf5_object(H5Aget_type(annotation.get_id())),
      type_class_(H5Tget_class(get_id()))
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
                hdf5_archive_exception::hdf5_archive_datatype_access_error
            )
        );
    }
}


bool hdf5_datatype::is_variable_length_string() const
{
    htri_t status = H5Tis_variable_str(get_id());
    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_access_error
            )
        );
    }
    else if(status == 0) {
        return false;
    }
    return true;
}


void hdf5_datatype::reclaim_buffer(hdf5_dataspace const& dataspace, void* buffer)
{
    herr_t status = H5Dvlen_reclaim(
        get_id(),
        dataspace.get_id(),
        H5P_DEFAULT,
        buffer
    );
    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_access_error
            )
        );
    }
}


size_t hdf5_datatype::get_size() const
{
    size_t size = H5Tget_size(get_id());
    if(!size) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_access_error
            )
        );
    }
    return size;
}


void hdf5_datatype::resize(std::size_t new_size)
{
    if(H5Tset_size(get_id(), new_size) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_set_size_error
            )
        );
    }
}


void hdf5_datatype::set_encoding(H5T_cset_t encoding)
{
    herr_t status = H5Tset_cset(get_id(), encoding);
    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_set_charset_error
            )
        );
    }

}


void hdf5_datatype::close_impl()
{
    if(H5Tclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_datatype_close_error
            )
        );
    }
}

} } } // end namespace boost::archive::detail


