/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_POLYMORPHIC_HDF5_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_HDF5_OARCHIVE_HPP

#include <boost/config.hpp>
#include <boost/archive/hdf5_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

typedef detail::polymorphic_oarchive_route
<
    hdf5_oarchive_impl<naked_hdf5_oarchive> 
> polymorphic_hdf5_oarchive;

} // end namespace archive
} // end namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_hdf5_oarchive)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::polymorphic_hdf5_oarchive)

#endif // BOOST_ARCHIVE_POLYMORPHIC_HDF5_OARCHIVE_HPP
