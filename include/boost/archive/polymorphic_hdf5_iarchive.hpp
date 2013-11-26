/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_POLYMORPHIC_HDF5_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_HDF5_IARCHIVE_HPP

#include <boost/config.hpp>
#include <boost/archive/hdf5_iarchive.hpp>
#include <boost/archive/detail/polymorphic_hdf5_iarchive_route.hpp>

namespace boost {
namespace archive {

typedef detail::polymorphic_hdf5_iarchive_route
<
    hdf5_iarchive_impl<naked_hdf5_iarchive> 
> polymorphic_hdf5_iarchive;

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_hdf5_iarchive
)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(
    boost::archive::polymorphic_hdf5_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_HDF5_IARCHIVE_HPP
