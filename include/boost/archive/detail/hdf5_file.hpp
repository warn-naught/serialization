/*+-------------------------------------------------------------------------+
  | hdf5_archive: a boost::serialization archive using HDF5 format          |
  | Copyright (C) 2012-2013 Daniel Koester (dk@eada.de)                     |
  +-------------------------------------------------------------------------+*/

#ifndef HDF5_FILE_HPP
#define HDF5_FILE_HPP

#include <string>
#include <boost/archive/detail/hdf5_annotatable_object.hpp>

namespace boost {
namespace archive {
namespace detail {

/*! \brief wrapper around HDF5 file
 *
 * Longer description
 *
 */

class hdf5_file
        :
        public hdf5_annotatable_object
{
public:
    //! File opening modes
    enum file_mode_t
    {
        READ_ONLY,
        READ_WRITE
    };

    /*! \brief Open an HDF5 file. May throw!
     *
     * File must exist already if opened in READ_ONLY mode. If file exists
     * and is opened in WRITE_ONLY, it will be truncated.
     */
    hdf5_file(std::string const& filename, file_mode_t mode);

    //! Free resources on destruction.
    virtual ~hdf5_file()
    {
        close_without_throwing();
    }

    //! Create a hard link to a given target object. May throw!
    //! All paths must be absolute paths from the file root group.
    void create_hdf5_hard_link
    (
        std::string const& source_path,
        std::string const& target_path
    );

    //! Create a soft link to a given target object. May throw!
    //! All paths must be absolute paths from the file root group.
    void create_hdf5_soft_link
    (
        std::string const& source_path,
        std::string const& target_path
    );


    //! Get the HDF5 file name.
    std::string const& get_filename() const;

private:
    std::string filename_;

    //! Close the file handle, flushing all buffers. May throw!
    virtual void close_impl();
};

} } } // end namespace boost::archive::detail

#endif // HDF5_FILE_HPP


