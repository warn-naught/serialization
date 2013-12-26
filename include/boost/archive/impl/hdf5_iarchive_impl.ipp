/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  |                                                                         |
  | Use, modification and distribution is subject to the Boost Software     |
  | License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at |
  | http://www.boost.org/LICENSE_1_0.txt)                                   |
  +-------------------------------------------------------------------------+*/

#include <cstring> // for memcpy
#include <boost/archive/hdf5_iarchive.hpp>

namespace boost {
namespace archive {

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::object_id_type& t,
    int
)
{
    unsigned int i;
    load(i);
    t = boost::archive::object_id_type(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::object_reference_type& t,
    int
)
{
    unsigned int i;
    load(i);
    t = boost::archive::object_reference_type(
            boost::archive::object_id_type(i)
        );
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::version_type& t,
    int
)
{
    unsigned int i;
    load(i);
    t = boost::archive::version_type(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::class_id_type& t,
    int
)
{
    size_t i;
    load(i);
    t = boost::archive::class_id_type(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::class_id_optional_type& /*t*/,
    int
)
{
    // WARNING: class_id_optional_type needs a special treatment.
    // Basically, it does not seem to be needed. Strangely, the serialization
    // code will sometimes wish to read it, even though it was not written!
    // Since this would break the archive reading process, I have simply
    // decided to ignore it, just as the other archive types do.
#if 0
    size_t i;
    load(i);
    t = boost::archive::class_id_optional_type(
            boost::archive::class_id_type(i)
        );
#endif
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::class_id_reference_type& t,
    int
)
{
    size_t i;
    load(i);
    t = boost::archive::class_id_reference_type(
            boost::archive::class_id_type(i)
        );
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::class_name_type& t,
    int
)
{
    std::string s;
    s.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
    load(s);
    if(s.size() > (BOOST_SERIALIZATION_MAX_KEY_SIZE - 1))
        boost::serialization::throw_exception(
            boost::archive::archive_exception(
                boost::archive::archive_exception::invalid_class_name
            )
        );

    std::memcpy(t, s.data(), s.size());
    // borland tweak
    t.t[s.size()] = '\0';
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_iarchive_impl<Archive>::load_override
(
    boost::archive::tracking_type& t,
    int
)
{
    bool i;
    load(i);
    t = boost::archive::tracking_type(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
hdf5_iarchive_impl<Archive>::hdf5_iarchive_impl
(
    std::string const& hdf5_filename,
    unsigned int flags
)
    :
    boost::archive::detail::common_iarchive<Archive>(flags),
    hdf5_iprimitive(hdf5_filename, flags & boost::archive::no_header),
    object_count_()
{}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
hdf5_iarchive_impl<Archive>::hdf5_iarchive_impl
(
    shared_ptr<hdf5_memory_buffer> buffer,
    unsigned int flags
)
    :
    boost::archive::detail::common_iarchive<Archive>(flags),
    hdf5_iprimitive(buffer, flags & boost::archive::no_header),
    object_count_()
{}

} } // end namespace boost::archive
