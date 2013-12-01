/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <sstream>
#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/detail/hdf5_common_archive.hpp>

namespace boost {
namespace archive {
namespace detail {

char const* const hdf5_common_archive::data_dir = "/<data>";
char const* const
hdf5_common_archive::tracked_objects_dir = "/<tracked_objects>";
char const* const hdf5_common_archive::tree_dir = "/<tree>";

std::string const
hdf5_common_archive::create_object_data_path(std::size_t count)
{
    std::ostringstream ss;
    ss << data_dir << "/" << count;
    return ss.str();
}

std::string const
hdf5_common_archive::create_tracked_objects_path(unsigned int count)
{
    std::ostringstream ss;
    ss << tracked_objects_dir << "/_o" << count;
    return ss.str();
}

} } } // end namespace boost::archive::detail
