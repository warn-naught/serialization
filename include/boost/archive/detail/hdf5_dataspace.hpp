/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_DATASPACE_HPP
#define HDF5_DATASPACE_HPP

#include <boost/archive/detail/hdf5_object.hpp>

namespace boost {
namespace archive {
namespace detail {

class hdf5_dataset;
class hdf5_annotation;

/*! \brief wrapper around HDF5 dataspace objects
 *
 * Longer description
 *
 */

class hdf5_dataspace
        :
        public hdf5_object
{
public:
    //! Create a new HDF5 dataspace of given size.
    explicit hdf5_dataspace(std::size_t size);

    //! Return dataspace belonging to a given dataset.
    explicit hdf5_dataspace(hdf5_dataset const& dataset);

    //! Return dataspace belonging to a given annotation.
    explicit hdf5_dataspace(hdf5_annotation const& annotation);

    //! Free resources on destruction.
    virtual ~hdf5_dataspace()
    {
        close_without_throwing();
    }

private:
    virtual void close_impl();
};

} } } // end namespace boost::archive::detail

#endif // HDF5_DATASPACE_HPP


