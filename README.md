serialization
=============

Boost.org serialization module


This code provides a new serialization archive format based on HDF5 
to complement the ones already included in the boost::serialization library: plain text, XML, and 
native binary. By building on the established and well-known boost::serialization framework, 
application code can use HDF5 or switch to any of the other established archive formats with 
only minimal changes to the code involved.

HDF5 has become a popular format to store scientific data. It is open and well-documented. 
Further advantages of HDF5 are the following:

    the format is self-describing and portable across computing platforms
    efficient storage of large arrays, parallel IO using MPI is possible (though not yet implemented)
    hierarchical description of stored data
    several low-level storage drivers, including single file or multiple-directory layouts
    APIs to C, C++, and Fortran

