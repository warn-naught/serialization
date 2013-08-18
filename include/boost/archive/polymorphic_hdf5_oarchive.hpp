/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef POLYMORPHIC_HDF5_OARCHIVE_HPP
#define POLYMORPHIC_HDF5_OARCHIVE_HPP

#include <boost/config.hpp>
#include "archive/hdf5_oarchive.hpp"
#include "archive/detail/polymorphic_hdf5_oarchive_route.hpp"

namespace archive {

typedef archive::detail::polymorphic_oarchive_route
<
    hdf5_oarchive_impl<naked_hdf5_oarchive> 
> polymorphic_hdf5_oarchive;

} // end namespace archive

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    ::archive::polymorphic_hdf5_oarchive
)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(
    ::archive::polymorphic_hdf5_oarchive
)

#endif // POLYMORPHIC_HDF5_OARCHIVE_HPP
