/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <vector>
#define BOOST_ARCHIVE_SOURCE
#include <boost/static_assert.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/hdf5_file.hpp>
#include <boost/archive/detail/hdf5_group.hpp>
#include <boost/archive/detail/hdf5_annotation.hpp>
#include <boost/archive/detail/hdf5_dataset.hpp>
#include <boost/archive/detail/hdf5_datatype.hpp>
#include <boost/archive/detail/hdf5_dataspace.hpp>
#include <boost/archive/detail/hdf5_oprimitive.hpp>
#include <boost/archive/detail/hdf5_iprimitive.hpp>


namespace boost {
namespace archive {
namespace detail {

void hdf5_iprimitive::init(bool ignore_header)
{
    if(!ignore_header) {
        // Check if this archive was written by the same library version.
        std::string archive_signature;

        read_hdf5_group_annotation("/", "signature", archive_signature);

        if(archive_signature != boost::archive::BOOST_ARCHIVE_SIGNATURE()) {
            boost::serialization::throw_exception(
                boost::archive::archive_exception(
                    boost::archive::archive_exception::invalid_signature
                )
            );
        }

        unsigned int version;
        read_hdf5_group_annotation("/", "version", version);

        if(version != boost::archive::BOOST_ARCHIVE_VERSION()) {
            boost::serialization::throw_exception(
                boost::archive::archive_exception(
                    boost::archive::archive_exception::unsupported_version
                )
            );
        }
    }
}


void hdf5_iprimitive::read_hdf5_group_annotation
(
    const std::string &name,
    const std::string &attribute,
    std::string &value
)
{
    const hdf5_group group(*file_, name);
    const hdf5_annotation group_annotation(group, attribute);
    hdf5_datatype datatype(group_annotation);


    if(datatype.is_variable_length_string()) {
        char* buffer;
        hdf5_dataspace dataspace(group_annotation);
        group_annotation.read(datatype, &buffer);
        value = buffer;
        datatype.reclaim_buffer(dataspace, &buffer);
        dataspace.close();
    }
    else {
        size_t size = datatype.get_size();
        std::vector<char> buffer(size);
        group_annotation.read(datatype, &buffer[0]);
        value.resize(size);
        value.replace(0,size,&buffer[0],size);
    }

    datatype.close();
}


void hdf5_iprimitive::read_hdf5_group_annotation
(
    const std::string &name,
    const std::string &attribute,
    unsigned int &value
)
{
    const hdf5_group group(*file_, name);
    hdf5_annotation group_annotation(group, attribute);
    hdf5_datatype datatype(group_annotation);
    group_annotation.read(datatype, &value);
}


void hdf5_iprimitive::read_dataset_basic
(
    void *ptr,
    std::size_t data_count,
    const hdf5_datatype &datatype,
    std::size_t object_number
)
{
    std::string path = create_object_data_path(object_number);
    hdf5_dataset dataset(*file_, path);

    dataset.read(datatype, ptr);

    dataset.close();
}


void hdf5_iprimitive::read_hdf5_dataset
(
    bool* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    hdf5_datatype bool_type(H5T_NATIVE_CHAR);
    bool_type.resize(sizeof(bool));

    read_dataset_basic(t, data_count, bool_type, object_number);
    bool_type.close();
}


void hdf5_iprimitive::read_hdf5_dataset
(
    char* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_CHAR), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    unsigned char* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_UCHAR), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    signed char* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_SCHAR), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    wchar_t* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    std::wstring wstring;
    read_hdf5_dataset(&wstring, 1, object_number); 
    for(std::size_t i = 0; i < data_count; i++)
      t[i] = wstring[i];
}


void hdf5_iprimitive::read_hdf5_dataset
(
    int* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_INT), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    unsigned int* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_UINT), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    short* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_SHORT), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    unsigned short* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_USHORT), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    long* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_LONG), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    unsigned long* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_ULONG), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    long long* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_LLONG), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    unsigned long long* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_ULLONG), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    float* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_FLOAT), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    double* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_DOUBLE), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    long double* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    read_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_LDOUBLE), object_number);
}


void hdf5_iprimitive::read_hdf5_dataset
(
    std::string* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    BOOST_ASSERT(data_count == 1);
    std::string path = create_object_data_path(object_number);
    hdf5_dataset dataset(*file_, path);
    hdf5_datatype datatype(dataset);

    if(datatype.is_variable_length_string()) {
        char* buffer;
        hdf5_dataspace dataspace(dataset);
        dataset.read(datatype, &buffer);
        *t = buffer;
        datatype.reclaim_buffer(dataspace, &buffer);
        dataspace.close();
    }
    else {
        size_t size = datatype.get_size();
        std::vector<char> buffer(size);
        dataset.read(datatype, &buffer[0]);
        t->resize(size);
        t->replace(0, size, &buffer[0], size);
    }

    datatype.close();
    dataset.close();
}


void hdf5_iprimitive::read_hdf5_dataset
(
    std::wstring* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    BOOST_ASSERT(data_count == 1);
    std::string path = create_object_data_path(object_number);
    hdf5_dataset dataset(*file_, path);
    hdf5_datatype datatype(dataset);

    // If you can think of a better way to store wchar_t/wstring objects in HDF5, be my guest...
    size_t size = datatype.get_size();
    std::size_t string_size = size / sizeof(wchar_t);
	if(string_size) {
		std::vector<wchar_t> buffer(string_size);
		dataset.read(datatype, &buffer[0]);

		t->resize(string_size);
		for(size_t i = 0; i < string_size; i++)
			(*t)[i] = buffer[i];
	}
    datatype.close();
    dataset.close();
}


void hdf5_iprimitive::read_hdf5_dataset
(
    boost::serialization::collection_size_type* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    BOOST_STATIC_ASSERT(sizeof(size_t) <= sizeof(hsize_t));

    hsize_t i;
    read_dataset_basic(&i, data_count, hdf5_datatype(H5T_NATIVE_HSIZE), object_number);
    *t = boost::serialization::collection_size_type(i);
}


void hdf5_iprimitive::read_hdf5_binary_dataset
(
    void *t,
    std::size_t data_count,
    std::size_t object_number
)
{
    // define the datatype
    hdf5_datatype datatype(H5T_OPAQUE);
    datatype.resize(data_count);

    read_dataset_basic(t, 1, datatype, object_number);

    // end access to the datatype and release resources.
    datatype.close();
}


hdf5_iprimitive::hdf5_iprimitive
(
    const std::string &hdf5_filename,
    bool ignore_header
)
    :
      file_(new hdf5_file(hdf5_filename, hdf5_file::READ_ONLY))
{
    init(ignore_header);
}

hdf5_iprimitive::~hdf5_iprimitive()
{}

} } } // end namespace boost::archive::detail
