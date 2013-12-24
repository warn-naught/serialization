/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <H5Apublic.h>
#include <H5Spublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_annotatable_object.hpp>
#include <boost/archive/detail/hdf5_dataspace.hpp>
#include <boost/archive/detail/hdf5_datatype.hpp>
#include <boost/archive/detail/hdf5_annotation.hpp>

namespace boost {
namespace archive {
namespace detail {

hdf5_annotation::hdf5_annotation
(
    hdf5_annotatable_object& object,
    std::string const& key,
    hdf5_datatype const& datatype,
    hdf5_dataspace const& dataspace
)
    :
      key_(key)
{
    // first check if given attribute is already present.
    htri_t attribute_status = H5Aexists(object.get_id(), key.c_str());
    if(attribute_status < 0) { // error accessing the object attributes
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_attribute_access_error
            )
        );
    }
    if(attribute_status > 0) { // attribute already present. Delete it!
        herr_t status = H5Adelete(object.get_id(), key.c_str());
        if(status < 0) {
            boost::serialization::throw_exception(
                hdf5_archive_exception(
                    hdf5_archive_exception::hdf5_archive_attribute_write_error
                )
            );
        }
    }

    // Create an attribute for key and value.
    set_id(
        H5Acreate2(
            object.get_id(),
            key.c_str(),
            datatype.get_id(),
            dataspace.get_id(),
            H5P_DEFAULT,
            H5P_DEFAULT
        )
    );
    if(get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_attribute_create_error,
                key.c_str()
            )
        );
    }
}


hdf5_annotation::hdf5_annotation
(
    hdf5_annotatable_object const& object,
    std::string const& key
)
    :
      key_(key)
{
    // Open the attribute.
    set_id(
        H5Aopen(object.get_id(), key.c_str(), H5P_DEFAULT)
    );
    if(get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_attribute_access_error,
                key.c_str()
            )
        );
    }
}


void hdf5_annotation::write
(
    hdf5_datatype const& value_type,
    void const* value
)
{
    herr_t status = H5Awrite(get_id(), value_type.get_id(), value);
    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_attribute_write_error,
                key_.c_str()
            )
        );
    }
}


void hdf5_annotation::read(const hdf5_datatype &value_type, void *value) const
{

    // attempt to read attribute value
    herr_t status = H5Aread(get_id(), value_type.get_id(), value);
    if(status < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_attribute_read_error,
                key_.c_str()
            )
        );
    }
}


void hdf5_annotation::close_impl()
{
    if(H5Aclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_annotation_close_error,
                key_.c_str()
            )
        );
    }
}

} } } // end namespace boost::archive::detail


