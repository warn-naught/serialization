/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_HDF5_OARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_HDF5_OARCHIVE_IMPL_HPP

#include <cstddef> // size_t
#include <deque>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/detail/hdf5_oprimitive.hpp>

namespace boost {
namespace archive {

template<class Archive>
class hdf5_oarchive_impl
        :
        public boost::archive::detail::common_oarchive<Archive>,
        public detail::hdf5_oprimitive
{
    friend class detail::interface_oarchive<Archive>;
    friend class save_access;

public:
    enum hdf5_archive_flags {
        use_variable_length_strings = 16
    };

    void save_binary(void const* address, std::size_t count)
    {
        write_hdf5_binary(address, count);
    }

    // we provide an optimized save for all arithmetic types
    struct use_array_optimization {
        template <class T>
        struct apply : public boost::is_arithmetic<T> {};
    };

    template<class ValueType>
    void save_array(boost::serialization::array<ValueType> const& a, unsigned int /*version*/)
    {
        write_hdf5_primitive_array(a.address(), a.count());
    }

protected:
    typedef boost::archive::detail::common_oarchive<Archive>
    detail_common_oarchive;

    // Anything not an attribute and not a name-value pair is an
    // error and should be trapped here.
    template<class T>
    void save_override(T & t, BOOST_PFTO int)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((boost::serialization::is_wrapper< T >));
        this->detail_common_oarchive::save_override(t, 0);
    }

    // special treatment for name-value pairs.
    template<class T>
    void save_override(
        #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
        const
        #endif
        ::boost::serialization::nvp< T > & t,
        int
    )
    {
        this->This()->start_hdf5_group(t.name());
        this->detail_common_oarchive::save_override(t.const_value(), 0);
        this->This()->end_hdf5_group();
    }

    // specific saves for attributes
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::object_id_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::object_reference_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	save_override(boost::archive::version_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::class_id_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::class_id_optional_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::class_id_reference_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::class_name_type const& t, int);
	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    save_override(boost::archive::tracking_type const& t, int);

    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
        save_binary(& t, sizeof(T));
    }

    // save routines for everything we can directly map to an HDF5 type.
    void save(bool const& t) { write_hdf5_primitive(t); }
    void save(char const& t) { write_hdf5_primitive(t); }
    void save(unsigned char const& t) { write_hdf5_primitive(t); }
    void save(signed char const& t) { write_hdf5_primitive(t); }
    void save(wchar_t const& t) { write_hdf5_primitive(t); }
    void save(int const& t) { write_hdf5_primitive(t); }
    void save(unsigned int const& t) { write_hdf5_primitive(t); }
    void save(short const& t) { write_hdf5_primitive(t); }
    void save(unsigned short const& t) { write_hdf5_primitive(t); }
    void save(long const& t) { write_hdf5_primitive(t); }
    void save(unsigned long const& t) { write_hdf5_primitive(t); }
    void save(long long const& t) { write_hdf5_primitive(t); }
    void save(unsigned long long const& t) { write_hdf5_primitive(t); }
    void save(float const& t) { write_hdf5_primitive(t); }
    void save(double const& t) { write_hdf5_primitive(t); }
    void save(long double const& t) { write_hdf5_primitive(t); }
    void save(std::string const& t) { write_hdf5_primitive(t); }
#ifndef BOOST_NO_STD_WSTRING
    void save(std::wstring const& t) { write_hdf5_primitive(t); }
#endif
    void save(boost::serialization::collection_size_type const& t) { write_hdf5_primitive(t); }

    // save for item_version objects.
    void save(boost::serialization::item_version_type const& t)
    {
        save(static_cast<unsigned int const>(t));
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
    hdf5_oarchive_impl(std::string const& hdf5_filename, unsigned int flags);

private:
    bool next_object_is_attribute_;
    std::size_t object_count_;
    std::size_t group_count_;
    typedef std::deque<std::string> group_stack_t;
    group_stack_t group_stack_;

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(std::string) 
	create_tree_object_path() const;

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	link_data_object();

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	link_tracked_object(unsigned int object);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	link_tracked_object_reference(unsigned int object_reference);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	link_data_and_update_object_count();

    template<class T>
    void write_hdf5_primitive(T const& t)
    {
        hdf5_oprimitive::write_hdf5_dataset(&t, 1, object_count_);
        link_data_and_update_object_count();
    }

    template<class T>
    void write_hdf5_primitive_array(T const* address, std::size_t count)
    {
        hdf5_oprimitive::write_hdf5_dataset(
            address,
            count,
            object_count_
        );
        link_data_and_update_object_count();
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_hdf5_binary(void const* address, std::size_t count);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	create_hdf5_group();

    template <typename ValueType>
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	write_attribute_on_current_hdf5_group
    (
        std::string const& attribute,
        ValueType const& value
    );

    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
	start_hdf5_group(char const* name);

	BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
    end_hdf5_group();
};

}} // end namespace boost::archive

#endif // BOOST_ARCHIVE_HDF5_OARCHIVE_IMPL_HPP
