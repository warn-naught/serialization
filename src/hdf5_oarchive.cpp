/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/hdf5_oarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>

// explicitly instantiate for this type of archive
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/hdf5_oarchive_impl.ipp>

namespace boost {
namespace archive {

template class detail::archive_serializer_map<hdf5_oarchive>;

// explicit instantiation of the implementation:
template class hdf5_oarchive_impl<hdf5_oarchive> ;

} // namespace archive
} // namespace boost
