/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_HDF5_OARCHIVE_HPP
#define BOOST_ARCHIVE_HDF5_OARCHIVE_HPP

#include <string>
#include <boost/config.hpp>
#include <boost/archive/hdf5_oarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { 
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derive from hdf5_oarchive_impl instead.  This will
// preserve correct static polymorphism.

class hdf5_oarchive
    :
    public hdf5_oarchive_impl<hdf5_oarchive>
{
public:
    hdf5_oarchive(std::string const & hdf5_filename, unsigned int flags = 0)
        :
        hdf5_oarchive_impl<hdf5_oarchive>(hdf5_filename, flags)
    {}

    hdf5_oarchive(shared_ptr<hdf5_memory_buffer> buffer, 
                  unsigned int flags = 0)
        :
        hdf5_oarchive_impl<hdf5_oarchive>(buffer, flags)
    {}

    ~hdf5_oarchive()
    {}
};

typedef hdf5_oarchive naked_hdf5_oarchive;

} } // end namespace boost::archive

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::hdf5_oarchive)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::hdf5_oarchive)

#endif // BOOST_ARCHIVE_HDF5_OARCHIVE_HPP
