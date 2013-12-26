/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <H5Fpublic.h>
#include <H5FDcore.h>
#include <H5Ppublic.h>
#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/hdf5_memory_buffer.hpp>

namespace boost {
namespace archive {

hdf5_memory_buffer::hdf5_memory_buffer(size_t len)
    :
    buffer_(new char[len]),
    len_(len)
{
    hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_core(fapl, len, 0);
    hid_t fid = H5Fcreate(".image", H5F_ACC_TRUNC, H5P_DEFAULT, fapl);
    H5Fflush(fid, H5F_SCOPE_GLOBAL);
    H5Fget_file_image(fid, ptr(), this->len());
    H5Fclose(fid);
    H5Pclose(fapl);
}

} } // end namespace boost::archive
