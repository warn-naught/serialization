/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_GROUP_HPP
#define HDF5_GROUP_HPP

#include <string>
#include <boost/archive/detail/hdf5_annotatable_object.hpp>

namespace boost {
namespace archive {
namespace detail {

class hdf5_file;

/*! \brief wrapper around an HDF5 group object
 *
 * Longer description
 *
 */

class hdf5_group
        :
        public hdf5_annotatable_object
{
public:
    /*! \brief Create or open HDF5 group in the given file for writing.
     *
     * The given path must be an absolute path. All intermediate path elements
     * must already exist. If name does not exist at the given path, create a
     * group of this name there. If it exists and is not a group, throw
     * exception.
     */
    hdf5_group
    (
        hdf5_file& file,
        std::string const& path
    );


    /*! \brief Open HDF5 group in the given file for reading.
     *
     * The given path must be an absolute path. All path elements
     * must already exist. If no group exists at the given path, throw
     * exception.
     */
    hdf5_group
    (
        hdf5_file const& file,
        std::string const& path
    );


    //! Free resources on destruction.
    virtual ~hdf5_group()
    {
        close_without_throwing();
    }

private:
    std::string path_;

    //! Close the group handle. May throw!
    virtual void close_impl();
};

} } } // end namespace boost::archive::detail

#endif // HDF5_GROUP_HPP


