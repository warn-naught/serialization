/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_DETAIL_HDF5_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_DETAIL_HDF5_IPRIMITIVE_HPP

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/archive/hdf5_memory_buffer.hpp>
#include <boost/archive/detail/hdf5_common_archive.hpp>

namespace boost {
namespace archive {
namespace detail {

class hdf5_file;
class hdf5_datatype;

/*! \brief encapsulate reading from HDF5 file to input archive
 *
 * Longer description
 *
 */

class hdf5_iprimitive
        :
        public hdf5_common_archive
{
protected:

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        bool* t,
        std::size_t data_count,
        std::size_t object_number
    );

	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        char* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        unsigned char* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        signed char* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        wchar_t* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        int* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        unsigned int* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        short* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        unsigned short* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        long* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        unsigned long* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        long long* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        unsigned long long* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        float* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        double* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        long double* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        std::string* t,
        std::size_t data_count,
        std::size_t object_number
    );

#ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        std::wstring* t,
        std::size_t data_count,
        std::size_t object_number
    );
#endif

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_dataset
    (
        boost::serialization::collection_size_type* t,
        std::size_t data_count,
        std::size_t object_number
    );

    // Read value of given attribute from an HDF5 group.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_group_annotation
    (
        std::string const& name,
        std::string const& attribute,
        unsigned int& value
    );
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_group_annotation
    (
        std::string const& name,
        std::string const& attribute,
        std::string& value
    );

    // Load block of raw bytes.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	read_hdf5_binary_dataset
    (
        void* t,
        std::size_t data_count,
        std::size_t object_number
    );

    // Close the HDF5 file. May throw!
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	close();

    hdf5_iprimitive
    (
        std::string const& hdf5_filename,
        bool ignore_header
    );

    hdf5_iprimitive
    (
        shared_ptr<hdf5_memory_buffer> buffer,
        bool ignore_header
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
	~hdf5_iprimitive();
	
private:
    // hide HDF5 implementation details
    scoped_ptr<const hdf5_file> file_;
    
    void init(bool ignore_header);

    void read_dataset_basic
    (
        void* ptr,
        std::size_t data_count,
        hdf5_datatype const& datatype,
        std::size_t object_number
    );
};

} } } // end namespace boost::archive::detail

#endif // BOOST_ARCHIVE_DETAIL_HDF5_IPRIMITIVE_HPP


