/*++

Copyright (C) 2023 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Autodesk Inc. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


This file has been generated by the Automatic Component Toolkit (ACT) version 1.8.0-develop.

Abstract: This is an autogenerated C++-Header file with basic types in
order to allow an easy use of GRPC Library Wrapper

Interface version: 1.2.0

*/

#ifndef __LIBGRPCWRAPPER_TYPES_HEADER_CPP
#define __LIBGRPCWRAPPER_TYPES_HEADER_CPP


/*************************************************************************************************************************
 Scalar types definition
**************************************************************************************************************************/

#ifdef LIBGRPCWRAPPER_USELEGACYINTEGERTYPES

typedef unsigned char LibGRPCWrapper_uint8;
typedef unsigned short LibGRPCWrapper_uint16 ;
typedef unsigned int LibGRPCWrapper_uint32;
typedef unsigned long long LibGRPCWrapper_uint64;
typedef char LibGRPCWrapper_int8;
typedef short LibGRPCWrapper_int16;
typedef int LibGRPCWrapper_int32;
typedef long long LibGRPCWrapper_int64;

#else // LIBGRPCWRAPPER_USELEGACYINTEGERTYPES

#include <stdint.h>

typedef uint8_t LibGRPCWrapper_uint8;
typedef uint16_t LibGRPCWrapper_uint16;
typedef uint32_t LibGRPCWrapper_uint32;
typedef uint64_t LibGRPCWrapper_uint64;
typedef int8_t LibGRPCWrapper_int8;
typedef int16_t LibGRPCWrapper_int16;
typedef int32_t LibGRPCWrapper_int32;
typedef int64_t LibGRPCWrapper_int64 ;

#endif // LIBGRPCWRAPPER_USELEGACYINTEGERTYPES

typedef float LibGRPCWrapper_single;
typedef double LibGRPCWrapper_double;

/*************************************************************************************************************************
 General type definitions
**************************************************************************************************************************/

typedef LibGRPCWrapper_int32 LibGRPCWrapperResult;
typedef void * LibGRPCWrapperHandle;
typedef void * LibGRPCWrapper_pvoid;

/*************************************************************************************************************************
 Version for LibGRPCWrapper
**************************************************************************************************************************/

#define LIBGRPCWRAPPER_VERSION_MAJOR 1
#define LIBGRPCWRAPPER_VERSION_MINOR 2
#define LIBGRPCWRAPPER_VERSION_MICRO 0
#define LIBGRPCWRAPPER_VERSION_PRERELEASEINFO ""
#define LIBGRPCWRAPPER_VERSION_BUILDINFO ""

/*************************************************************************************************************************
 Error constants for LibGRPCWrapper
**************************************************************************************************************************/

#define LIBGRPCWRAPPER_SUCCESS 0
#define LIBGRPCWRAPPER_ERROR_NOTIMPLEMENTED 1001 /** functionality not implemented */
#define LIBGRPCWRAPPER_ERROR_INVALIDPARAM 1002 /** an invalid parameter was passed */
#define LIBGRPCWRAPPER_ERROR_INVALIDCAST 1003 /** a type cast failed */
#define LIBGRPCWRAPPER_ERROR_BUFFERTOOSMALL 1004 /** a provided buffer is too small */
#define LIBGRPCWRAPPER_ERROR_GENERICEXCEPTION 1005 /** a generic exception occurred */
#define LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY 1006 /** the library could not be loaded */
#define LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT 1007 /** a required exported symbol could not be found in the library */
#define LIBGRPCWRAPPER_ERROR_INCOMPATIBLEBINARYVERSION 1008 /** the version of the binary interface does not match the bindings interface */
#define LIBGRPCWRAPPER_ERROR_NOTCONNECTED 1009 /** PLC is not connected */

/*************************************************************************************************************************
 Error strings for LibGRPCWrapper
**************************************************************************************************************************/

inline const char * LIBGRPCWRAPPER_GETERRORSTRING (LibGRPCWrapperResult nErrorCode) {
  switch (nErrorCode) {
    case LIBGRPCWRAPPER_SUCCESS: return "no error";
    case LIBGRPCWRAPPER_ERROR_NOTIMPLEMENTED: return "functionality not implemented";
    case LIBGRPCWRAPPER_ERROR_INVALIDPARAM: return "an invalid parameter was passed";
    case LIBGRPCWRAPPER_ERROR_INVALIDCAST: return "a type cast failed";
    case LIBGRPCWRAPPER_ERROR_BUFFERTOOSMALL: return "a provided buffer is too small";
    case LIBGRPCWRAPPER_ERROR_GENERICEXCEPTION: return "a generic exception occurred";
    case LIBGRPCWRAPPER_ERROR_COULDNOTLOADLIBRARY: return "the library could not be loaded";
    case LIBGRPCWRAPPER_ERROR_COULDNOTFINDLIBRARYEXPORT: return "a required exported symbol could not be found in the library";
    case LIBGRPCWRAPPER_ERROR_INCOMPATIBLEBINARYVERSION: return "the version of the binary interface does not match the bindings interface";
    case LIBGRPCWRAPPER_ERROR_NOTCONNECTED: return "PLC is not connected";
    default: return "unknown error";
  }
}

/*************************************************************************************************************************
 Declaration of handle classes 
**************************************************************************************************************************/

typedef LibGRPCWrapperHandle LibGRPCWrapper_Base;
typedef LibGRPCWrapperHandle LibGRPCWrapper_Connection;

namespace LibGRPCWrapper {

} // namespace LibGRPCWrapper;

// define legacy C-names for enums, structs and function types

#endif // __LIBGRPCWRAPPER_TYPES_HEADER_CPP
