/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef BASIC_HDF5_OPRIMITIVE_HPP
#define BASIC_HDF5_OPRIMITIVE_HPP

#include <boost/scoped_ptr.hpp>
#include <boost/archive/detail/hdf5_common_archive.hpp>

namespace boost {
namespace archive {
namespace detail {

class hdf5_file;
class hdf5_datatype;

class hdf5_oprimitive
        :
        public hdf5_common_archive
{
protected:
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    write_hdf5_dataset
    (
        bool const* t,
        std::size_t data_count,
        std::size_t object_number
    );

	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        char const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        unsigned char const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        signed char const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    write_hdf5_dataset
    (
        wchar_t const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    write_hdf5_dataset
    (
        int const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        unsigned int const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        short const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        unsigned short const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        long const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        unsigned long const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        long long const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        unsigned long long const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        float const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        double const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        long double const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        std::string const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        std::wstring const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_dataset
    (
        boost::serialization::collection_size_type const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    // create a new group given its absolute path. All intermediate groups must
    // exist already.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	create_hdf5_group(std::string const& name);

    // annotate given group, if that group is present, and if the attribute
    // does not exist yet.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_group_annotation
    (
        std::string const& name,
        std::string const& attribute,
        unsigned int const value
    );
    
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_group_annotation
    (
        std::string const& name,
        std::string const& attribute,
        std::string const& value
    );

    // save block of raw bytes.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_binary_dataset
    (
        void const* t,
        std::size_t data_count,
        std::size_t object_number
    );

    // create a hard link to a given internal object.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	create_hdf5_hard_link
    (
        std::string const& source_path,
        std::string const& target_path
    );

    // create a soft link to a given internal object.
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	create_hdf5_soft_link
    (
        std::string const& source_path,
        std::string const& target_path
    );

    // Close the HDF5 file. May throw!
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	close();

    hdf5_oprimitive
    (
        std::string const& hdf5_filename,
        bool no_header,
        bool use_variable_length_strings
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
	~hdf5_oprimitive();

private:
	// hide HDF5 implementation details
    scoped_ptr<hdf5_file> file_;
    bool const use_variable_length_strings_;

    void init(bool suppress_header);

    void write_dataset_basic
    (
        void const* ptr,
        std::size_t data_count,
        hdf5_datatype const& data_type,
        std::size_t object_number
    );
};


} } } // end namespace boost::archive::detail


#endif // BASIC_HDF5_OPRIMITIVE_HPP
