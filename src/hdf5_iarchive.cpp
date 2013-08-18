/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include "archive/hdf5_iarchive.hpp"
#include <boost/archive/detail/archive_serializer_map.hpp>

// explicitly instantiate for this type of archive
#include <boost/archive/impl/archive_serializer_map.ipp>
#include "archive/impl/hdf5_iarchive_impl.ipp"

namespace boost {
namespace archive {

template class detail::archive_serializer_map< ::archive::naked_hdf5_iarchive>;
template class detail::archive_serializer_map< ::archive::hdf5_iarchive>;

} // namespace archive
} // namespace boost

namespace archive {

template class hdf5_iarchive_impl<naked_hdf5_iarchive> ;
template class hdf5_iarchive_impl<hdf5_iarchive> ;

} // namespace archive

