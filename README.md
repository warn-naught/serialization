serialization
=============

Boost.org serialization module

This repository adds a new serialization archive format based on HDF5 
to complement the ones already included in the official boost::serialization library: plain text, XML, and 
native binary. By building on the established and well-known boost::serialization framework, 
application code can use HDF5 or switch to any of the other established archive formats with 
only minimal changes to the code involved.

HDF5 has become a popular format to store scientific data. It is open and well-documented. 
Further advantages of HDF5 are the following:

* the format is self-describing and portable across computing platforms
* efficient storage of large arrays, parallel IO using MPI is possible (though not yet implemented)
* hierarchical description of stored data
* several low-level storage drivers, including single file or multiple-directory layouts

To compile and install this work in a Linux environment, please follow the following steps:

1. Retrieve the official Git boost superproject
    $ git clone --recursive https://github.com/boostorg/boost.git modular-boost

2. Change the serialization module to refer to the HDF5 archive version. For a recent
version of Git you can edit the following line in ".gitmodules":
    "url = ../serialization.git" --> "url = https://github.com/dk1978/serialization"

3. Synchronize submodules:
    $ git submodule sync

4. Pull HDF5 serialization code from remote repository.
    $ cd libs/serialization
    $ git pull origin master

5. Bootstrap and update Boost headers (see https://svn.boost.org/trac/boost/wiki/TryModBoost for details)
    $ cd ../..
    $ ./bootstrap.sh
    $ ./b2 headers


6. Define paths to HDF5 headers and library (assuming a bash shell syntax)
    $ export HDF5_INCLUDE_PATH=...
    $ export HDF5_LIB_PATH=...

7. Compile serialization lib
    $ cd libs/serialization/build
    $ ../../../b2 -q
