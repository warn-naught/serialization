/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

// DK: dummy wrapper to represent test_[io]stream. The point is to throw away
// the second argument that would otherwise contain TEST_STREAM_FLAGS

#if !defined(HDF5_ARCHIVE_TEST_STREAM_WRAPPER)
#define HDF5_ARCHIVE_TEST_STREAM_WRAPPER
struct test_stream_wrapper
  :
  public std::string
{
  test_stream_wrapper(std::string const& str, unsigned int = 0)
    :
    std::string(str)
  {}
  
};
#endif

#include <boost/archive/polymorphic_hdf5_oarchive.hpp>
typedef boost::archive::polymorphic_hdf5_oarchive test_oarchive;
typedef test_stream_wrapper test_ostream;
#include <boost/archive/polymorphic_hdf5_iarchive.hpp>
typedef boost::archive::polymorphic_hdf5_iarchive test_iarchive;
typedef test_stream_wrapper test_istream;
