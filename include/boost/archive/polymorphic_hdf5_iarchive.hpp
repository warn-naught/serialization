/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_POLYMORPHIC_HDF5_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_HDF5_IARCHIVE_HPP

#include <boost/config.hpp>
#include <boost/archive/hdf5_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

namespace boost {
namespace archive {
class polymorphic_hdf5_iarchive : 
    public detail::polymorphic_iarchive_route<naked_hdf5_iarchive>
{
public:
    polymorphic_hdf5_iarchive(std::string const& fn, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<naked_hdf5_iarchive>(fn, flags)
    {}
    ~polymorphic_hdf5_iarchive(){}
};
} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_hdf5_iarchive)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::polymorphic_hdf5_iarchive)

#endif // BOOST_ARCHIVE_POLYMORPHIC_HDF5_IARCHIVE_HPP
