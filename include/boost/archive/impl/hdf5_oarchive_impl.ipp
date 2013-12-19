/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#include <sstream>
#include <boost/archive/hdf5_oarchive.hpp>

namespace boost {
namespace archive {

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::object_id_type const& t,
    int
)
{
    unsigned int const i = t;
    write_attribute_on_current_hdf5_group("object_id", i);
    link_tracked_object(i);
    next_object_is_attribute_ = true;
    save(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::object_reference_type const& t,
    int
)
{
    unsigned int const i = t;
    write_attribute_on_current_hdf5_group("object_reference", i);
    link_tracked_object_reference(i);
    next_object_is_attribute_ = true;
    save(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::version_type const& t,
    int
)
{
    unsigned int const i = t;
    write_attribute_on_current_hdf5_group("version", i);
    next_object_is_attribute_ = true;
    save(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::class_id_type const& t,
    int
)
{
    size_t i = t;
    write_attribute_on_current_hdf5_group("class_id", i);
    next_object_is_attribute_ = true;
    save(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::class_id_optional_type const& /*t*/,
    int
)
{
    // WARNING: class_id_optional_type needs a special treatment.
    // Basically, it does not seem to be needed. Strangely, the serialization
    // code will sometimes wish to read it, even though it was not written!
    // Since this would break the archive reading process, I have simply
    // decided to ignore it, just as the other archive types do.
#if 0
    size_t i = t;
    write_attribute_on_current_hdf5_group("class_id_optional", i);
    next_object_is_attribute_ = true;
    save(i);
#endif
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::class_id_reference_type const& t,
    int
)
{
    size_t i = t;
    write_attribute_on_current_hdf5_group("class_id_reference", i);
    next_object_is_attribute_ = true;
    save(i);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::class_name_type const& t,
    int
)
{
    const std::string s(t);
    write_attribute_on_current_hdf5_group("class_name", s);
    next_object_is_attribute_ = true;
    save(s);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) 
hdf5_oarchive_impl<Archive>::save_override
(
    boost::archive::tracking_type const& t,
    int
)
{
    write_attribute_on_current_hdf5_group("class_tracking", t.t);
    next_object_is_attribute_ = true;
    save(t.t);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(std::string)
hdf5_oarchive_impl<Archive>::create_tree_object_path() const
{
    std::ostringstream ss;

    ss << hdf5_oprimitive::tree_dir;
    for(group_stack_t::const_iterator it = group_stack_.begin();
        it != group_stack_.end();
        ++it)
    {
        ss << "/" << *it;
    }

    return ss.str();
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::link_data_object()
{
    if(!next_object_is_attribute_) {
        std::ostringstream source_path;
        source_path << create_tree_object_path() << "/<data>_d" << object_count_;
        std::string target_path =
                hdf5_oprimitive::create_object_data_path(object_count_);
        hdf5_oprimitive::create_hdf5_hard_link(source_path.str(), target_path);
    }
    next_object_is_attribute_ = false;
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::link_tracked_object(unsigned int object)
{
    std::string source_path = create_tracked_objects_path(object);
    std::string target_path = create_tree_object_path();

    hdf5_oprimitive::create_hdf5_soft_link(source_path, target_path);
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::link_tracked_object_reference
(
    unsigned int object_reference
)
{
    std::ostringstream source_path;
    source_path << create_tree_object_path()
                << "/<reference>_o"
                << object_reference;
    std::string target_path =
        hdf5_oprimitive::create_tracked_objects_path(object_reference);

    hdf5_oprimitive::create_hdf5_soft_link(
        source_path.str(),
        target_path
    );
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::write_hdf5_binary
(
    void const* address,
    std::size_t count
)
{
    hdf5_oprimitive::write_hdf5_binary_dataset(
        address,
        count,
        object_count_
    );
    link_data_and_update_object_count();
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::link_data_and_update_object_count()
{
    link_data_object();
    ++object_count_;
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::create_hdf5_group()
{
    hdf5_oprimitive::create_hdf5_group(
        create_tree_object_path()
    );
}


template<class Archive>
template <typename ValueType>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::write_attribute_on_current_hdf5_group
(
    std::string const& attribute,
    ValueType const& value
)
{
    std::ostringstream attribute_name;
    attribute_name << attribute << "_d" << object_count_;

    hdf5_oprimitive::write_hdf5_group_annotation(
        create_tree_object_path(),
        attribute_name.str(),
        value
    );
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::start_hdf5_group(char const* name)
{
    std::ostringstream group_name;

    if(NULL == name) // can occur for pointers or enums
        group_name << "_g" << group_count_;
    else
        group_name << name << "_g" << group_count_;

    group_stack_.push_back(group_name.str());
    this->create_hdf5_group();
    group_count_++;
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
hdf5_oarchive_impl<Archive>::end_hdf5_group()
{
    group_stack_.pop_back();
}


template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
hdf5_oarchive_impl<Archive>::hdf5_oarchive_impl
(
    std::string const& hdf5_filename,
    unsigned int flags
)
    :
    boost::archive::detail::common_oarchive<Archive>(flags),
    hdf5_oprimitive(hdf5_filename,
                          flags & boost::archive::no_header,
                          flags & use_variable_length_strings),
    next_object_is_attribute_(),
    object_count_(),
    group_count_(),
    group_stack_()
{}

} } // end namespace boost::archive
