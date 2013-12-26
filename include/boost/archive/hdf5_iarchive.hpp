/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_HDF5_IARCHIVE_HPP
#define BOOST_ARCHIVE_HDF5_IARCHIVE_HPP

#include <string>
#include <boost/archive/hdf5_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {

// do not derive from the classes below.  If you want to extend this functionality
// via inheritance, derive from hdf5_iarchive_impl instead.  This will
// preserve correct static polymorphism.

// same as hdf5_iarchive below - without the shared_ptr_helper
class naked_hdf5_iarchive :
    public hdf5_iarchive_impl<naked_hdf5_iarchive>
{
public:
    naked_hdf5_iarchive
    (
            std::string const& hdf5_filename,
            unsigned int flags = 0
    )
        :
        hdf5_iarchive_impl<naked_hdf5_iarchive>(
            hdf5_filename,
            flags
        )
    {}


    naked_hdf5_iarchive
    (
        shared_ptr<hdf5_memory_buffer> buffer,
        unsigned int flags = 0
    )
        :
        hdf5_iarchive_impl<naked_hdf5_iarchive>(
            buffer,
            flags
        )
    {}

    ~naked_hdf5_iarchive()
    {}
};

} } // end namespace boost::archive

// note special treatment of shared_ptr. This type needs a special
// structure associated with every archive.  We created a "mix-in"
// class to provide this functionality.  Since shared_ptr holds a
// special esteem in the boost library - we included it here by default.
#include <boost/archive/shared_ptr_helper.hpp>

namespace boost {
namespace archive {

class hdf5_iarchive :
        public hdf5_iarchive_impl<hdf5_iarchive>,
        public boost::archive::detail::shared_ptr_helper
{
public:
    hdf5_iarchive(std::string const& hdf5_filename, unsigned int flags = 0)
        :
        hdf5_iarchive_impl<hdf5_iarchive>(hdf5_filename, flags)
    {}

    hdf5_iarchive(shared_ptr<hdf5_memory_buffer> buffer, 
    unsigned int flags = 0)
        :
        hdf5_iarchive_impl<hdf5_iarchive>(buffer, flags)
    {}

    ~hdf5_iarchive()
    {}
};

} } // end namespace boost::archive

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::hdf5_iarchive)
// make array optimization possible
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::hdf5_iarchive)

#endif // BOOST_ARCHIVE_HDF5_IARCHIVE_HPP


