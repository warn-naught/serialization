/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef POLYMORPHIC_HDF5_IARCHIVE_HPP
#define POLYMORPHIC_HDF5_IARCHIVE_HPP

#include <boost/config.hpp>
#include "archive/hdf5_iarchive.hpp"
#include "archive/detail/polymorphic_hdf5_iarchive_route.hpp"

namespace archive {

typedef archive::detail::polymorphic_iarchive_route
<
    hdf5_iarchive_impl<naked_hdf5_iarchive> 
> polymorphic_hdf5_iarchive;

} // end namespace archive

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    ::archive::polymorphic_hdf5_iarchive
)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(
    ::archive::polymorphic_hdf5_iarchive
)

#endif // POLYMORPHIC_HDF5_IARCHIVE_HPP
