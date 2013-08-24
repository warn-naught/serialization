/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <boost/detail/no_exceptions_support.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_object.hpp>

namespace boost {
namespace archive {
namespace detail {

hdf5_object::~hdf5_object()
{
    // trap deletion of objects without calling close().
    BOOST_ASSERT(id_ == H5I_INVALID_HID);
}


void hdf5_object::close()
{
    if(id_ == H5I_INVALID_HID) // prevent trying to close more than once.
        return;

    close_impl();
    id_ = H5I_INVALID_HID; // Be sure id cannot be used further.
}


void hdf5_object::close_without_throwing()
{
    BOOST_TRY {
        close();
    }
    BOOST_CATCH(...) {}
    BOOST_CATCH_END
}


bool hdf5_object::is_valid() const
{
    htri_t status = H5Iis_valid(id_);
    if(status > 0) { // valid
        return true;
    }
    else if(status == 0) { // invalid
        return false;
    }
    else { // error, status is undetermined.
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_identifier_access_error
            )
        );
        return false;
    }
}

} } } // end namespace boost::archive::detail
