/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <H5Ipublic.h>
#include <H5Fpublic.h>
#include <H5Lpublic.h>
#include <H5LTpublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/hdf5_archive_exception.hpp>
#include <boost/archive/detail/hdf5_memory_file.hpp>

namespace boost {
namespace archive {
namespace detail {

hdf5_memory_file::hdf5_memory_file(shared_ptr<hdf5_memory_buffer> buffer, 
    file_mode_t mode) 
    :
    hdf5_file(
        mode == READ_ONLY ?
            H5LTopen_file_image(
                buffer->ptr(),
                buffer->len(),
                H5LT_FILE_IMAGE_DONT_COPY 
                | H5LT_FILE_IMAGE_DONT_RELEASE
            )
            :
            H5LTopen_file_image(
                buffer->ptr(),
                buffer->len(),
                H5LT_FILE_IMAGE_DONT_COPY 
                | H5LT_FILE_IMAGE_DONT_RELEASE
                | H5LT_FILE_IMAGE_OPEN_RW
            )
    ),
    buffer_(buffer)
{
    if(get_id() < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                mode == READ_ONLY ?
                hdf5_archive_exception::hdf5_archive_file_access_error
                :
                hdf5_archive_exception::hdf5_archive_file_create_error
            )
        );
    }
}


void hdf5_memory_file::close_impl()
{
    if(H5Fclose(get_id()) < 0) {
        boost::serialization::throw_exception(
            hdf5_archive_exception(
                hdf5_archive_exception::hdf5_archive_file_close_error
            )
        );
    }
}


} } } // end namespace boost::archive::detail
