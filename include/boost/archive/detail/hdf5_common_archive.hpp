/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_COMMON_ARCHIVE_HPP
#define HDF5_COMMON_ARCHIVE_HPP

#include <string>

namespace archive {
namespace detail {

/*! \brief code common to both input and output HDF5 archive types
 *
 * Longer description
 *
 */

class hdf5_common_archive
{
protected:
    // base directory for flat data list
    static char const* const data_dir;

    // base directory for tracked object list
    static char const* const tracked_objects_dir;

    // base directory for object hierarchy tree
    static char const* const tree_dir;

    // create a path to given object dataset in the flat data list.
    std::string const create_object_data_path(std::size_t count);

    // create a path to given group in the tracked objects list.
    std::string const create_tracked_objects_path(unsigned int count);

private:
    
};

} } // end namespace archive::detail

#endif // HDF5_COMMON_ARCHIVE_HPP


