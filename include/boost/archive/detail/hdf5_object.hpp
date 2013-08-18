/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_OBJECT_HPP
#define HDF5_OBJECT_HPP

#include <boost/noncopyable.hpp>
#include <H5Ipublic.h>

namespace archive {
namespace detail {

/*! \brief wrapper around any HDF5 object.
 *
 * Longer description
 *
 */

class hdf5_object
        :
        private boost::noncopyable
{
public:
    explicit hdf5_object(hid_t id = H5I_INVALID_HID)
        :
          id_(id)
    {}

    /*! Destroy an hdf5_object.
     *
     * Almost all HDF5 objects require a call to a H*close routine to free
     * resources. If these routines fail we throw an exception to signal the
     * problem. This would not be acceptable within a destructor, however.
     */
    virtual ~hdf5_object();

    //! Check if the HDF5 object can still be accessed safely. May throw!
    bool is_valid() const;

    //! Get the object identifier.
    inline hid_t get_id() const
    {
        return id_;
    }

    //! Invalidate the object, no further access allowed.
    //! This version may throw, so should not be called from a destructor.
    void close();

    //! Invalidate the object, no further access allowed.
    void close_without_throwing();

protected:
    //! Set an id. This might be necessary if we cannot initialize with
    //! a correct id immediately. Use with care.
    void set_id(hid_t id)
    {
        id_ = id;
    }

private:
    hid_t id_;

    virtual void close_impl() = 0;
};

} } // end namespace archive::detail

#endif // HDF5_OBJECT_HPP
