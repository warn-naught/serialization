/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_HDF5_IARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_HDF5_IARCHIVE_IMPL_HPP

#include <cstddef> // size_t
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/archive/detail/hdf5_iprimitive.hpp>

namespace boost {
namespace archive {

template<class Archive>
class hdf5_iarchive_impl
        :
        public boost::archive::detail::common_iarchive<Archive>,
        public detail::hdf5_iprimitive
{
    friend class detail::interface_iarchive<Archive>;
    friend class load_access;

public:
    void load_binary(void* address, std::size_t count)
    {
        read_hdf5_binary(address, count);
    }

    // we provide an optimized load for all arithmetic types
    struct use_array_optimization {
        template <class T>
        struct apply : public boost::is_arithmetic<T> {};
    };

    template<class ValueType>
    void load_array(boost::serialization::array<ValueType>& a, unsigned int /*version*/)
    {
        read_hdf5_primitive_array(a.address(), a.count());
    }

protected:
    typedef boost::archive::detail::common_iarchive<Archive>
    detail_common_iarchive;

    // Anything not an attribute and not a name-value pair is an
    // should be trapped here.
    template<class T>
    void load_override(T & t,  BOOST_PFTO int)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((boost::serialization::is_wrapper< T >));
        this->detail_common_iarchive::load_override(t, 0);
    }


    // special treatment for name-value pairs.
    template<class T>
    void load_override(
        #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
        const
        #endif
        boost::serialization::nvp< T > & t,
        int
    )
    {
        this->detail_common_iarchive::load_override(t.value(), 0);
    }

    // specific loads for attributes
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::object_id_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::object_reference_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::version_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::class_id_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::class_id_optional_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::class_id_reference_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::class_name_type& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    load_override(boost::archive::tracking_type& t, int);

    // main template for serialization of primitive types
    template<class T>
    void load(T & t){
        load_binary(& t, sizeof(T));
    }

    // load routines for everything we can directly map to an HDF5 type.
    void load(bool& t) { read_hdf5_primitive(t); }
    void load(char& t) { read_hdf5_primitive(t); }
    void load(unsigned char& t) { read_hdf5_primitive(t); }
    void load(signed char& t) { read_hdf5_primitive(t); }
    void load(wchar_t& t) { read_hdf5_primitive(t); }
    void load(int& t) { read_hdf5_primitive(t); }
    void load(unsigned int& t) { read_hdf5_primitive(t); }
    void load(short& t) { read_hdf5_primitive(t); }
    void load(unsigned short& t) { read_hdf5_primitive(t); }
    void load(long& t) { read_hdf5_primitive(t); }
    void load(unsigned long& t) { read_hdf5_primitive(t); }
    void load(long long& t) { read_hdf5_primitive(t); }
    void load(unsigned long long& t) { read_hdf5_primitive(t); }
    void load(float& t) { read_hdf5_primitive(t); }
    void load(double& t) { read_hdf5_primitive(t); }
    void load(long double& t) { read_hdf5_primitive(t); }
    void load(std::string& t) { read_hdf5_primitive(t); }
 #ifndef BOOST_NO_STD_WSTRING
	void load(std::wstring& t) { read_hdf5_primitive(t); }
#endif
	void load(boost::serialization::collection_size_type& t) { read_hdf5_primitive(t); }

    // load for item_version objects.
    void load(boost::serialization::item_version_type& t)
    {
        unsigned int v;
        load(v);
        t = boost::serialization::item_version_type(v);
    }
	
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
    hdf5_iarchive_impl(std::string const& hdf5_filename, unsigned int flags);

private:
    std::size_t object_count_;

    void update_object_count()
    {
        object_count_++;
    }

    template<class T>
    void read_hdf5_primitive(T& t)
    {
        hdf5_iprimitive::read_hdf5_dataset(&t, 1, object_count_);
        update_object_count();
    }

    template <class T>
    void read_hdf5_primitive_array(T* address, std::size_t count)
    {
        hdf5_iprimitive::read_hdf5_dataset(
            address,
            count,
            object_count_
        );
        update_object_count();
    }

    void read_hdf5_binary(void* address, std::size_t count)
    {
        hdf5_iprimitive::read_hdf5_binary_dataset(
            address,
            count,
            object_count_
        );
        update_object_count();
    }
};

}} // end namespace boost::archive

#endif // BOOST_ARCHIVE_HDF5_IARCHIVE_IMPL_HPP
