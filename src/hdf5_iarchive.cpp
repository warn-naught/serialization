/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#define BOOST_ARCHIVE_SOURCE  
#include <boost/archive/hdf5_iarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>

// explicitly instantiate for this type of archive
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/hdf5_iarchive_impl.ipp>

namespace boost {
namespace archive {

template class 
detail::archive_serializer_map<naked_hdf5_iarchive>;
template class 
detail::archive_serializer_map<hdf5_iarchive>;
template class hdf5_iarchive_impl<naked_hdf5_iarchive> ;
template class hdf5_iarchive_impl<hdf5_iarchive> ;

} // namespace archive
} // namespace boost
