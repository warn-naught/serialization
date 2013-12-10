/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <sstream>
#include <cstring>
#include <vector>
#define BOOST_ARCHIVE_SOURCE
#include <boost/static_assert.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/archive/detail/hdf5_file.hpp>
#include <boost/archive/detail/hdf5_group.hpp>
#include <boost/archive/detail/hdf5_dataset.hpp>
#include <boost/archive/detail/hdf5_datatype.hpp>
#include <boost/archive/detail/hdf5_dataspace.hpp>
#include <boost/archive/detail/hdf5_oprimitive.hpp>
#include <boost/archive/detail/hdf5_annotation.hpp>

namespace boost {
namespace archive {
namespace detail {

void hdf5_oprimitive::init(bool suppress_header)
{
    if(!suppress_header) {
        // Annotate the root group with basic boost::archive information.
        char const *archive_signature =
            boost::archive::BOOST_ARCHIVE_SIGNATURE();

        write_hdf5_group_annotation("/", "signature", archive_signature);

        unsigned int version = boost::archive::BOOST_ARCHIVE_VERSION();

        write_hdf5_group_annotation("/", "version", version);
    }

    // Create a group containing all serialized objects in a flat list.
    create_hdf5_group(data_dir);

    // Create a group containing links to all tracked objects.
    create_hdf5_group(tracked_objects_dir);

    // Create a group "<tree>" containing all serialized objects
    // with hierarchy information.
    create_hdf5_group(tree_dir);
}


void hdf5_oprimitive::write_hdf5_group_annotation
(
    std::string const& name,
    std::string const& attribute,
    std::string const& value
)
{
    hdf5_group group(*file_, name);
    hdf5_datatype datatype(H5T_STRING);
    if(use_variable_length_strings_)
        datatype.resize(H5T_VARIABLE);
    else
        datatype.resize(value.size());

    hdf5_dataspace dataspace(1);
    hdf5_annotation group_annotation(group, attribute, datatype, dataspace);
    char const* c_string = value.c_str();

    if(use_variable_length_strings_)
        group_annotation.write(datatype, &c_string);
    else
        group_annotation.write(datatype, c_string);

    group_annotation.close();
    dataspace.close();
    datatype.close();
    group.close();
}


void hdf5_oprimitive::write_hdf5_group_annotation
(
    std::string const& name,
    std::string const& attribute,
    unsigned int const value
)
{
    hdf5_group group(*file_, name);
    hdf5_datatype datatype(H5T_NATIVE_UINT);
    hdf5_dataspace dataspace(1);
    hdf5_annotation group_annotation(group, attribute, datatype, dataspace);

    group_annotation.write(datatype, &value);

    group_annotation.close();
    dataspace.close();
    datatype.close();
    group.close();
}



void hdf5_oprimitive::write_dataset_basic
(
    void const* ptr,
    std::size_t data_count,
    hdf5_datatype const& datatype,
    std::size_t object_number
)
{
    // create a dataspace
    hdf5_dataspace dataspace(data_count);

    // create a new dataset at given path.
    std::string path = create_object_data_path(object_number);

    hdf5_dataset dataset(*file_, path, datatype, dataspace);

    // store the data.
    dataset.write(datatype, ptr);

    // end access to dataset and release resources.
    dataset.close();

    // end access to the dataspace and release resources.
    dataspace.close();
}


void hdf5_oprimitive::write_hdf5_dataset
(
    bool const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    hdf5_datatype bool_type(H5T_NATIVE_CHAR);
    bool_type.resize(sizeof(bool));

    write_dataset_basic(t, data_count, bool_type, object_number);
    bool_type.close();
}


void hdf5_oprimitive::write_hdf5_dataset
(
    char const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_CHAR), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    unsigned char const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_UCHAR), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    signed char const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_SCHAR), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    int const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_INT), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    unsigned int const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_UINT), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    short const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_SHORT), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    unsigned short const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_USHORT), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    long const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_LONG), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    unsigned long const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_ULONG), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    long long const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_LLONG), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    unsigned long long const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_ULLONG), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    float const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_FLOAT), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    double const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_DOUBLE), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    long double const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    write_dataset_basic(t, data_count, hdf5_datatype(H5T_NATIVE_LDOUBLE), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    const std::string *t,
    std::size_t data_count,
    std::size_t object_number
)
{
    BOOST_ASSERT(data_count == 1);
    char const* c_string = t->c_str();

    hdf5_datatype string_type(H5T_STRING);
    if(use_variable_length_strings_ || t->empty()) {
        string_type.resize(H5T_VARIABLE);
        write_dataset_basic(&c_string, data_count, string_type, object_number);
    }
    else {
        string_type.resize(t->size());
        write_dataset_basic(c_string, data_count, string_type, object_number);
    }

    string_type.close();
}


void hdf5_oprimitive::write_hdf5_dataset
(
    boost::serialization::collection_size_type const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    BOOST_STATIC_ASSERT(sizeof(size_t) <= sizeof(hsize_t));

    hsize_t i = *t;
    // paranoid and perhaps unnecessary checking...
    BOOST_ASSERT(boost::serialization::collection_size_type(i) == *t);

    write_dataset_basic(&i, data_count, hdf5_datatype(H5T_NATIVE_HSIZE), object_number);
}


void hdf5_oprimitive::write_hdf5_dataset
(
    wchar_t const* t,
    std::size_t data_count,
    std::size_t object_number
)
{
    std::wstring wstring(t, data_count);
    write_hdf5_dataset(&wstring, 1, object_number); 
}


void hdf5_oprimitive::write_hdf5_dataset
(
    const std::wstring *t,
    std::size_t data_count,
    std::size_t object_number
)
{
    BOOST_ASSERT(data_count == 1);
    // If you can think of a better way to store wchar_t/wstring objects in HDF5, be my guest...
    std::size_t size = (t->size() + 1) * sizeof(wchar_t);
    void const* buffer = t->c_str();
    write_hdf5_binary_dataset(buffer, size, object_number);
}


void hdf5_oprimitive::write_hdf5_binary_dataset(
    void const* address,
    std::size_t data_count,
    std::size_t object_number
)
{
    // define the datatype
    hdf5_datatype datatype(H5T_OPAQUE);
    datatype.resize(data_count);

    write_dataset_basic(address, 1, datatype, object_number);

    // end access to the datatype and release resources.
    datatype.close();
}


void hdf5_oprimitive::create_hdf5_group(std::string const& name)
{
    hdf5_group group(*file_, name);
    group.close();
}


void hdf5_oprimitive::create_hdf5_hard_link
(
    std::string const& source_path,
    std::string const& target_path
)
{
    file_->create_hdf5_hard_link(source_path, target_path);
}


void hdf5_oprimitive::create_hdf5_soft_link
(
    std::string const& source_path,
    std::string const& target_path
)
{
    file_->create_hdf5_soft_link(source_path, target_path);
}


void hdf5_oprimitive::close()
{
    file_->close();
}


hdf5_oprimitive::hdf5_oprimitive
(
    std::string const& hdf5_filename,
    bool no_header,
    bool use_variable_length_strings
)
    :
      file_(new hdf5_file(hdf5_filename, hdf5_file::READ_WRITE)),
      use_variable_length_strings_(use_variable_length_strings)
{
    init(no_header);
}


hdf5_oprimitive::~hdf5_oprimitive()
{}

} } } // end namespace boost::archive::detail
