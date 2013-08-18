/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_DATASET_HPP
#define HDF5_DATASET_HPP

#include <string>
#include "archive/detail/hdf5_annotatable_object.hpp"

namespace archive {
namespace detail {

/*! \brief wrapper around HDF5 datasets
 *
 * Longer description
 *
 */

class hdf5_file;
class hdf5_datatype;
class hdf5_dataspace;

class hdf5_dataset
        :
        public hdf5_annotatable_object
{
public:
    /*! \brief Create or open HDF5 dataset in the given file for writing.
     *
     * The given path must be an absolute path. All intermediate path elements
     * must already exist. If name does not exist at the given path, create a
     * dataset of this name there. If it exists and is not a dataset, throw
     * exception.
     */
    hdf5_dataset
    (
        hdf5_file& file,
        std::string const& path,
        hdf5_datatype const& datatype,
        hdf5_dataspace const& dataspace
    );

    /*! \brief Open HDF5 dataset in the given file for reading.
     *
     * The given path must be an absolute path. All path elements
     * must already exist. If no dataset exists at the given path, throw
     * exception.
     */
    hdf5_dataset
    (
        hdf5_file const& file,
        std::string const& path
    );

    //! Write to dataset.
    void write(hdf5_datatype const& type, void const* buffer);

    //! Read from dataset.
    void read(hdf5_datatype const& type, void* buffer);

    //! Free resources on destruction.
    virtual ~hdf5_dataset()
    {
        close_without_throwing();
    }

private:
    std::string path_;

    //! Close the dataset handle. May throw!
    virtual void close_impl();
};

} } // end namespace archive::detail

#endif // HDF5_DATASET_HPP


