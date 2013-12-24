/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_DETAIL_HDF5_ANNOTATABLE_OBJECT_HPP
#define BOOST_ARCHIVE_DETAIL_HDF5_ANNOTATABLE_OBJECT_HPP

#include <boost/archive/detail/hdf5_object.hpp>

namespace boost {
namespace archive {
namespace detail {

/*! \brief interface to objects that may be provided with annotation
 *
 * Longer description
 *
 */

class hdf5_annotatable_object
        :
        public hdf5_object
{
public:
    explicit hdf5_annotatable_object(hid_t id = H5I_INVALID_HID)
        :
          hdf5_object(id)
    {}

private:
    virtual void close_impl() = 0;
};

} } } // end namespace boost::archive::detail

#endif // BOOST_ARCHIVE_DETAIL_HDF5_ANNOTATABLE_OBJECT_HPP


