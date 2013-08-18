/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_ANNOTATION_HPP
#define HDF5_ANNOTATION_HPP

#include <string>
#include "archive/detail/hdf5_object.hpp"

namespace archive {
namespace detail {

class hdf5_annotatable_object;
class hdf5_datatype;
class hdf5_dataspace;

/*! \brief wrapper around HDF5 annotations
 *
 * Longer description
 *
 */

class hdf5_annotation
        :
        public hdf5_object
{
public:
    //! Create a new annotation on an annotatable object.
    hdf5_annotation
    (
        hdf5_annotatable_object& object,
        std::string const& key,
        hdf5_datatype const& datatype,
        hdf5_dataspace const& dataspace
    );

    //! Open a present annotation for reading
    hdf5_annotation
    (
        hdf5_annotatable_object const& object,
        std::string const& key
    );

    //! Write to annotation object. May throw!
    void write
    (
        hdf5_datatype const& type,
        void const* value
    );

    //! Read from annotation object. May throw!
    void read
    (
        hdf5_datatype const& value_type,
        void* value
    ) const;

    //! Free resources on destruction.
    virtual ~hdf5_annotation()
    {
        close_without_throwing();
    }

private:
    std::string key_;

    //! Close the datatype handle, if necessary. May throw!
    virtual void close_impl();

};

} } // end namespace archive::detail

#endif // HDF5_ANNOTATION_HPP


