/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_DATATYPE_HPP
#define HDF5_DATATYPE_HPP

#include <H5Tpublic.h>
#include <boost/archive/detail/hdf5_object.hpp>

namespace boost {
namespace archive {
namespace detail {

class hdf5_dataspace;
class hdf5_dataset;
class hdf5_annotation;

/*! \brief wrapper around and HDF5 datatype object
 *
 * Longer description
 *
 */

class hdf5_datatype
        :
        public hdf5_object
{
public:
    //! Create a new HDF5 datatype for H5T_STRING or H5T_OPAQUE.
    //! Size defaults to 1, but can be resized (see below).
    explicit hdf5_datatype(H5T_class_t type_class);

    //! Create a copy of the given HDF5 datatype id.
    explicit hdf5_datatype(hid_t type);

    //! Return the datatype belonging to a given HDF5 dataset object.
    explicit hdf5_datatype(hdf5_dataset const& dataset);

    //! Return the datatype belonging to a given HDF5 annotation object.
    explicit hdf5_datatype(hdf5_annotation const& annotation);

    //! Resize datatype. May throw!
    void resize(std::size_t new_size);

    //! Return size of datatype. May throw!
    size_t get_size() const;

    //! Set encoding for strings. May throw!
    void set_encoding(H5T_cset_t encoding);

    //! Check if datatype represents a variable length string. May throw!
    bool is_variable_length_string() const;

    //! Release resources for variable length strings. May throw!
    void reclaim_buffer(hdf5_dataspace const& dataspace, void* buffer);

    //! Free resources on destruction.
    virtual ~hdf5_datatype()
    {
        close_without_throwing();
    }

private:
    H5T_class_t type_class_;

    //! Close the datatype handle, if necessary. May throw!
    virtual void close_impl();
};

} } } // end namespace boost::archive::detail

#endif // HDF5_DATATYPE_HPP


