/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef BOOST_ARCHIVE_DETAIL_POLYMORPHIC_HDF5_IARCHIVE_ROUTE_HPP
#define BOOST_ARCHIVE_DETAIL_POLYMORPHIC_HDF5_IARCHIVE_ROUTE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#include <string>
#include <cstddef>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization
namespace archive {
namespace detail{

class BOOST_ARCHIVE_DECL(BOOST_PP_EMPTY()) basic_iserializer;
class BOOST_ARCHIVE_DECL(BOOST_PP_EMPTY()) basic_pointer_iserializer;

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class ArchiveImplementation>
class polymorphic_hdf5_iarchive_route :
    public polymorphic_iarchive,
    // note: gcc dynamic cross cast fails if the the derivation below is
    // not public.  I think this is a mistake.
    public /*protected*/ ArchiveImplementation
{
private:
    // these are used by the serialization library.
    virtual void load_object(
        void *t,
        const boost::archive::detail::basic_iserializer & bis
    ){
        ArchiveImplementation::load_object(t, bis);
    }
    virtual const 
    boost::archive::detail::basic_pointer_iserializer * load_pointer(
        void * & t,
        const boost::archive::detail::basic_pointer_iserializer * bpis_ptr,
        const boost::archive::detail::basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    ){
        return ArchiveImplementation::load_pointer(t, bpis_ptr, finder);
    }
    virtual void set_library_version(
        boost::archive::library_version_type archive_library_version
    ){
        ArchiveImplementation::set_library_version(archive_library_version);
    }
    virtual boost::archive::library_version_type get_library_version() const{
        return ArchiveImplementation::get_library_version();
    }
    virtual unsigned int get_flags() const {
        return ArchiveImplementation::get_flags();
    }
    virtual void delete_created_pointers(){
        ArchiveImplementation::delete_created_pointers();
    }
    virtual void reset_object_address(
        const void * new_address,
        const void * old_address
    ){
        ArchiveImplementation::reset_object_address(new_address, old_address);
    }
    virtual void load_binary(void * t, std::size_t size){
        ArchiveImplementation::load_binary(t, size);
    }
    // primitive types the only ones permitted by polymorphic archives
    virtual void load(bool & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(char & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(signed char & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned char & t){
        ArchiveImplementation::load(t);
    }
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void load(wchar_t & t){
        ArchiveImplementation::load(t);
    }
    #endif
    #endif
    virtual void load(short & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned short & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(int & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned int & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(long & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned long & t){
        ArchiveImplementation::load(t);
    }
    #if defined(BOOST_HAS_LONG_LONG)
    virtual void load(boost::long_long_type & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(boost::ulong_long_type & t){
        ArchiveImplementation::load(t);
    }
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void load(__int64 & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned __int64 & t){
        ArchiveImplementation::load(t);
    }
    #endif
    virtual void load(float & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(double & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(std::string & t){
        ArchiveImplementation::load(t);
    }
    #ifndef BOOST_NO_STD_WSTRING
    virtual void load(std::wstring & t){
        ArchiveImplementation::load(t);
    }
    #endif
    // used for xml and other tagged formats default does nothing
    virtual void load_start(const char * name){
        ArchiveImplementation::load_start(name);
    }
    virtual void load_end(const char * name){
        ArchiveImplementation::load_end(name);
    }

    virtual void register_basic_serializer
    (
        const boost::archive::detail::basic_iserializer & bis
    ){
        ArchiveImplementation::register_basic_serializer(bis);
    }
public:
    // this can't be inheriteded because they appear in mulitple
    // parents
    typedef boost::mpl::bool_<true> is_loading;
    typedef boost::mpl::bool_<false> is_saving;
    // the >> operator
    template<class T>
    polymorphic_iarchive & operator>>(T & t){
        return polymorphic_iarchive::operator>>(t);
    }
    // the & operator
    template<class T>
    polymorphic_iarchive & operator&(T & t){
        return polymorphic_iarchive::operator&(t);
    }
    // register type function
    template<class T>
    const basic_pointer_iserializer * 
    register_type(T * t = NULL){
        return ArchiveImplementation::register_type(t);
    }
    // hdf5 archives take a string as constructor argument
    polymorphic_hdf5_iarchive_route(
        std::string const& hdf5_filename,
        unsigned int flags = 0
    ) :
        ArchiveImplementation(hdf5_filename, flags)
    {}
    virtual ~polymorphic_hdf5_iarchive_route(){};
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_POLYMORPHIC_HDF5_IARCHIVE_ROUTE_HPP
